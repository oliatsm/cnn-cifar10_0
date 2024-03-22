#ifndef LAYERS_H
#define LAYERS_H

#include <stdio.h>

typedef struct {
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
}conv_layer;


#endif