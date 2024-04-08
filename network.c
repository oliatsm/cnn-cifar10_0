#include "network.h"

Network * make_network(){
    Network *net = malloc(sizeof(Network));
    net->L1 = make_conv_layer(N_in,N_in,C_in,K1,M1,S1,P1);
    net->L2 = make_relu_layer(net->L1->out_width,net->L1->out_height,net->L1->out_depth);
    net->L3 = make_pool_layer(net->L2->out_width,net->L2->out_height,net->L2->out_depth,K3,S3,P3);
    net->L4 = make_conv_layer(net->L3->out_width,net->L3->out_height,net->L3->out_depth,K4,M4,S4,P4);
    net->L5 = make_relu_layer(net->L4->out_width,net->L4->out_height,net->L4->out_depth);
    net->L6 = make_pool_layer(net->L5->out_width,net->L5->out_height,net->L5->out_depth,K6,S6,P6);
    net->L7 = make_conv_layer(net->L6->out_width,net->L6->out_height,net->L6->out_depth,K7,M7,S7,P7);
    net->L8 = make_relu_layer(net->L7->out_width,net->L7->out_height,net->L7->out_depth);
    net->L9 = make_pool_layer(net->L8->out_width,net->L8->out_height,net->L8->out_depth,K9,S9,P9);
    net->L10 = make_fc_layer(net->L9->out_width,net->L9->out_height,net->L9->out_depth,M10);
    net->L11 = make_softmax_layer(net->L10->out_width,net->L10->out_height,net->L10->out_depth);

    return net;
}

void free_network(Network * net){
    free_softmax(net->L11);
    free_fc(net->L10);

    free_pool(net->L9);
    free_relu(net->L8);
    free_conv(net->L7);

    free_pool(net->L6);
    free_relu(net->L5);
    free_conv(net->L4);

    free_pool(net->L3);
    free_relu(net->L2);
    free_conv(net->L1);

    free(net);
}

float ** allocate_outputs(Network * net){
    float **out = malloc(sizeof(float*)*NUM_LAYERS-1);

        out[0] = malloc(sizeof(float)*net->L1->out_width*net->L1->out_height*net->L1->out_depth);
#pragma acc enter data create(out[0][0:net->L1->out_width*net->L1->out_height*net->L1->out_depth])
    out[1] = malloc(sizeof(float)*net->L2->out_width*net->L2->out_height*net->L2->out_depth);
#pragma acc enter data create(out[1][0:net->L2->out_width*net->L2->out_height*net->L2->out_depth])
    out[2] = malloc(sizeof(float)*net->L3->out_width*net->L3->out_height*net->L3->out_depth);
#pragma acc enter data create(out[2][0:net->L3->out_width*net->L3->out_height*net->L3->out_depth])
    out[3] = malloc(sizeof(float)*net->L4->out_width*net->L4->out_height*net->L4->out_depth);
#pragma acc enter data create(out[3][0:net->L4->out_width*net->L4->out_height*net->L4->out_depth])
    out[4] = malloc(sizeof(float)*net->L5->out_width*net->L5->out_height*net->L5->out_depth);
#pragma acc enter data create(out[4][0:net->L5->out_width*net->L5->out_height*net->L5->out_depth])
    out[5] = malloc(sizeof(float)*net->L6->out_width*net->L6->out_height*net->L6->out_depth);
#pragma acc enter data create(out[5][0:net->L6->out_width*net->L6->out_height*net->L6->out_depth])
    out[6] = malloc(sizeof(float)*net->L7->out_width*net->L7->out_height*net->L7->out_depth);
#pragma acc enter data create(out[6][0:net->L7->out_width*net->L7->out_height*net->L7->out_depth])
    out[7] = malloc(sizeof(float)*net->L8->out_width*net->L8->out_height*net->L8->out_depth);
#pragma acc enter data create(out[7][0:net->L8->out_width*net->L8->out_height*net->L8->out_depth])
    out[8] = malloc(sizeof(float)*net->L9->out_width*net->L9->out_height*net->L9->out_depth);
#pragma acc enter data create(out[8][0:net->L9->out_width*net->L9->out_height*net->L9->out_depth])
    out[9] = malloc(sizeof(float)*net->L10->out_depth*net->L10->in_neurons);
#pragma acc enter data create(out[9][0:net->L10->out_width*net->L10->out_height*net->L10->out_depth])
//     out[10] = malloc(sizeof(float)*net->L11->out_depth);
// #pragma acc enter data create(out[10][0:NUM_IMAGES][0:net->L11->out_depth])

    return out;
}

void free_outputs(float **out,Network *net){

    // #pragma acc exit data delete(O[10][0:NUM_IMAGES][0:net->L11->out_depth])
    // free(out[10]);
#pragma acc exit data delete(out[9]0[0:net->L10->out_width*net->L10->out_height*net->L10->out_depth])
    free(out[9]);
#pragma acc exit data delete(out[8][0:net->L9->out_width*net->L9->out_height*net->L9->out_depth])
    free(out[8]);
#pragma acc exit data delete(out[7][0:net->L8->out_width*net->L8->out_height*net->L8->out_depth])    
    free(out[7]);
#pragma acc exit data delete(out[6][0:net->L7->out_width*net->L7->out_height*net->L7->out_depth])
    free(out[6]);
#pragma acc exit data delete(out[5][0:net->L6->out_width*net->L6->out_height*net->L6->out_depth])   
    free(out[5]);    
#pragma acc exit data delete(out[4][0:net->L5->out_width*net->L5->out_height*net->L5->out_depth])
    free(out[4]);
#pragma acc exit data delete(out[3][0:net->L4->out_width*net->L4->out_height*net->L4->out_depth])
    free(out[3]);
#pragma acc exit data delete(out[2][0:net->L3->out_width*net->L3->out_height*net->L3->out_depth])
    free(out[2]);
#pragma acc exit data delete(out[1][0:net->L2->out_width*net->L2->out_height*net->L2->out_depth])    
    free(out[1]);
#pragma acc exit data delete(out[0][0:net->L1->out_width*net->L1->out_height*net->L1->out_depth])
    free(out[0]);

}