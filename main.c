#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h> 

#include <openacc.h>

#include "layers.h"
#include "malloc2D.h"
// #include "tests.h"

#define NUM_IMAGES 50000//Number of Input Data
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

int main(){
    // const char *label_names[]={"airplane","automobile","bird","cat","deer","dog","frog","horse","ship","truck"};
    // clock_t t1,t2; 
    printf("CNN for %d images\n",NUM_IMAGES);

    int labels[NUM_IMAGES];
    
    float** restrict input =malloc2D(NUM_IMAGES,IMAGE_PIXELS);
    #pragma acc enter data create(input[0:NUM_IMAGES][0:IMAGE_PIXELS])

    load_data(input,labels,NUM_IMAGES);
    #pragma acc update device (input[0:NUM_IMAGES][0:IMAGE_PIXELS])

    
    // Network Layers
    Conv_Layer * L1 = make_conv_layer(N_in,N_in,C_in,K1,M1,S1,P1);
    ReLU_Layer * L2 = make_relu_layer(L1->out_width,L1->out_height,L1->out_depth);
    Pool_Layer * L3 = make_pool_layer(L2->out_width,L2->out_height,L2->out_depth,K3,S3,P3);
    Conv_Layer * L4 = make_conv_layer(L3->out_width,L3->out_height,L3->out_depth,K4,M4,S4,P4);
    ReLU_Layer * L5 = make_relu_layer(L4->out_width,L4->out_height,L4->out_depth);
    Pool_Layer * L6 = make_pool_layer(L5->out_width,L5->out_height,L5->out_depth,K6,S6,P6);
    Conv_Layer * L7 = make_conv_layer(L6->out_width,L6->out_height,L6->out_depth,K7,M7,S7,P7);
    ReLU_Layer * L8 = make_relu_layer(L7->out_width,L7->out_height,L7->out_depth);
    Pool_Layer * L9 = make_pool_layer(L8->out_width,L8->out_height,L8->out_depth,K9,S9,P9);
    FC_Layer   *L10 = make_fc_layer(L9->out_width,L9->out_height,L9->out_depth,M10);
    Softmax_Layer *L11 = make_softmax_layer(L10->out_width,L10->out_height,L10->out_depth);
    
    //Loading Layers' parameters
    load_conv(L1,"./snapshot/layer1_conv.txt");
    load_conv(L4,"./snapshot/layer4_conv.txt");
    load_conv(L7,"./snapshot/layer7_conv.txt");
    load_fc(L10,"./snapshot/layer10_fc.txt");
    
    //Allocate Outputs
    float* restrict O1 = malloc(sizeof(float)*L1->out_width*L1->out_height*L1->out_depth);
#pragma acc enter data create(O1[0:L1->out_width*L1->out_height*L1->out_depth])
    float* restrict O2 = malloc(sizeof(float)*L2->out_width*L2->out_height*L2->out_depth);
#pragma acc enter data create(O2[0:L2->out_width*L2->out_height*L2->out_depth])
    float* restrict O3 = malloc(sizeof(float)*L3->out_width*L3->out_height*L3->out_depth);
#pragma acc enter data create(O3[0:L3->out_width*L3->out_height*L3->out_depth])
    float* restrict O4 = malloc(sizeof(float)*L4->out_width*L4->out_height*L4->out_depth);
#pragma acc enter data create(O4[0:L4->out_width*L4->out_height*L4->out_depth])
    float* restrict O5 = malloc(sizeof(float)*L5->out_width*L5->out_height*L5->out_depth);
#pragma acc enter data create(O5[0:L5->out_width*L5->out_height*L5->out_depth])
    float* restrict O6 = malloc(sizeof(float)*L6->out_width*L6->out_height*L6->out_depth);
#pragma acc enter data create(O6[0:L6->out_width*L6->out_height*L6->out_depth])
    float* restrict O7 = malloc(sizeof(float)*L7->out_width*L7->out_height*L7->out_depth);
#pragma acc enter data create(O7[0:L7->out_width*L7->out_height*L7->out_depth])
    float* restrict O8 = malloc(sizeof(float)*L8->out_width*L8->out_height*L8->out_depth);
#pragma acc enter data create(O8[0:L8->out_width*L8->out_height*L8->out_depth])
    float* restrict O9 = malloc(sizeof(float)*L9->out_width*L9->out_height*L9->out_depth);
#pragma acc enter data create(O9[0:L9->out_width*L9->out_height*L9->out_depth])
    float* restrict O10 = malloc(sizeof(float)*L10->out_depth*L10->in_neurons);
#pragma acc enter data create(O10[0:L10->out_width*L10->out_height*L10->out_depth])
    float** restrict O11 = malloc2D(NUM_IMAGES,L11->out_depth);
#pragma acc enter data create(O11[0:NUM_IMAGES][0:L11->out_depth])


    // //Net Forward
    // t1 = clock();
    // for(int i=0;i<NUM_IMAGES;i++){

    //     conv_forward(input[i],L1,O1);
    //     relu_forward(O1,L2,O2);
    //     pool_forward(O2,L3,O3);
    //     conv_forward(O3,L4,O4);
    //     relu_forward(O4,L5,O5);
    //     pool_forward(O5,L6,O6);
    //     conv_forward(O6,L7,O7);
    //     relu_forward(O7,L8,O8);
    //     pool_forward(O8,L9,O9);
    //     fc_forward(O9,L10,O10);
    //     softmax_forward(O10,L11,O11[i]);

    //     }
    // t2 = clock();
   
    // printf("Net Forward total time:%f seconds\n",(double)(t2-t1)/CLOCKS_PER_SEC);

    // // Results
    // int predictions[NUM_IMAGES];
    // for(int n=0;n<NUM_IMAGES;n++){
    //     int class_o = 0;
    //     float max_o = O11[n][0];
    //     for(int i=1;i<L11->out_depth;i++){
    //         if(max_o < O11[n][i]){
    //             class_o = i;
    //             max_o = O11[n][i];
    //         }
    //     }
    //     predictions[n] = class_o;
    // }

    // //Network Accuracy
    // int correct_label=0;
    // for(int n=0;n<NUM_IMAGES;n++){
    //     if(predictions[n]==labels[n]){
    //         correct_label++;
    //     }
    // }

    // printf("Net Accuracy: %.2f %% \n",100*(float)correct_label/NUM_IMAGES);

#pragma acc exit data delete(O11[0:NUM_IMAGES][0:L11->out_depth])
    free(O11);
#pragma acc exit data delete(O10[0:L10->out_width*L10->out_height*L10->out_depth])
    free(O10);
#pragma acc exit data delete(O9[0:L9->out_width*L9->out_height*L9->out_depth])
    free(O9);
#pragma acc exit data delete(O8[0:L8->out_width*L8->out_height*L8->out_depth])    
    free(O8);
#pragma acc exit data delete(O7[0:L7->out_width*L7->out_height*L7->out_depth])
    free(O7);
#pragma acc exit data delete(O6[0:L6->out_width*L6->out_height*L6->out_depth])   
    free(O6);    
#pragma acc exit data delete(O5[0:L5->out_width*L5->out_height*L5->out_depth])
    free(O5);
#pragma acc exit data delete(O4[0:L4->out_width*L4->out_height*L4->out_depth])
    free(O4);
#pragma acc exit data delete(O3[0:L3->out_width*L3->out_height*L3->out_depth])
    free(O3);
#pragma acc exit data delete(O2[0:L2->out_width*L2->out_height*L2->out_depth])    
    free(O2);
#pragma acc exit data delete(O1[0:L1->out_width*L1->out_height*L1->out_depth])
    free(O1);


    free_softmax(L11);
    free_fc(L10);

    free_pool(L9);
    free_relu(L8);
    free_conv(L7);

    free_pool(L6);
    free_relu(L5);
    free_conv(L4);

    free_pool(L3);
    free_relu(L2);
    free_conv(L1);

    #pragma acc exit data delete(input[0:NUM_IMAGES][0:IMAGE_PIXELS])
    free(input);
    printf("END!\n");

    return 0;
}

