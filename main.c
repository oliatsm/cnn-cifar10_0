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
    float* restrict O1 = malloc(sizeof(float)*cnn->L1->out_width*cnn->L1->out_height*cnn->L1->out_depth);
#pragma acc enter data create(O1[0:cnn->L1->out_width*cnn->L1->out_height*cnn->L1->out_depth])
    float* restrict O2 = malloc(sizeof(float)*cnn->L2->out_width*cnn->L2->out_height*cnn->L2->out_depth);
#pragma acc enter data create(O2[0:cnn->L2->out_width*cnn->L2->out_height*cnn->L2->out_depth])
    float* restrict O3 = malloc(sizeof(float)*cnn->L3->out_width*cnn->L3->out_height*cnn->L3->out_depth);
#pragma acc enter data create(O3[0:cnn->L3->out_width*cnn->L3->out_height*cnn->L3->out_depth])
    float* restrict O4 = malloc(sizeof(float)*cnn->L4->out_width*cnn->L4->out_height*cnn->L4->out_depth);
#pragma acc enter data create(O4[0:cnn->L4->out_width*cnn->L4->out_height*cnn->L4->out_depth])
    float* restrict O5 = malloc(sizeof(float)*cnn->L5->out_width*cnn->L5->out_height*cnn->L5->out_depth);
#pragma acc enter data create(O5[0:cnn->L5->out_width*cnn->L5->out_height*cnn->L5->out_depth])
    float* restrict O6 = malloc(sizeof(float)*cnn->L6->out_width*cnn->L6->out_height*cnn->L6->out_depth);
#pragma acc enter data create(O6[0:cnn->L6->out_width*cnn->L6->out_height*cnn->L6->out_depth])
    float* restrict O7 = malloc(sizeof(float)*cnn->L7->out_width*cnn->L7->out_height*cnn->L7->out_depth);
#pragma acc enter data create(O7[0:cnn->L7->out_width*cnn->L7->out_height*cnn->L7->out_depth])
    float* restrict O8 = malloc(sizeof(float)*cnn->L8->out_width*cnn->L8->out_height*cnn->L8->out_depth);
#pragma acc enter data create(O8[0:cnn->L8->out_width*cnn->L8->out_height*cnn->L8->out_depth])
    float* restrict O9 = malloc(sizeof(float)*cnn->L9->out_width*cnn->L9->out_height*cnn->L9->out_depth);
#pragma acc enter data create(O9[0:cnn->L9->out_width*cnn->L9->out_height*cnn->L9->out_depth])
    float* restrict O10 = malloc(sizeof(float)*cnn->L10->out_depth*cnn->L10->in_neurons);
#pragma acc enter data create(O10[0:cnn->L10->out_width*cnn->L10->out_height*cnn->L10->out_depth])
    float** restrict O11 = malloc2D(NUM_IMAGES,cnn->L11->out_depth);
#pragma acc enter data create(O11[0:NUM_IMAGES][0:cnn->L11->out_depth])

    //Net Forward
    t1 = clock();
    for(int i=0;i<NUM_IMAGES;i++){

        conv_forward(input[i],cnn->L1,O1);
        relu_forward(O1,cnn->L2,O2);
        pool_forward(O2,cnn->L3,O3);
        conv_forward(O3,cnn->L4,O4);
        relu_forward(O4,cnn->L5,O5);
        pool_forward(O5,cnn->L6,O6);
        conv_forward(O6,cnn->L7,O7);
        relu_forward(O7,cnn->L8,O8);
        pool_forward(O8,cnn->L9,O9);
        fc_forward(O9,cnn->L10,O10);
        softmax_forward(O10,cnn->L11,O11[i]);

        }
    t2 = clock();
   arr2txt(O11[NUM_IMAGES-1],cnn->L11->out_width,cnn->L11->out_depth,"O11_1.txt");
    printf("Net Forward total time:%f seconds\n",(double)(t2-t1)/CLOCKS_PER_SEC);

    // Results
    int predictions[NUM_IMAGES];
    for(int n=0;n<NUM_IMAGES;n++){
        int class_o = 0;
        float max_o = O11[n][0];
        for(int i=1;i<cnn->L11->out_depth;i++){
            if(max_o < O11[n][i]){
                class_o = i;
                max_o = O11[n][i];
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

#pragma acc exit data delete(O11[0:NUM_IMAGES][0:cnn->L11->out_depth])
    free(O11);
#pragma acc exit data delete(O10[0:cnn->L10->out_width*cnn->L10->out_height*cnn->L10->out_depth])
    free(O10);
#pragma acc exit data delete(O9[0:cnn->L9->out_width*cnn->L9->out_height*cnn->L9->out_depth])
    free(O9);
#pragma acc exit data delete(O8[0:cnn->L8->out_width*cnn->L8->out_height*cnn->L8->out_depth])    
    free(O8);
#pragma acc exit data delete(O7[0:cnn->L7->out_width*cnn->L7->out_height*cnn->L7->out_depth])
    free(O7);
#pragma acc exit data delete(O6[0:cnn->L6->out_width*cnn->L6->out_height*cnn->L6->out_depth])   
    free(O6);    
#pragma acc exit data delete(O5[0:cnn->L5->out_width*cnn->L5->out_height*cnn->L5->out_depth])
    free(O5);
#pragma acc exit data delete(O4[0:cnn->L4->out_width*cnn->L4->out_height*cnn->L4->out_depth])
    free(O4);
#pragma acc exit data delete(O3[0:cnn->L3->out_width*cnn->L3->out_height*cnn->L3->out_depth])
    free(O3);
#pragma acc exit data delete(O2[0:cnn->L2->out_width*cnn->L2->out_height*cnn->L2->out_depth])    
    free(O2);
#pragma acc exit data delete(O1[0:cnn->L1->out_width*cnn->L1->out_height*cnn->L1->out_depth])
    free(O1);


    // free_softmax(L11);
    // free_fc(L10);

    // free_pool(L9);
    // free_relu(L8);
    // free_conv(L7);

    // free_pool(L6);
    // free_relu(L5);
    // free_conv(L4);

    // free_pool(L3);
    // free_relu(L2);
    // free_conv(L1);
    free_network(cnn);

    #pragma acc exit data delete(input[0:NUM_IMAGES][0:IMAGE_PIXELS])
    free(input);
    printf("END!\n");

    return 0;
}

