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

