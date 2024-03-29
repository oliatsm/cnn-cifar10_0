#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h> 

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

inline float get_image_pixel(float *image,int width,int height,int channel){
    return image[((height*IMAGE_HEIGHT)+width)+(IMAGE_WIDTH*IMAGE_HEIGHT)*channel];
}
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
    printf("Writing to file...\n");
    FILE *file = fopen(file_name, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int k = 0; k < M; ++k) {
        for (int j = 0; j < N; ++j) {
            for (int i = 0; i < N; ++i) {
                int idx = ((j*N)+i)+(N*N*M)*k;
                // fprintf(file, "%.4f ", arr[idx]);
                printf("%d\n",idx);
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
    // printf("%d %d %d %d\n", filter_width, filter_height, depth, filters);
    assert(filter_width==K1);
    assert(filter_height==K1);
    assert(depth==C_in);
    assert(filters==M1);

    double val;
    for(int f = 0; f < filters; f++) {
        for (int x = 0; x < filter_width; x++) {
            for (int y = 0; y < filter_height; y++) {
                for (int d = 0; d < depth; d++) {
                    
                    // fscanf(fin, "%lf", &val);
                    // volume_set(l->filters[f], x, y, d, val);
                    int idx=(filter_width*y+x)*depth+d;
                    printf("%d \n",idx);
                    // w[idx]=(float)val;
                    // printf("%f \n",w[idx]);
                }
            }
        }

    }

    printf(".");
    for(int d = 0; d < M1; d++) {
        // fscanf(fin, "%lf", &val);
        // volume_set(l->biases, 0, 0, d, val);
        int idx=(filter_width*0+0)*depth+d;
        // b[idx]=(float)val;
        printf("%d \n",idx);
        // printf("%f \n",b[idx]);
    }

    fclose(fin);
    
    return 0;
}

int main(){
    // const char *label_names[]={"airplane","automobile","bird","cat","deer","dog","frog","horse","ship","truck"};
    int N = NUM_IMAGES;
    clock_t t1,t2; 
 
    // if (N>50000 || N<=0){
    //     printf("Not Valind Number of Sample Images.\n (0 < n < 50.000)\n");
    //     exit(EXIT_SUCCESS);
    // }

    // float (*input)[IMAGE_PIXELS]=malloc(sizeof(*input)*N);
    float **input = (float **)malloc(N*sizeof(float *) + N*IMAGE_PIXELS*sizeof(float));
    assert(input!=NULL);

    input[0] = (float *)(input + N);
   for (int j = 1; j < N; j++) {
      input[j] = input[j-1] + IMAGE_PIXELS;
   }

    int labels[N];

    t1 = clock();        
    load_data(input,labels,N);
    t2 = clock();

    //Weights
    float *weights1=malloc(sizeof(float)*(M1*C_in*K1*K1));
    assert(weights1!=NULL);
    float * bias1=(float *)malloc(sizeof(float)*M1);
     assert(bias1!=NULL);
    
    load_weights(weights1,bias1,"./snapshot/layer1_conv.txt");
   
    // img2txt(input,labels,N);
    //Test First Convolution Layer
    float * O1 =malloc(sizeof(float)*N1*N1*M1);
    assert(O1!=NULL);

    // convLayer_forward(N_in,C_in,input[0],M1,K1,weights1,bias1,N1,O1,S1,P1);
    // arr2txt(O1,N1,M1,"O1.txt");
    // printf("%d %d %d\n",N1,N1,M1);
    // for (size_t i = 0; i < N1*N1*M1; i++)
    // {
    //     printf("%f\n",O1[i]);
    // }
    
    

    printf("Total time:%f seconds\n",(double)(t2-t1)/CLOCKS_PER_SEC);
    free(O1);
    free(bias1);
    free(weights1);
    free(input);
    printf("END!\n");

    return 0;
}