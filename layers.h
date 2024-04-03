#ifndef LAYERS_H
#define LAYERS_H

#include <stdio.h>
// Input Data
// #define NUM_IMG 2 //Number of images
#define N_in 32//Input Width-Height
#define C_in 3//Colour Chanels

//Layer 1 : Convolutional
// in[32][32][3],out[32][32][16]
//     Filters[5][5][3]x(16), stride:1,pad:2
#define K1 5 //Filter Width Height
#define S1 1 //Stride
#define P1 2 //Padding
//Layer 1 Output
#define N1 32//(N_in-K1+2*P1)/S1+1 //Output Width-Height
#define M1 16 //Output number of Feature Maps 

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

}ConvLayer;

typedef struct relu_layer {
    int in_width;
    int in_height;
    int in_depth;

    int out_width;
    int out_height;
    int out_depth;

}ReluLayer;

ConvLayer * make_conv_layer(int W, int H, int D,int K, int M, int S, int P);
ReluLayer * make_relu_layer(int W, int H, int D);

void convLayer_forward(float* restrict X,ConvLayer * l,float* restrict Y);
void relu_forward(float* restrict X,ReluLayer * l,float * restrict Y);


#endif