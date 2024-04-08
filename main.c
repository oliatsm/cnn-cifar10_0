#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h> 

#include <openacc.h>

#include "layers.h"
#include "network.h"
#include "malloc2D.h"
// #include "tests.h"

#define NUM_IMAGES 1200//Number of Input Data
#define NUM_IMAGES 1200//Number of Input Data
#define NUM_CLASSES 10 // Number of Classes, CIFAR-10
#define IMAGE_PIXELS 3072 // Number of pixels of each image

#define MAX_TRAINING_DATA 50000
#define MAX_BATCH_DATA 10000


// Folder for .bin files of cifar dataset on my system.
const char *DATA_FOLDER = "../cifar-10-batches-bin";

// Loading N samples from CIFAR-10 Dataset to Image[N][PIXEL] and Label[N]
int load_data(float** image, int * label, int N) {
    
    //Find how many batches I need and how many extra samples
    int batches = (N/MAX_BATCH_DATA)+1; 
    int samples = N%MAX_BATCH_DATA;
    int n = 0;  //Image index

    // printf("Batches: %d, Samples: %d.\n",batches,samples);
    char file_name[1024];
    size_t LINE_SIZE = 3073;
    
    //Loading the whole batches. If we need less than 10.000 images, the condition (b<batches) ends the loop.
    for (int b=1;b<batches;b++){
        printf("Loading input batch %d...\n", b);

        sprintf(file_name, "%s/data_batch_%d.bin", DATA_FOLDER, b);

        FILE *fbin = fopen(file_name, "rb");
        if(fbin==NULL){
            printf("File not found. Error reading .bin files.\n");
            exit(EXIT_FAILURE);
        }

        uint8_t data[LINE_SIZE];
        for (int i = 0; i < MAX_BATCH_DATA; i++) {

            size_t bytesRead = fread(data, 1, LINE_SIZE, fbin);
            assert(bytesRead == LINE_SIZE);

            label[n] = data[0];
            size_t data_i=1;
            for (int j = 0; j < IMAGE_PIXELS && data_i<LINE_SIZE; j++) {
                image[n][j] = (float)data[data_i++]/255.0-0.5;
            }
            n++;
            //printf("%d ",n);
        }
        assert((n%MAX_BATCH_DATA)==0);
        fclose(fbin);
    }

    // Loading less than 10.000 images from a batch
    if(samples!=0){
        printf("Loading input batch %d...\n", batches);

            sprintf(file_name, "%s/data_batch_%d.bin", DATA_FOLDER, batches);

            FILE *fbin = fopen(file_name, "rb");

            if(fbin==NULL){
                printf("File not found. Error reading .bin files.\n");
                exit(EXIT_FAILURE);
            }

            uint8_t data[LINE_SIZE];
            for (int i = 0; i < samples; i++) {

                size_t bytesRead = fread(data, 1, LINE_SIZE, fbin);
                assert(bytesRead == LINE_SIZE);

                label[n] = data[0];
                size_t data_i=1;
                for (int j = 0; j < IMAGE_PIXELS && data_i<LINE_SIZE; j++) {
                    image[n][j] = (float)data[data_i++]/255.0-0.5;
                }
                n++;
            }
            fclose(fbin);
    }assert(n==N);

    return 0;
}

void arr2txt(float *arr, int N,int M, char * file_name) {
    FILE *file = fopen(file_name, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file,"%d,%d,%d\n",N,N,M);
    for (int k = 0; k < M; ++k) {
        for (int j = 0; j < N; ++j) {
            for (int i = 0; i < N; ++i) {
                int idx = ((j*N)+i)+(N*N)*k;
                fprintf(file, "%f ", arr[idx]);
                // printf("%d\n",idx);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

int main(){
    // const char *label_names[]={"airplane","automobile","bird","cat","deer","dog","frog","horse","ship","truck"};
    clock_t t1,t2; 
    printf("CNN for %d images\n",NUM_IMAGES);

    int labels[NUM_IMAGES];

    float** restrict input =malloc2D(NUM_IMAGES,IMAGE_PIXELS);
    #pragma acc enter data create(input[0:NUM_IMAGES][0:IMAGE_PIXELS])

    load_data(input,labels,NUM_IMAGES);
    #pragma acc update device (input[0:NUM_IMAGES][0:IMAGE_PIXELS])

    Network *cnn = make_network();
    // Network Layers
    
    
    //Loading Layers' parameters
    load_conv(cnn->L1,"./snapshot/layer1_conv.txt");
    load_conv(cnn->L4,"./snapshot/layer4_conv.txt");
    load_conv(cnn->L7,"./snapshot/layer7_conv.txt");
    load_fc(cnn->L10,"./snapshot/layer10_fc.txt");
    
    //Allocate Outputs
    float **O = allocate_outputs(cnn);
    float**  output =malloc2D(NUM_IMAGES,cnn->L11->out_depth);
    #pragma acc enter data create(output[0:NUM_IMAGES][0:cnn->L11->out_depth])


    //Net Forward
    t1 = clock();
    for(int i=0;i<NUM_IMAGES;i++){

        conv_forward(input[i],cnn->L1,O[0]);
        relu_forward(O[0],cnn->L2,O[1]);
        pool_forward(O[1],cnn->L3,O[2]);
        conv_forward(O[2],cnn->L4,O[3]);
        relu_forward(O[3],cnn->L5,O[4]);
        pool_forward(O[4],cnn->L6,O[5]);
        conv_forward(O[5],cnn->L7,O[6]);
        relu_forward(O[6],cnn->L8,O[7]);
        pool_forward(O[7],cnn->L9,O[8]);
        fc_forward(O[8],cnn->L10,O[9]);
        softmax_forward(O[9],cnn->L11,output[i]);

        }
    t2 = clock();
   arr2txt(output[NUM_IMAGES-1],cnn->L11->out_width,cnn->L11->out_depth,"out1_1.txt");
    printf("Net Forward total time:%f seconds\n",(double)(t2-t1)/CLOCKS_PER_SEC);

    // Results
    int predictions[NUM_IMAGES];
    for(int n=0;n<NUM_IMAGES;n++){
        int class_o = 0;
        float max_o = output[n][0];
        for(int i=1;i<cnn->L11->out_depth;i++){
            if(max_o < output[n][i]){
                class_o = i;
                max_o = output[n][i];
            }
        }
        predictions[n] = class_o;
    }

    //Network Accuracy
    int correct_label=0;
    for(int n=0;n<NUM_IMAGES;n++){
        if(predictions[n]==labels[n]){
            correct_label++;
        }
    }
   

    printf("Net Accuracy: %.2f %% \n",100*(float)correct_label/NUM_IMAGES);
#pragma acc exit data delete(output[0:NUM_IMAGES][0:cnn->L11->out_depth])
    free(output);
    free(O);

    free_network(cnn);

    #pragma acc exit data delete(input[0:NUM_IMAGES][0:IMAGE_PIXELS])
    free(input);
    
    printf("END!\n");

    return 0;
}

