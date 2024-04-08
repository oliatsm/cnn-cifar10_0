#ifndef NETWORK_H
#define NETWORK_H

#include "layers.h"

// Input Data
#define N_in 32//Input Width-Height
#define C_in 3//Colour Chanels

//Layer 1 : Convolutional
#define K1 5 //Filter Width Height
#define S1 1 //Stride
#define P1 2 //Padding
#define M1 16 //Output number of Feature Maps 
//Layer 2 : ReLU (No parameters)
//Layer 3 : Pooling
#define K3 2
#define S3 2
#define P3 0

//Layer 4 : Convolutional
#define K4 5 //Filter Width Height
#define S4 1 //Stride
#define P4 2 //Padding
#define M4 20 //Output number of Feature Maps 
//Layer 5 : ReLU (No parameters)
//Layer 6 : Pooling
#define K6 2
#define S6 2
#define P6 0

//Layer 7 : Convolutional
#define K7 5 //Filter Width Height
#define S7 1 //Stride
#define P7 2 //Padding
#define M7 20 //Output number of Feature Maps 
//Layer 8 : ReLU (No parameters)
//Layer 9 : Pooling
#define K9 2
#define S9 2
#define P9 0

//Layer 10 : Fully Connected
#define M10 10 // Output Neurons

//Layer 11 : Softmax (No parameters)
typedef struct network{
    Conv_Layer *L1;
    ReLU_Layer *L2;
    Pool_Layer *L3;
    Conv_Layer *L4;
    ReLU_Layer *L5;
    Pool_Layer *L6;
    Conv_Layer *L7;
    ReLU_Layer *L8;
    Pool_Layer *L9;
    FC_Layer   *L10;
    Softmax_Layer *L11;
    
}Network;

Network * make_network();
void free_network(Network * net);

#endif