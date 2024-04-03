#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h> 

#include <openacc.h>

#include "layers.h"
#include "malloc2D.h"

#define NUM_IMAGES 1//Number of Input Data
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

    printf("Batches: %d, Samples: %d.\n",batches,samples);
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

int load_weights(ConvLayer * l ,char * file_name){
    printf("Loading Conv Layer 1 Weights\n %dx(%d,%d,%d)\n",
            l->num_filters,l->filter_width,l->filter_height,l->in_depth);

    int filter_width, filter_height, depth, filters;
    
    FILE *fin = fopen(file_name, "r");
    if (fin == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fscanf(fin, "%d %d %d %d", &filter_width, &filter_height, &depth, &filters);
    printf("%d %d %d %d\n", filter_width, filter_height, depth, filters);
    assert(filter_width==l->filter_width);
    assert(filter_height==l->filter_height);
    assert(depth==l->in_depth);
    assert(filters==l->num_filters);

    double val;
    for(int f = 0; f < filters; f++) {
        for (int i = 0; i < filter_width; i++) {
            for (int j = 0; j < filter_height; j++) {
                for (int d = 0; d < depth; d++) {
                    fscanf(fin, "%lf", &val);
                    int idx=i+j*filter_width+(d+f*depth)*(filter_width*filter_height);
                    l->weights[idx]=(float)val;
                    //printf("%d, %lf->%f\n",idx,val,l->weights[idx]);
                }
            }
        }

    }

    for(int d = 0; d < filters; d++) {
        fscanf(fin, "%lf", &val);
        int idx=d;
        l->bias[idx]=(float)val;
        // printf("%d\n",idx);
    }

    fclose(fin);
    
    return 0;
}

void arr2txt(float *arr, int N,int M, char * file_name);

int main(){
    // const char *label_names[]={"airplane","automobile","bird","cat","deer","dog","frog","horse","ship","truck"};
    clock_t t1,t2; 

    int labels[NUM_IMAGES];
    
    float** restrict input =malloc2D(NUM_IMAGES,IMAGE_PIXELS);

    load_data(input,labels,NUM_IMAGES);

    // //Weights
    ConvLayer * L1 =make_conv_layer(N_in,N_in,C_in,K1,M1,S1,P1);
    ReluLayer * L2 =make_relu_layer(L1->out_width,L1->out_height,L1->out_depth);
    
    load_weights(L1,"./snapshot/layer1_conv.txt");
    // for(int i=0;i<K1*K1*C_in*M1;i++){
    //     printf("%f\n",L1->weights[i]);
    //     }
    //Test First Convolution Layer
    float* restrict O1 =malloc(sizeof(float)*N1*N1*M1);
    assert(O1!=NULL);
    float* restrict O2 =malloc(sizeof(float)*L2->out_width*L2->out_height*L2->out_depth);


    t1 = clock();
    for(int i=0;i<NUM_IMAGES;i++){
        // printf("conv for image %d\n",i);
        convLayer_forward(input[i],L1,O1);
        relu_forward(O1,L2,O2);
        }
    t2 = clock();
    // arr2txt(input[NUM_IMAGES-1],N_in,C_in,"In_50k.txt"); 
    arr2txt(O1,N1,M1,"O1_1.txt");
    arr2txt(O2,N1,M1,"O2_1.txt");

    // for(int i=0;i<(L1->out_height*L1->out_width*L1->out_depth);i++){
    //     printf("%f\n",O1[i]);
    //     }

    printf("Total time:%f seconds\n",(double)(t2-t1)/CLOCKS_PER_SEC);
    free(O1);
    free(O2);
    free(L1->weights);
    free(L1->bias);
    free(L1);
    free(L2);

    free(input);
    printf("END!\n");

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