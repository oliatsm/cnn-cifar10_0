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
        // printf("%d ",number);
    }
    // printf(".\n");

fclose(fp);
return 0;

}

// void convLayer_forward(int M, int C, int H, int W, int K, float* X, float* Weights, float* Y) {
void convLayer_forward(float* X, ConvLayer *l, float* Y) {

    int H=l->in_height;
    int W=l->in_width;
    int C=l->in_depth;
    int K=l->filter_height;
    int P=l->padding;
    int S=l->stride;
    // Validate input dimensions for compatibility
    if (H < K || W < K) {
        printf("Error: Input image dimensions (H=%d, W=%d) must be greater than or equal to filter size (K=%d).\n", H, W, K);
        return;
    }

    int H_out = l->out_height;
    int W_out = l->out_width;
    int M = l->out_depth;

    for(int m=0;m<M;m++){
        for(int h=0;h<H_out;h++){
            for(int w=0;w<W_out;w++){
                int y_idx=w+(W_out*h)+ (W_out*H_out)*m;
                Y[y_idx]=0.0;
                for(int c=0;c<C;c++){
                    for(int fh=0;fh<K;fh++){
                        for(int fw=0;fw<K;fw++){
                            int f_idx=m*(K*K*C)+fw+(fh*K)+c*(K*K);
                            Y[y_idx]+=l->weights[f_idx];
                            printf("%d %d\n",y_idx,f_idx);
                        }

                    }
                }

                Y[y_idx]+=l->bias[m];

            }
        }
    }
}

void print_map(float * x, int W, int H, int D ){

    for(int k=0;k<D;k++){
            for(int j=0;j<H;j++){
                for(int i=0;i<W;i++){
                    int indx=(j*H)+i+(W*H)*k;
                    printf("%2.f ",x[indx]);
                }
                putchar('\n');
            }
            putchar('\n');
        }
        //putchar('\n');
}

int main() {
    /*
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
    
    for (int i=0;i<(M * (H - K + 1) * (W - K + 1));i++)
        printf("%.2f ",Y[i]);
    putchar('\n');

    // Free allocated memory
    free(X);
    free(Weights);
    free(Y);
    */

    //**********************************************************************
    int M = 2;  // Number of output feature maps
    int C = 3;  // Number of input feature maps
    int H = 5;  // Input image height
    int W = 5;  // Input image width
    int K = 3;  // Filter size (KxK)
    ConvLayer * L2;
    L2=make_conv_layer(W,H,C,K,M,2,1);
    float * Input =malloc(sizeof(float)*W*H*C);
    load_data(Input,(H*W*C),"data/input.txt");
    print_map(Input,W,H,C);
    load_data(L2->weights,(K*K*M*C),"data/weights.txt");
    L2->bias[0]=1;L2->bias[1]=0;
    print_conv_layer(L2);

    float * Output =malloc(sizeof(float)*(L2->out_depth*L2->out_height*L2->out_height));
    for(int i=0;i<(L2->out_depth*L2->out_height*L2->out_height);i++)
        Output[i]=-1.0;
    
    printf("Output:\n");
    print_map(Output,L2->out_width,L2->out_height,L2->out_depth);

    convLayer_forward(Input,L2,Output);

printf("Output:\n");
    print_map(Output,L2->out_width,L2->out_height,L2->out_depth);

    return 0;
}
