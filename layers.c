
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


#include "layers.h"



//W: input Width, H: input height, D: input depth, K: filter width and height
// M: output feature maps, S: stride, P: zerro padding
Conv_Layer * make_conv_layer(int W, int H, int D,int K, int M, int S, int P){
    
    Conv_Layer *layer=malloc(sizeof(Conv_Layer));
#pragma acc enter data create(layer[0:1])

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

    int size = K*K*M*D;
    layer->weights=malloc(sizeof(float)*size);
#pragma acc enter data create(layer->weights[0:size])

    layer->bias=malloc(sizeof(float)*M);
#pragma acc enter data create(layer->bias[0:M])

#pragma acc update device(layer[0:1])
//Test1: Add 1 to all Conv parameters on host, and load corrext data from device
/*
printf("Conv:(%d,%d,%d)->(%d,%d,%d)\n\tFilters:(%d,%d)x%d s:%d,p:%d\n",
    layer->in_width,layer->in_height,layer->in_depth,layer->out_width,layer->out_height,layer->out_depth,
    layer->filter_width,layer->filter_height,layer->num_filters,layer->stride,layer->padding);

    layer->in_width++;layer->in_height++;layer->in_depth++;layer->out_width++;layer->out_height++;layer->out_depth++;
    layer->filter_width++;layer->filter_height++;layer->num_filters++;layer->stride++;layer->padding++;
#pragma acc update self(layer[0:1])
printf("After\n Conv:(%d,%d,%d)->(%d,%d,%d)\n\tFilters:(%d,%d)x%d s:%d,p:%d\n",
    layer->in_width,layer->in_height,layer->in_depth,layer->out_width,layer->out_height,layer->out_depth,
    layer->filter_width,layer->filter_height,layer->num_filters,layer->stride,layer->padding);
*/
//Test1^    
    return layer;
}

void free_conv(Conv_Layer * l){
    int size = l->in_depth*l->filter_height*l->filter_width*l->num_filters;
#pragma acc exit data delete(l->bias[0:l->out_depth])
    free(l->bias);
#pragma acc exit data delete(l->weights[0:size])
    free(l->weights);
#pragma acc exit data delete(l[0:1])
    free(l);
}

void conv_forward(float* restrict X,Conv_Layer * l,float* restrict Y) {
    
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

ReLU_Layer * make_relu_layer(int W, int H, int D){
    ReLU_Layer * layer=malloc(sizeof(ReLU_Layer));

    layer->in_width=W;
    layer->in_height=H;
    layer->in_depth=D;

    layer->out_width=W;
    layer->out_height=H;
    layer->out_depth=D;

    return layer;
}

void relu_forward(float* restrict X,ReLU_Layer * l,float * restrict Y){

    int size = l->out_depth*l->in_height*l->in_width;
    for(int i=0;i<size;i++){
        Y[i]=(X[i]<0.0f) ? 0.0f : X[i];
    }
}

Pool_Layer * make_pool_layer(int W, int H, int D,int K, int S, int P){
    Pool_Layer * layer = malloc(sizeof(Pool_Layer));

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

void pool_forward(float * restrict X, Pool_Layer * l,float * restrict Y){
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

FC_Layer   * make_fc_layer(int W, int H, int D,int num_neurons){
    FC_Layer * layer = malloc(sizeof(FC_Layer));

    layer->in_neurons = W*H*D;
    layer->in_width=W;
    layer->in_height=H;
    layer->in_depth=D;

    layer->out_width=1;
    layer->out_height=1;
    layer->out_depth = num_neurons;

    layer->weights = (float *) malloc(sizeof(float)*layer->in_neurons*layer->out_depth);
    layer->bias    = (float *) malloc(sizeof(float)*layer->out_depth);

    return layer;
}

void fc_forward(float * restrict X, FC_Layer * l,float * restrict Y){

    for(int i = 0; i < l->out_depth;i++) {
            float dot = 0.0f;
            for(int j = 0; j < l->in_neurons; j++) {
                int w_idx= j+ i*l->in_neurons;
                dot += X[j]*l->weights[w_idx];
            }
            dot += l->bias[i];
            Y[i] = dot;
        }

}

int load_conv(Conv_Layer* l ,char * file_name){
    
    int filter_width, filter_height, depth, filters;
    
    FILE *fin = fopen(file_name, "r");
    if (fin == NULL) {
        printf("Error opening conv_layer file!\n");
        return 1;
    }

    fscanf(fin, "%d %d %d %d", &filter_width, &filter_height, &depth, &filters);

    assert(filter_width==l->filter_width);
    assert(filter_height==l->filter_height);
    assert(depth==l->in_depth);
    assert(filters==l->num_filters);

    double val;
    for(int f = 0; f < filters; f++) {
        for (int i = 0; i < filter_width; i++) {
            for (int j = 0; j < filter_height; j++) {
                for (int d = 0; d < depth; d++) {
                    fscanf(fin, "%lf", &val);
                    int idx=i+j*filter_width+(d+f*depth)*(filter_width*filter_height);
                    l->weights[idx]=(float)val;
                }
            }
        }

    }

    for(int d = 0; d < filters; d++) {
        fscanf(fin, "%lf", &val);
        int idx=d;
        l->bias[idx]=(float)val;
    }

    fclose(fin);
    
    return 0;
}

int load_fc(FC_Layer *l, const char *filename) {
    
    FILE *fin = fopen(filename, "r");
    if (fin == NULL) {
        printf("Error opening fc_layer file!\n");
        return 1;
    }

    int num_inputs;
    int output_depth;
    fscanf(fin, "%d %d", &num_inputs, &output_depth);
    assert(output_depth == l->out_depth);
    assert(num_inputs == l->in_neurons);

    double val;
    for(int i = 0; i < l->out_depth; i++){  
        for(int h=0;h<l->in_height;h++){
            for(int w=0;w<l->in_width;w++){
                for(int d=0;d<l->in_depth;d++){
                    int idx = w+(h+d*l->in_height)*l->in_width+i*l->in_neurons;
                    fscanf(fin, "%lf", &val);
                    l->weights[idx]=(float)val;
        }}}
    }
    for(int i = 0; i < l->out_depth; i++) {
        fscanf(fin, "%lf", &val);
        l->bias[i]=(float)val;
    }

    fclose(fin);

    return 0;
}

Softmax_Layer * make_softmax_layer(int W, int H, int D){

    Softmax_Layer * layer = malloc(sizeof(Softmax_Layer));
    layer->in_width = W;
    layer->in_height = H;
    layer->in_depth = D;

    layer->out_width = 1;
    layer->out_height = 1;
    layer->out_depth = H*W*D;

    layer->likelihoods = (float*) malloc(sizeof(float)*layer->out_depth);

    return layer;
}

void softmax_forward(float * restrict X, Softmax_Layer * l,float * restrict Y){

    // Compute max activation
    float amax = X[0]; 
    for(int i = 1; i < l->out_depth; i++) {
        if (X[i] > amax) {
            amax = X[i];
        }
    }

    // Compute exponentials and total
    float total = 0.0f;
    for(int i = 0; i < l->out_depth; i++) {
        float e = exp(X[i] - amax);
        total += e;
        l->likelihoods[i] = e;
    }

    // Normalize and output to sum to one
    for(int i = 0; i < l->out_depth; i++) {
        Y[i] = l->likelihoods[i] / total;

    }

}