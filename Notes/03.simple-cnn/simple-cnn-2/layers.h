#ifndef LAYERS_H
#define LAYERS_H

#include <stdio.h>
// Input Data
#define NUM_IMG 6 //Number of images
#define N_in 5//Input Width-Height
#define C_in 3//Colour Chanels

//Layer 1 : Convolutional
#define K1 3 //Filter Width Height
#define S1 2 //Step
#define P1 1 //Padding
//Layer 1 Output
#define N1 (N_in-K1+2*P1)/S1+1 //Output Width-Height
#define M1 2 //Output number of Feature Maps 

void convLayer_forward(int N,int C, float* X,int M, int K, float* Weights,float *bias, int N_out,float* Y,int S,int P);

#endif