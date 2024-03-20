#include <stdio.h>
#include <stdlib.h>


#define NUM_IMAGES 4//Number of Input Data
#define IMAGE_PIXELS 3 //

// 1
// int load_data( float (*image)[IMAGE_PIXELS], int N) {
// 2
int load_data(float **image, int N) {

    float counter =1.0;
    for (int i=0;i<N;i++){
        for (int j=0;j<IMAGE_PIXELS;j++){
            image[i][j]=counter++;
    }}
    return 0;
}

int print_addr(int N, int M, float (*arr)[M]){
    printf("Addresses of input[i]:\n");

    for (int i=0;i<N;i+=1){
            printf("%p ",&arr[i]);
    }
putchar('\n');
printf("Addresses of input[i][j]:\n");

    for (int i=0;i<N;i+=1){
        for (int j=0;j<IMAGE_PIXELS;j+=1){
            printf("%p ",&arr[i][j]);
    }putchar('\n');}
    return 0;

}

int print_address(float **arr, int N, int M){
    printf("Addresses of input[i]:\n");

    for (int i=0;i<N;i+=1){
            printf("%p ",&arr[i]);
    }
putchar('\n');
printf("Addresses of input[i][j]:\n");

    for (int i=0;i<N;i+=1){
        for (int j=0;j<IMAGE_PIXELS;j+=1){
            printf("%p ",&arr[i][j]);
    }putchar('\n');}

    return 0;
}

int main(){
    int N = NUM_IMAGES;

//**************************************************************
// 1
printf("\n1) Allocating (*input)[PIXELS]:\n");
    float (*input)[IMAGE_PIXELS]=malloc(sizeof(*input)*N);
printf(" (*input):%ld bytes (float):%ld bytes \n", sizeof(*input), sizeof(float));

print_addr(N,IMAGE_PIXELS, input);

free(input);

//**************************************************************
// 2
printf("\n2) Allocating (**input)-input[i]:\n");

    float **input2=(float **)malloc(sizeof(float*)*N);

    for (int i=0;i<N;i++){
        input2[i] = (float *)malloc(sizeof(float)*IMAGE_PIXELS);
    }

print_address(input2,N,IMAGE_PIXELS);

//**************************************************************
// 3
printf("\n3) Allocating (**input)-input[0]:\n");

float **input3=(float **)malloc(sizeof(float*)*N);
    input3[0] = malloc(IMAGE_PIXELS*N*sizeof(float));

    for (int i=1;i<N;i++){
        input3[i] = input3[i-1]+IMAGE_PIXELS;
    }


print_address(input3,N,IMAGE_PIXELS);

free(input3[0]);
free(input3);

//**************************************************************
// 4
printf("\n4) Allocating (**input),input[0] one allocation:\n");

float **input4=(float **)malloc(sizeof(float*)*N+N*IMAGE_PIXELS*sizeof(float));
    input4[0] = (float *)(input4 + N);

    for (int i=1;i<N;i++){
        input4[i] = input4[i-1]+IMAGE_PIXELS;
    }

print_address(input4,N,IMAGE_PIXELS);
//---        
    load_data(input4,N);

    putchar('\n');
    for (int i=0;i<N;i++){
        for (int j=0;j<IMAGE_PIXELS;j++){
            printf("%5.2f ",input4[i][j]);
    }putchar('\n');}

free(input4);



    printf(">END!\n");

    return 0;
}