#include "tests.h"
void test1(float** input, int num, int pixels) {
#pragma acc parallel loop present(input[0:num][0:pixels])
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < pixels; j++) {
            input[i][j] += 1;
        }
    }
    // #pragma acc update self (input[0:num][0:pixels])

    for (int i = 0; i < num; i += 5000) {
        for (int j = 0; j < pixels; j += 100) {
            printf("%f\n", input[i][j]);
        }
    }
}


//Test2: Add 1 to all Conv parameters on host, and load correct data from device
void test2(Conv_Layer* l) {
    printf("L1:Conv:(%d,%d,%d)->(%d,%d,%d)\n\tFilters:(%d,%d)x%d s:%d,p:%d\n",
        l->in_width, l->in_height, l->in_depth, l->out_width, l->out_height, l->out_depth,
        l->filter_width, l->filter_height, l->num_filters, l->stride, l->padding);

    l->in_width++; l->in_height++; l->in_depth++; l->out_width++; l->out_height++; l->out_depth++;
    l->filter_width++; l->filter_height++; l->num_filters++; l->stride++; l->padding++;
#pragma acc update self(l->in_width,l->in_height,l->in_depth,l->out_width,l->out_height,l->out_depth,l->filter_width,l->filter_height,l->num_filters,l->stride,l->padding)
    printf("After\n Conv:(%d,%d,%d)->(%d,%d,%d)\n\tFilters:(%d,%d)x%d s:%d,p:%d\n",
        l->in_width, l->in_height, l->in_depth, l->out_width, l->out_height, l->out_depth,
        l->filter_width, l->filter_height, l->num_filters, l->stride, l->padding);
}
//Test2^  

//Test3: add 1 to Weights, then copy to the host
void test3(Conv_Layer* l, int size) {
    //present(l->weights[0:size],l->bias[0:l->out_depth])
#pragma acc parallel loop copyin(size) present(l)
    for (int i = 0; i < size; i++) {
        l->weights[i] += 1;
    }
#pragma acc update self(l->weights[0:size])
}
//Test3^

//Test4: Add 1 to all ReLU pparameters on device, and load data to host
void test4(ReLU_Layer* l) {

    printf("ReLU:(%d,%d,%d)->(%d,%d,%d)\n",
        l->in_width, l->in_height, l->in_depth, l->out_width, l->out_height, l->out_depth);
#pragma acc parallel loop present(l)
    for (int i = 0; i < 1; i++) {
        l->in_width++; l->in_height++; l->in_depth++; l->out_width++; l->out_height++; l->out_depth++;
    }
#pragma acc update self(l->in_width,l->in_height,l->in_depth,l->out_width,l->out_height,l->out_depth)
    printf("After\n ReLU:(%d,%d,%d)->(%d,%d,%d)\n",
        l->in_width, l->in_height, l->in_depth, l->out_width, l->out_height, l->out_depth);
}
//Test4^  

//Test5: Add 1 to all Pool parameters on device, and load data to host
void test5(Pool_Layer* l) {

    printf("Pooling:(%d,%d,%d)->(%d,%d,%d)\n",
        l->in_width, l->in_height, l->in_depth, l->out_width, l->out_height, l->out_depth);
#pragma acc parallel loop present(l)
    for (int i = 0; i < 1; i++) {
        l->in_width++; l->in_height++; l->in_depth++; l->out_width++; l->out_height++; l->out_depth++;
    }
#pragma acc update self(l->in_width,l->in_height,l->in_depth,l->out_width,l->out_height,l->out_depth)
    printf("After\n Pooling:(%d,%d,%d)->(%d,%d,%d)\n",
        l->in_width, l->in_height, l->in_depth, l->out_width, l->out_height, l->out_depth);
}
//Test5^  

//Test6: add 1 to Weights, then copy to the host
void test6(FC_Layer* l) {

    int size = l->in_neurons * l->out_depth;
    arr2txt(l->weights, 1, size, "FC-host.txt");
#pragma acc parallel loop copyin(size) present(l)
    for (int i = 0; i < size; i++) {
        l->weights[i] += 1;
    }
#pragma acc update self(l->weights[0:size])

    arr2txt(l->weights, 1, size, "FC-device.txt");
}
//Test6^

void test7(Softmax_Layer* l) {

#pragma acc parallel loop present(l)
    for (int i = 0; i < l->out_depth; i++) {
        l->likelihoods[i] = i;
    }
#pragma acc update self(l->likelihoods[0:l->out_depth])

    arr2txt(l->likelihoods, 1, l->out_depth, "L11-like-device.txt");

}

//Test8: Add 1 to all Softmax pparameters on device, and load data to host
void test8(Softmax_Layer* l) {

    printf("Softmax:(%d,%d,%d)->(%d,%d,%d)\n",
        l->in_width, l->in_height, l->in_depth, l->out_width, l->out_height, l->out_depth);
    // #pragma acc parallel loop present(l)
    for (int i = 0; i < 1; i++) {
        l->in_width++; l->in_height++; l->in_depth++; l->out_width++; l->out_height++; l->out_depth++;
    }
#pragma acc update self(l->in_width,l->in_height,l->in_depth,l->out_width,l->out_height,l->out_depth)
    printf("After\n Softmax:(%d,%d,%d)->(%d,%d,%d)\n",
        l->in_width, l->in_height, l->in_depth, l->out_width, l->out_height, l->out_depth);
}
//Test8^  

void test9(Conv_Layer* l, float* out) {

#pragma acc parallel loop present(l,out)
    for (int i = 0; i < (l->out_width * l->out_height * l->out_depth); i++) {
        out[i] = 0.0f;
        for (int j = 0; j < l->filter_width * l->filter_height; j++) {
            out[i] += l->weights[j];
        }
    }
#pragma acc update self(out[0:l->out_width*l->out_height*l->out_depth])
    arr2txt(out, 1, l->out_width * l->out_height * l->out_depth, "out7.txt");
}

void arr2txt(float* arr, int N, int M, char* file_name) {
    FILE* file = fopen(file_name, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d,%d,%d\n", N, N, M);
    for (int k = 0; k < M; ++k) {
        for (int j = 0; j < N; ++j) {
            for (int i = 0; i < N; ++i) {
                int idx = ((j * N) + i) + (N * N) * k;
                fprintf(file, "%f ", arr[idx]);
                // printf("%d\n",idx);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
}