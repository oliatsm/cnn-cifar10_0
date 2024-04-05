#ifndef LAYERS_H
#define LAYERS_H

#include <stdio.h>
// Input Data
#define N_in 32//Input Width-Height
#define C_in 3//Colour Chanels

//Layer 1 : Convolutional
#define K1 5 //Filter Width Height
#define S1 1 //Stride
#define P1 2 //Padding
#define M1 16 //Output number of Feature Maps 
//Layer 2 : ReLU (No parameters)
//Layer 3 : Pooling
#define K3 2
#define S3 2
#define P3 0

//Layer 4 : Convolutional
#define K4 5 //Filter Width Height
#define S4 1 //Stride
#define P4 2 //Padding
#define M4 20 //Output number of Feature Maps 
//Layer 5 : ReLU (No parameters)
//Layer 6 : Pooling
#define K6 2
#define S6 2
#define P6 0

//Layer 7 : Convolutional
#define K7 5 //Filter Width Height
#define S7 1 //Stride
#define P7 2 //Padding
#define M7 20 //Output number of Feature Maps 
//Layer 8 : ReLU (No parameters)
//Layer 9 : Pooling
#define K9 2
#define S9 2
#define P9 0

//Layer 10 : Fully Connected
#define M10 10 // Output Neurons

//Layer 11 : Softmax (No parameters)

typedef struct conv_layer {
    int in_width;
    int in_height;
    int in_depth;

    int num_filters;
    int filter_width;
    int filter_height;
    int stride;
    int padding;

    int out_width;
    int out_height;
    int out_depth;

    float *weights;
    float *bias;

}Conv_Layer;

typedef struct relu_layer {
    int in_width;
    int in_height;
    int in_depth;

    int out_width;
    int out_height;
    int out_depth;

}ReLU_Layer;

typedef struct pool_layer {
    int in_width;
    int in_height;
    int in_depth;

    int pool_width;
    int stride;
    int padding;

    int out_width;
    int out_height;
    int out_depth;

}Pool_Layer;

typedef struct fc_layer {
    int in_width;
    int in_height;
    int in_depth;

    int in_neurons;

    int out_width;
    int out_height;
    int out_depth;

    float * weights;
    float * bias;

}FC_Layer;

typedef struct softmax_layer {
    int in_width;
    int in_height;
    int in_depth;

    int out_width;
    int out_height;
    int out_depth;

    float * likelihoods;

}Softmax_Layer;

Conv_Layer * make_conv_layer(int W, int H, int D,int K, int M, int S, int P);
ReLU_Layer * make_relu_layer(int W, int H, int D);
Pool_Layer * make_pool_layer(int W, int H, int D,int K, int S, int P);
FC_Layer   * make_fc_layer(int W, int H, int D,int num_neurons);
Softmax_Layer * make_softmax_layer(int W, int H, int D);

void free_conv(Conv_Layer * l);


void conv_forward(float* restrict X, Conv_Layer * l,float* restrict Y);
void relu_forward(float* restrict X, ReLU_Layer * l,float * restrict Y);
void pool_forward(float * restrict X, Pool_Layer * l,float * restrict Y);
void fc_forward(float * restrict X, FC_Layer * l,float * restrict Y);
void softmax_forward(float * restrict X, Softmax_Layer * l,float * restrict Y);

int load_conv(Conv_Layer* l ,char * file_name);
int load_fc(FC_Layer *l, const char *filename);


#endif