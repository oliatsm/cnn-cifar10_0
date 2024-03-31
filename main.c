#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h> 

#include <openacc.h>

#include "layers.h"

#define NUM_IMAGES 50000//Number of Input Data
#define NUM_CLASSES 10 // Number of Classes, CIFAR-10
#define IMAGE_PIXELS 3072 // Number of pixels of each image

#define MAX_TRAINING_DATA 50000
#define MAX_BATCH_DATA 10000

#define IMAGE_WIDTH 32
#define IMAGE_HEIGHT 32
#define IMAGE_CHANEL 3


// Folder for .bin files of cifar dataset on my system.
const char *DATA_FOLDER = "../cifar-10-batches-bin";

// Loading N samples from CIFAR-10 Dataset to Image[N][PIXEL] and Label[N]
int load_data(float **image, int * label, int N) {
    
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

void img2txt(float **image, int *label, int N) {
    FILE *file = fopen("image.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int n = 0; n < N; n+=5000) {
        // fprintf(file, "%d: %d \n",n,label[n]);
        for (int k = 0; k < 3; ++k) {
            for (int j = 0; j < 32; ++j) {
                for (int i = 0; i < 32; ++i) {
                    fprintf(file, "%.4f ", image[n][((j*32)+i)+1024*k]);
                }
                fprintf(file, "\n");
            }
        }
    }

    fclose(file);
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

int load_weights(float * w,float * b ,char * file_name){
    printf("Loading Conv Layer 1 Weights\n %dx(%d,%d,%d)\n",M1,K1,K1,C_in);

    int filter_width, filter_height, depth, filters;
    
    FILE *fin = fopen(file_name, "r");
    if (fin == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fscanf(fin, "%d %d %d %d", &filter_width, &filter_height, &depth, &filters);
    printf("%d %d %d %d\n", filter_width, filter_height, depth, filters);
    assert(filter_width==K1);
    assert(filter_height==K1);
    assert(depth==C_in);
    assert(filters==M1);

    double val;
    for(int f = 0; f < filters; f++) {
        for (int i = 0; i < filter_width; i++) {
            for (int j = 0; j < filter_height; j++) {
                for (int d = 0; d < depth; d++) {
                    fscanf(fin, "%lf", &val);
                    int idx=i+j*K1+(d+f*C_in)*(K1*K1);
                    w[idx]=(float)val;
                    // printf("%d, %lf->%f\n",idx,val,w[idx]);
                }
            }
        }

    }

    for(int d = 0; d < M1; d++) {
        fscanf(fin, "%lf", &val);
        int idx=d;
        b[idx]=(float)val;
        // printf("%d\n",idx);
    }

    fclose(fin);
    
    return 0;
}

void print_map(int n,int m,int f,float *x){

    for(int l=0;l<f;l++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<m;k++){
                    int idx=i+(n*j)+(n*n)*k+(n*n*m)*l;
                    printf("%f \n",x[idx]);
                }
                // putchar('\n');
            }
            // putchar('\n');
        }
        // putchar('\n');
    }
}

int main(){
    // const char *label_names[]={"airplane","automobile","bird","cat","deer","dog","frog","horse","ship","truck"};
    // clock_t t1,t2; 
 
    // float **input = (float **)malloc(N*sizeof(float *) + N*IMAGE_PIXELS*sizeof(float));
    // assert(input!=NULL);

    // input[0] = (float *)(input + N);
    // for (int j = 1; j < N; j++) {
    //   input[j] = input[j-1] + IMAGE_PIXELS;
    // }
    int labels[NUM_IMAGES];
    float ** input =(float **)malloc(NUM_IMAGES*sizeof(float *));
    for (int i = 0 ; i < NUM_IMAGES ; i++){
        input[i]=(float*)malloc(sizeof(float)*IMAGE_PIXELS);
    }

    load_data(input,labels,NUM_IMAGES);

#pragma acc enter data copyin (input[:NUM_IMAGES])
    for (int i = 0 ; i < NUM_IMAGES ; i++){
#pragma acc enter data copyin (input[i][:IMAGE_PIXELS])
    }


#pragma acc parallel loop present(input)
    for (int i=0;i<NUM_IMAGES;i++){
        for (int j=0;j<IMAGE_PIXELS;j++){
            input[i][j]+=1;
        }
    }
for (int i=0;i<NUM_IMAGES;i++){
    #pragma acc update self(input[i][:IMAGE_PIXELS])
}
    for (int i=0;i<NUM_IMAGES;i+=5000){
        for (int j=0;j<IMAGE_PIXELS;j+=100){
            printf("%f\n",input[i][j]);
        }
    }

    

    // //Weights
    // float *weights1=malloc(sizeof(float)*(M1*C_in*K1*K1));
    // assert(weights1!=NULL);
    // float * bias1=(float *)malloc(sizeof(float)*M1);
    //  assert(bias1!=NULL);
    
    // load_weights(weights1,bias1,"./snapshot/layer1_conv.txt");
    
    // //Test First Convolution Layer
    // float * O1 =malloc(sizeof(float)*N1*N1*M1);
    // assert(O1!=NULL);

    // t1 = clock();
    // for(int i=0;i<NUM_IMAGES;i++){
    //     printf("conv for image %d\n",i);
    //     convLayer_forward(N_in,C_in,input[i],M1,K1,weights1,bias1,N1,O1,S1,P1);
    //     }
    // t2 = clock();
    
    // arr2txt(O1,N1,M1,"O1.txt");

    // printf("Total time:%f seconds\n",(double)(t2-t1)/CLOCKS_PER_SEC);
    // free(O1);

    // free(bias1);
    // free(weights1);

    for(int i=0;i<NUM_IMAGES;i++){
        free(input[i]);
// #pragma acc exit data delete(input[i])
    }
    free(input);
// #pragma acc exit data delete(input)
    printf("END!\n");

    return 0;
}