#ifndef LAYERS_H
#define LAYERS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

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
void free_relu(ReLU_Layer * l);
void free_pool(Pool_Layer * l);
void free_fc(FC_Layer * l);
void free_softmax(Softmax_Layer * l);

void conv_forward(float* restrict X, Conv_Layer * l,float* restrict Y);
void relu_forward(float* restrict X, ReLU_Layer * l,float * restrict Y);
void pool_forward(float * restrict X, Pool_Layer * l,float * restrict Y);
void fc_forward(float * restrict X, FC_Layer * l,float * restrict Y);
void softmax_forward(float * restrict X, Softmax_Layer * l,float * restrict Y);

int load_conv(Conv_Layer* l ,char * file_name);
int load_fc(FC_Layer *l, const char *filename);


#endif