#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <openacc.h>

#define SIZE 1000

typedef struct point_t{
    int n;
    float *x,*y,*z;
}point;


void init_base();
void print_arr(int size,float arr[size]);
point * malloc_points(int size);
void vecadd(point *A, float* base);
void vecaddgpu(point *A, float* base);
void move_to_device(point *A);
void move_from_device(point *A);


int main(){

    float * base = malloc(sizeof(float)*SIZE);
    
    point * P = malloc_points(SIZE);

    init_base(base);
    move_to_device(P);
    vecaddgpu(P,base);
    move_from_device(P);

    print_arr(P->n,P->y);
    

    return 0;
}

void init_base(float * base){

    for (int i=0;i<SIZE;i++){
        base[i] = (i+1)*(i+1);
    }
}

void print_arr(int size,float arr[size]){
    printf("Print...\n");
    for(int i=0;i<size;i+=1){
        printf("%.2f\n",arr[i]);
    }

}
point * malloc_points(int size){
    point * A = malloc(sizeof(point));
    A->n = size;
    A->x = malloc(sizeof(float)*A->n);
    A->y = malloc(sizeof(float)*A->n);
    A->z = malloc(sizeof(float)*A->n);
    return A;
}
void vecadd(point *A, float* base){
    for(int i=0 ; i<A->n ; i++){
        A->x[i] = base[i];
        A->y[i] = sqrtf(base[i]);
        A->z[i] = 0;
    }
}

void move_to_device(point *A){
    #pragma acc enter data copyin(A[0:1])
    #pragma acc enter data create(A->x[A->n],A->y[A->n],A->z[A->n])
}

void move_from_device(point *A){
    #pragma acc exit data copyout(A->x[A->n],A->y[A->n],A->z[A->n])
    #pragma acc exit data delete(A[0:1])
}

void vecaddgpu(point *A, float* base){
// #pragma acc parallel loop copyin(A[0:1]) copyout(A->x[0:A->n],A->y[0:A->n],A->z[0:A->n]) copyin(base[0:A->n])
#pragma acc parallel loop present(A[0:1]) present(A->x[0:A->n],A->y[0:A->n],A->z[0:A->n]) copyin(base[0:A->n])
    for(int i=0 ; i<A->n ; i++){
        A->x[i] = base[i];
        A->y[i] = sqrtf(base[i]);
        A->z[i] = 0;
    }
}