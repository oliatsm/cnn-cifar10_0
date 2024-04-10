#ifndef TESTS_H
#define TESTS_H
#include "layers.h"
void test1(float **input,int num,int pixels);
void test2(Conv_Layer * l);
void test3(Conv_Layer * l,int size);
void test4(ReLU_Layer * l);
void test5(Pool_Layer * l);
void test6(FC_Layer * l);
void test7(Softmax_Layer * l);
void test8(Softmax_Layer * l);
void test9(Conv_Layer *l, float * out);
void arr2txt(float *arr, int N,int M, char * file_name) ;

#endif