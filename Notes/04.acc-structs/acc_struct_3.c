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
void print_points(point *A);
point * malloc_points(int size);
void vecadd(point *A, float* base);
void vecaddgpu(point *A, float* base);
void move_to_device(point *A);
void move_from_device(point *A);
void free_point(point *A);


int main(){

    float *base = malloc(sizeof(float)*SIZE);
    init_base(base);
    #pragma acc enter data copyin(base[0:SIZE])
    
    point *P = malloc_points(SIZE);
    move_to_device(P);

    vecaddgpu(P,base);
    move_from_device(P);

    print_points(P);

    free_point(P);

    #pragma acc exit data delete(base[0:SIZE])
    free(base);

    return 0;
}

void init_base(float * base){

    for (int i=0;i<SIZE;i++){
        base[i] = (i+1)*(i+1);
    }
}

void print_arr(int size,float arr[size]){
    for(int i=0;i<size;i+=1){
        printf("%.2f\n",arr[i]);
    }

}

void print_points(point *A){
    for(int i=0;i<A->n;i+=100){
        printf("%.2f %.2f %.2f \n",A->x[i],A->y[i],A->z[i]);
    }

}

point * malloc_points(int size){
    point *A = malloc(sizeof(point));
    A->n = size;
    printf("%d\n",A->n);
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
    #pragma acc enter data create(A->x[0:A->n],A->y[0:A->n],A->z[0:A->n])

    // #pragma acc update device(A->n)
}

void move_from_device(point *A){
    #pragma acc exit data copyout(A->x[0:A->n],A->y[0:A->n],A->z[0:A->n])
    #pragma acc exit data delete(A[0:1])
}

void vecaddgpu(point *A, float* base){
#pragma acc parallel loop present(A) present(base[0:A->n])
    for(int i=0 ; i<A->n ; i++){
        A->x[i] = base[i];
        A->y[i] = sqrtf(base[i]);
        A->z[i] = 0;
    }
}

void free_point(point * A){
    free(A->x);
    free(A->y);
    free(A->z);
    free(A);

}