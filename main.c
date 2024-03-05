#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// #include <opencv2/opencv.hpp>

// using namespace cv;

#define N 50000//Number of Input Data
#define NUM_CLASSES 10 // Number of Classes, CIFAR-10
#define IMAGE_PIXELS 3072

#define MAX_TRAINING_DATA 50000
#define MAX_BATCH_DATA 10000


// Place where test data is stored on instructional machines.
// const char *DATA_FOLDER = "/home/olia/Documents/Programming/cifar-10-batches-bin";
const char *DATA_FOLDER = "../cifar-10-batches-bin";


// Load an entire batch of images from the cifar10 data set (which is divided
// into 5 batches with 10,000 images each).
void load_data(int **image, int * label) {
    
    int batch = 1;
    size_t LINE_SIZE = 3073;

    //TODO: Elegxos gia poio batch kano load

    printf("Loading input batch %d...\n", batch);

    char file_name[1024];
    sprintf(file_name, "%s/data_batch_%d.bin", DATA_FOLDER, batch);

    FILE *fbin = fopen(file_name, "rb");
    assert(fbin != NULL);

    for (int i = 0; i < N; i++) {

        uint8_t data[LINE_SIZE];
        assert(fread(data, 1, LINE_SIZE, fbin) == LINE_SIZE);

        label[i] = data[0];
        size_t data_i=1;
        for (int j = 0; j < IMAGE_PIXELS && data_i<LINE_SIZE; j++) {
            image[i][j] = (int)data[data_i++];///255.0-0.5; 
            // printf("(%d,%d) ",j,j+1);
                }//printf("\n");
            
            
    }

    fclose(fbin);

}

void img2txt(int *image) {
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
    const char *label_names[]={"airplane","automobile","bird","cat","deer","dog","frog","horse","ship","truck"};

    int **input=(int **)malloc(sizeof(int*)*N);
    assert(input!=NULL);
    for (int i=0;i<N;i++){
        input[i] = (int *)malloc(sizeof(int)*IMAGE_PIXELS);
        assert(input[i]!=NULL);
    }

    int labels[N];
    

    load_data(input,labels);
    
    //Print image with OpenCV
    // Mat image(32, 32, CV_8UC3);
    // for(int n=0;n<N;n++){
    //     printf("LABEL = %d,%s\n",labels[n],label_names[labels[n]]);
    // for (int i = 0; i < 32 * 32; ++i) {
    //     image.at<Vec3b>(i) = Vec3b((char)input[n][i], (char)input[n][i + 1024],(char) input[n][i + 2048]);
    // }
    // imshow("RGB Image", image);
    // if (waitKey(0) == 27) { // Press 'Esc' to exit
    //         break;
    //     }
    // }
    //^OpenCV

    // for(int i=0;i<32;i++){
    //     for (int j=0;j<32;j++){
    //         printf("%d ",input[0][32*i+j]);
    //     }printf("\n");
    // }

    for (int i=0;i<N;i++){
        free(input[i]);
    }

    free(input);
    printf("END!\n");

    return 0;
}