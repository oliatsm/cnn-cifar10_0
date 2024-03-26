#include <stdio.h>
#include <stdlib.h>

#include "layers.h"

int load_data(float *data_array, int size, char * file_name){

    FILE * fp;
    fp=fopen(file_name,"r");
    if(fp==NULL){
        printf("Error opening file!\n");
        return 1;
    }

    int number;
    
    for(int i=0;i<size;i++){
        fscanf(fp,"%d",&number);
        data_array[i]=number;
        printf("%d ",number);
    }printf(".\n");

fclose(fp);
return 0;

}

void convLayer_forward(int M, int C, int H, int W, int K, float* X, float* Weights, float* Y) {
    // Validate input dimensions for compatibility
    if (H < K || W < K) {
        printf("Error: Input image dimensions (H=%d, W=%d) must be greater than or equal to filter size (K=%d).\n", H, W, K);
        return;
    }

    int H_out = H - K + 1;
    int W_out = W - K + 1;

    for (int m = 0; m < M; m++) {  // for each output feature map
        for (int h = 0; h < H_out; h++) { // for each output element
            for (int w = 0; w < W_out; w++) {
                Y[m * H_out * W_out + h * W_out + w] = 0.0f;  // Efficient indexing with offset
                for (int c = 0; c < C; c++) { // sum over all input feature maps
                    for (int p = 0; p < K; p++) { // KxK filter
                        for (int q = 0; q < K; q++) {
                            int x_idx = c * H * W + (h + p) * W + (w + q);
                            int w_idx = m * C * K * K + c * K * K + p * K + q;
                            Y[m * H_out * W_out + h * W_out + w] += X[x_idx] * Weights[w_idx];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Define sample input and filter dimensions
    int M = 2;  // Number of output feature maps
    int C = 3;  // Number of input feature maps
    int H = 3;  // Input image height
    int W = 3;  // Input image width
    int K = 2;  // Filter size (KxK)

    ConvLayer *L1;

    L1=make_conv_layer(W,H,C,K,M,1,0);
    print_conv_layer(L1);

    // Allocate memory for input, filter, and output (assuming float data type)
    float* X = (float*)malloc(C * H * W * sizeof(float));
    float* Weights = (float*)malloc(M * C * K * K * sizeof(float));
    float* Y = (float*)malloc(M * (H - K + 1) * (W - K + 1) * sizeof(float));

    load_data(X,C * H * W,"INPUT.txt");
    
    load_data(Weights,M * C * K * K,"WEIGHTS.txt");

    L1->weights=Weights;
    print_conv_layer(L1);

    // Perform convolution
    convLayer_forward(M, C, H, W, K, X, L1->weights, Y);

    // Print the first few elements of the output (adjust printing as needed)
    printf("Output :\n");
    // for (int m = 0; m < M; m++) {
    //     for (int h = 0; h < 2; h++) {
    //         for (int w = 0; w < 2; w++) {
    //             printf("Y[%d, %d, %d] = %.2f\n", m, h, w, Y[m * (H - K + 1) * (W - K + 1) + h * (W - K + 1) + w]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }
    for (int i=0;i<(M * (H - K + 1) * (W - K + 1));i++)
        printf("%.2f ",Y[i]);
    putchar('\n');

    // Free allocated memory
    free(X);
    free(Weights);
    free(Y);

    return 0;
}
