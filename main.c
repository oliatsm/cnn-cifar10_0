#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h> 

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
int load_data(float (*image)[IMAGE_PIXELS], int * label, int N) {
    
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

void img2txt(float (*image)[IMAGE_PIXELS], int *label, int N) {
    FILE *file = fopen("image.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int n = 0; n < N; n+=5000) {
        fprintf(file, "%d: %d \n",n,label[n]);
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


int main(){
    // const char *label_names[]={"airplane","automobile","bird","cat","deer","dog","frog","horse","ship","truck"};
    int N = NUM_IMAGES;
    clock_t t1,t2; 
 
    // if (N>50000 || N<=0){
    //     printf("Not Valind Number of Sample Images.\n (0 < n < 50.000)\n");
    //     exit(EXIT_SUCCESS);
    // }

    float (*input)[IMAGE_PIXELS]=malloc(sizeof(*input)*N);
    assert(input!=NULL);

    int labels[N];

    t1 = clock();        
    load_data(input,labels,N);
    t2 = clock();
    
    // img2txt(input,labels,N);

    printf("Total time:%f seconds\n",(double)(t2-t1)/CLOCKS_PER_SEC);

    free(input);
    printf("END!\n");

    return 0;
}