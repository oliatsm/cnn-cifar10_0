#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <opencv2/opencv.hpp>

using namespace cv;

#define N 1 //Number of Input Data
#define NUM_CLASSES 10 // Number of Classes, CIFAR-10
#define IMAGE_PIXELS 3072

#define MAX_TRAINING_DATA 50000
#define MAX_BATCH_DATA 10000


// Place where test data is stored on instructional machines.
const char *DATA_FOLDER = "/home/olia/Documents/Programming/cifar-10-batches-bin";


// Load an entire batch of images from the cifar10 data set (which is divided
// into 5 batches with 10,000 images each).
void load_data(int ** image, int * label) {
    
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
        for (int j = 0; j < (IMAGE_PIXELS); j++) {
            image[i][j] = ((int)data[j+1]);///255.0-0.5;
                }
            
            
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
        fprintf(file, "\n\n");
    }

    fclose(file);
}


int main(){

    int **input=(int **)malloc(sizeof(int*)*N);
    for (int i=0;i<N;i++){
        input[i] = (int *)malloc(sizeof(int)*IMAGE_PIXELS);
    }

    int labels[NUM_CLASSES];

    load_data(input,labels);
    
    printf("LABEL = %d\n",labels[0]);
    // for(int i=0;i<IMAGE_PIXELS;i++)
    //     printf("%d, ", input[0][i]);
    // printf("/n");

    // Create an OpenCV Mat object from the array
    // cv::Mat image(32, 32, CV_32SC3, input[0]);
    // image.convertTo(image, CV_8UC3);
    // // Display the image using OpenCV
    // cv::imshow("RGB Image", image);
    // cv::waitKey(0); // Wait for a key press
    // img2txt(input[0]);

    Mat image(32, 32, CV_8UC3);
    for (int i = 0; i < 32 * 32; ++i) {
        image.at<Vec3b>(i) = Vec3b(input[0][i], input[0][i + 1024], input[0][i + 2048]);
    }
    imshow("RGB Image", image);
    waitKey(0);

    free(input);
    printf("END!\n");


    return 0;
}