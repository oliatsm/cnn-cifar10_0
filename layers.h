#ifndef LAYERS_H
#define LAYERS_H

#include <stdio.h>
// Input Data
// #define NUM_IMG 2 //Number of images
#define N_in 32//Input Width-Height
#define C_in 3//Colour Chanels

//Layer 1 : Convolutional
// in[32][32][3],out[32][32][16]
//     Filters[5][5][3]x(16), stride:1,pad:2
#define K1 5 //Filter Width Height
#define S1 1 //Stride
#define P1 2 //Padding
//Layer 1 Output
#define N1 32//(N_in-K1+2*P1)/S1+1 //Output Width-Height
#define M1 16 //Output number of Feature Maps 

void convLayer_forward(int N,int C, float* X,int M, int K, float* Weights,float *bias, int N_out,float* Y,int S,int P);

#endif