
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "layers.h"



//W: input Width, H: input height, D: input depth, K: filter width and height
// M: output feature maps, S: stride, P: zerro padding
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

void convLayer_forward(float* restrict X,ConvLayer * l,float* restrict Y) {
    
    for(int m=0;m<l->out_depth;m++){
        int x_j=-l->padding;
        for(int j=0;j<l->out_height;j++, x_j+=l->stride){
            int x_i=-l->padding;
            for(int i=0;i<l->out_width;i++,x_i+=l->stride){
                int y_idx=i+(l->out_width*(j+m*l->out_height));
                // Y[y_idx]=0.0f;
                float sum = 0.0f;
                for(int c=0;c<l->in_depth;c++){
                    for(int f_j=0;f_j<l->filter_height;f_j++){
                        for(int f_i=0;f_i<l->filter_width;f_i++){
                            int f_idx=f_i+(f_j*l->filter_width)+(c+m*l->in_depth)*(l->filter_height*l->filter_width);
                            if((x_j+f_j)>=0&&(x_i+f_i)>=0 && (x_j+f_j)<l->in_height&&(x_i+f_i)<l->in_width){
                                int x_idx= c*l->in_height*l->in_width+(x_j+f_j)*l->in_width+(x_i+f_i);                            
                                sum+=l->weights[f_idx]*X[x_idx];
                            }
                        }
                    }
                }
                sum+=l->bias[m];
                Y[y_idx]=sum;
            }
        }
    }
}

ReluLayer * make_relu_layer(int W, int H, int D){
    ReluLayer * layer=malloc(sizeof(ReluLayer));

    layer->in_width=W;
    layer->in_height=H;
    layer->in_depth=D;

    layer->out_width=W;
    layer->out_height=H;
    layer->out_depth=D;

    return layer;
}

void relu_forward(float* restrict X,ReluLayer * l,float * restrict Y){

    int size = l->out_depth*l->in_height*l->in_width;
    for(int i=0;i<size;i++){
        Y[i]=(X[i]<0.0f) ? 0.0f : X[i];
    }
}

PoolLayer * make_pool_layer(int W, int H, int D,int K, int S, int P){
    PoolLayer * layer = malloc(sizeof(PoolLayer));

    layer->in_width=W;
    layer->in_height=H;
    layer->in_depth=D;

    layer->pool_width=K;

    layer->stride=S;
    layer->padding=P;

    layer->out_width=floor((W-K+2*P)/S+1);
    layer->out_height=floor((H-K+2*P)/S+1);
    layer->out_depth=D;

    return layer;
}

void pool_forward(float * restrict X, PoolLayer * l,float * restrict Y){
    for(int m=0;m<l->out_depth;m++){
        int x_j=-l->padding;
        for(int j=0;j<l->out_height;x_j+=l->stride,j++){
            int x_i=-l->padding;
            for(int i =0; i<l->out_width;x_i+=l->stride,i++){
                int y_idx = i+l->out_width*(j+m*l->out_height);
                float max = -INFINITY;
                for(int p_j=0;p_j<l->pool_width;p_j++){
                    for(int p_i=0;p_i<l->pool_width;p_i++){
                        int x_idx = (x_i+p_i) + ((x_j+p_j)+m*l->in_height)*l->in_width;
                        if((x_i+p_i)>=0&&(x_j+p_j)>=0&&(x_i+p_i)<l->in_width&&(x_j+p_j)<l->in_height){
                            if(X[x_idx]>max){
                                max=X[x_idx];
                            }
                        }
                    }
                }
                Y[y_idx]=max;
            }
        }
    }
}
