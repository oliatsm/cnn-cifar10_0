
#include <stdio.h>
#include <stdlib.h>

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
    printf("In[%d][%d][%d], Out[%d][%d][%d]\n",l->in_width,l->in_height,
                l->in_depth,l->out_width,l->out_height,l->out_depth);
    printf("Filter[%d][%d][%d] x%d, S:%d,P:%d\n",l->filter_height,l->filter_height,
                l->out_depth,l->num_filters,l->stride,l->padding);
    
    for(int m=0;m<l->out_depth;m++){ printf("M %d\n",m);
        int x_j=-l->padding;
        for(int j=0;j<l->out_height;j++, x_j+=l->stride){
            int x_i=-l->padding;
            for(int i=0;i<l->out_width;i++,x_i+=l->stride){
                int y_idx=i+(l->out_width*(j+m*l->out_height));

                float sum = 0.0f;
                for(int c=0;c<l->in_depth;c++){ //printf("c %d,m %d\n",c,m);
                    for(int f_j=0;f_j<l->filter_height;f_j++){
                        for(int f_i=0;f_i<l->filter_width;f_i++){
                            int f_idx=f_i+(f_j*l->filter_width)+(c+m*l->in_depth)*(l->filter_height*l->filter_width);
                            if((x_j+f_j)>=0&&(x_i+f_i)>=0 && (x_j+f_j)<l->in_height&&(x_i+f_i)<l->in_width){
                                int x_idx= c*(l->in_height*l->in_width)+(x_j+f_j)*l->in_width+(x_i+f_i);                            
                                sum+=l->weights[f_idx]*X[x_idx]; printf("f %d, X %d\n",f_idx,x_idx);
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