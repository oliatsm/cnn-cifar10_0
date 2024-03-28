
#include <stdio.h>
#include <stdlib.h>

#include "layers.h"

ConvLayer * make_conv_layer(int W, int H, int D,int K, int M, int S, int P){
    
    ConvLayer *layer=malloc(sizeof(ConvLayer));

    layer->in_width=W;
    layer->in_height=H;
    layer->in_depth=D;

    layer->filter_width=K;
    layer->filter_height=K;
    layer->num_filters=M;

    layer->stride =S;
    layer->padding=P;

    layer->out_width=(W-K+2*P)/S+1;
    layer->out_height=(H-K+2*P)/S+1;
    layer->out_depth=M;

    layer->weights=malloc(sizeof(float)*K*K*M*D);
    for(int i=0;i<(K*K*M*D);i++){
        layer->weights[i]=0.f;
    }

    layer->bias=malloc(sizeof(float)*M);
    for(int i=0;i<(M);i++){
        layer->bias[i]=0.f;
    }
    
    return layer;
}

void print_conv_layer(ConvLayer * layer){

    printf("Input: %d,%d,%d \n",layer->in_width,layer->in_height,layer->in_depth);
    printf("Filters: (%d,%d)x%d , S:%d P:%d \n",layer->filter_width,layer->filter_height,layer->num_filters,
                        layer->stride,layer->padding);

    printf("Output: %d,%d,%d \n",layer->out_width,layer->out_height,layer->out_depth);

    for (int f=0;f<layer->num_filters;f++){
        printf("W%d:\n",f);
        for(int k=0;k<layer->in_depth;k++){
            for(int j=0;j<layer->filter_height;j++){
                for(int i=0;i<layer->filter_width;i++){
                    int indx=(j*layer->filter_height)+i+(layer->filter_width*layer->filter_height)*k+(layer->filter_height*layer->in_depth*layer->filter_width)*f;
                    printf("%2.f ",layer->weights[indx]);
                }
                putchar('\n');
            }
            putchar('\n');
        }
        //putchar('\n');
    }

}