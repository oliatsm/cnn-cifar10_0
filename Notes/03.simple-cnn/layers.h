#ifndef LAYERS_H
#define LAYERS_H

#include <stdio.h>

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


ConvLayer * make_conv_layer(int W, int H, int D,int K, int M, int S, int P);
void print_conv_layer(ConvLayer * layer);


#endif