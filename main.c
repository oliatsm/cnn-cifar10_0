#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define NUM_IMAGES 50000//Number of Input Data
#define NUM_CLASSES 10 // Number of Classes, CIFAR-10
#define IMAGE_PIXELS 3072 //

#define MAX_TRAINING_DATA 50000
#define MAX_BATCH_DATA 10000


// Foler for .bin files of cifar dataset on my system.
const char *DATA_FOLDER = "/home/olia/Documents/Programming/cifar-10-batches-bin";
// const char *DATA_FOLDER = "../cifar-10-batches-bin";


// Loading N samples from CIFAR-10 Dataset to Image[N][PIXEL] and Label[N]
int load_data(int **image, int * label, int N) {
    
    //Find how many batches I need and how many extra samples
    int batches = (N/MAX_BATCH_DATA)+1; 
    int samples = N%MAX_BATCH_DATA;
    int n = 0;  //Image index

    printf("Batches: %d, Samples: %d.\n",batches,samples);
    size_t LINE_SIZE = 3073;
    char file_name[1024];
    
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
                image[n][j] = (int)data[data_i++];///255.0-0.5;
            }
            n++;printf("%d \n",n);
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
                    image[n][j] = (int)data[data_i++];///255.0-0.5;
                }
                n++;
            }
            fclose(fbin);
    }assert(n==N);

    return 0;

}

void img2txt(int *image, int N) {
    FILE *file = fopen("image_N_3.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int n = 0; n < N; ++n) {
        
        for (int k = 0; k < 3; ++k) {
            for (int j = 0; j < 32; ++j) {
                for (int i = 0; i < 32; ++i) {
                    fprintf(file, "%d ", image[((j*32)+i)+1024*k]);
                }
                fprintf(file, "\n");
            }
        }
        // for (int i = 0; i < 3072; ++i) {
        //             fprintf(file, "%d ", image[i]);
        //         }
        // fprintf(file, "\n\n");
    }

    fclose(file);
}


int main(){
    // const char *label_names[]={"airplane","automobile","bird","cat","deer","dog","frog","horse","ship","truck"};
    int N = NUM_IMAGES;

    // if (N>50000 || N<=0){
    //     printf("Not Valind Number of Sample Images.\n (0 < n < 50.000)\n");
    //     exit(EXIT_SUCCESS);
    // }

    int **input=(int **)malloc(sizeof(int*)*N);
    assert(input!=NULL);
    for (int i=0;i<N;i++){
        input[i] = (int *)malloc(sizeof(int)*IMAGE_PIXELS);
        assert(input[i]!=NULL);
    }

    int labels[N];
    
    
    load_data(input,labels,N);

    for (int i=(N-1);i>=0;i--){
        free(input[i]);
    }

    free(input);
    printf("END!\n");

    return 0;
}