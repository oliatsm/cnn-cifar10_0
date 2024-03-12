
//  void convLayer_forward(int M, int C, int H, int W, int K, float* X, float* W,float* Y) {
//     int H_out = H - K + 1;
//     int W_out = W - K + 1;
    
//     for(int m = 0; m < M; m++)  // for each output feature map
//         for(int h = 0; h < H_out; h++) // for each output element
//             for(int w = 0; w < W_out; w++) {
//                 Y[m, h, w] = 0;
//                 for(int c = 0; c < C; c++) // sum over all input feature maps
//                     for(int p = 0; p < K; p++) // KxK filter
//                         for(int q = 0; q < K; q++)
//                             Y[m, h, w] += X[c, h + p, w + q] * W[m, c, p, q];
//             }
// }

#include <stdio.h>
#include <stdlib.h>

void convLayer_forward(int M, int C, int H, int W, int K, float* X, float* We, float* Y) {
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
                            Y[m * H_out * W_out + h * W_out + w] += X[x_idx] * We[w_idx];
                        }
                    }
                }
            }
        }
    }
}

int load(float * numbers,int size,char * c){
FILE *fp;
    int num, i;

    fp = fopen(c, "r");  // Replace "data.txt" with your actual file name
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    
    // while (fscanf(fp, "%d", &num) != EOF && i < sizeof(numbers) / sizeof(numbers[0])) {
    for(i = 0;i<size;i++){
        fscanf(fp, "%d", &num);
        numbers[i] = (float)num;  // Convert integer to float
    }

    // Check for potential errors during reading
    if (ferror(fp)) {
        printf("Error reading from file!\n");
        fclose(fp);
        return 1;
    }

    // Close the file
    fclose(fp);
}

int main() {
    // Define sample input and filter dimensions
    int M = 2;  // Number of output feature maps
    int C = 3;  // Number of input feature maps
    int H = 3;  // Input image height
    int W = 3;  // Input image width
    int K = 2;  // Filter size (KxK)

    // Allocate memory for input, filter, and output (assuming float data type)
    float* X = (float*)malloc(C * H * W * sizeof(float));
    float* We = (float*)malloc(M * C * K * K * sizeof(float));
    float* Y = (float*)malloc(M * (H - K + 1) * (W - K + 1) * sizeof(float));

    // Initialize input and filter with sample values (replace with your actual data)
    printf("x[%d][%d][%d]:\n",W,H,C);
    load(X,(C * H * W ),"INPUT.txt");
    for (int i = 0; i < C * H * W; i++) {
        printf("%.2f ",X[i]);
    } printf("\n");

    printf("\nWe:[%d][%d][%d]\n",K,K,M*C);
        load(We,(M * C * K * K),"WEIGHTS.txt");
    for (int i = 0; i < M * C * K * K; i++) {
                printf("%.2f ",We[i]);
    } printf("\n");

    // Perform convolution
    convLayer_forward(M, C, H, W, K, X, We, Y);

    // Print the first few elements of the output (adjust printing as needed)
    printf("\ny:[%d][%d][%d]\n",(W - K + 1),(H - K + 1),M);
    printf("Output (first few elements):\n");
    for (int m = 0; m < M; m++) {
        for (int h = 0; h < (H - K + 1); h++) {
            for (int w = 0; w < (W - K + 1); w++) {
                printf("Y[%d, %d, %d] = %.2f\n", m, h, w, Y[m * (H - K + 1) * (W - K + 1) + h * (W - K + 1) + w]);
            }
            // printf("\n");
        }
        printf("\n");
    }

    // Free allocated memory
    free(X);
    free(We);
    free(Y);

    return 0;
}
