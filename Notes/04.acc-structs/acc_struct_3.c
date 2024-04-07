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


int main(){

    float * base = malloc(sizeof(float)*SIZE);
    
    point * P = malloc_points(SIZE);

    init_base(base);
    // move_to_device(P);
    #pragma acc enter data copyin(base[0:SIZE])
    #pragma acc enter data create(P[0:1])
    #pragma acc enter data create(P->x[0:P->n],P->y[0:P->n],P->z[0:P->n])
    #pragma acc update device(P->n)
    
    // #pragma acc parallel loop present(P[0:1],P->x[0:P->n],P->y[0:P->n],P->z[0:P->n]) present(base[0:SIZE])
    // #pragma acc parallel loop present(base[0:SIZE]) present(P->n) present(P->x[:P->n],P->y[0:P->n],P->z[0:P->n])
    // #pragma acc parallel loop present(base[0:SIZE]) 
    // for(int i=0 ; i<P->n ; i++){
    //     P->x[i] = base[i];
    //     P->y[i] = sqrtf(base[i]);
    //     P->z[i] = 0;
    // }
    vecaddgpu(P,base);
    // move_from_device(P);
#pragma acc update self(base[0:SIZE],P->x[:P->n],P->y[0:P->n],P->z[0:P->n])
    // print_arr(P->n,base);
    print_points(P);

    // #pragma acc exit data delete(P->x[P->n],P->y[P->n],P->z[P->n])
    // #pragma acc exit data delete(P[0:1])
    
    

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
    for(int i=0;i<A->n;i++){
        printf("%.2f %.2f %.2f \n",A->x[i],A->y[i],A->z[i]);
    }

}

point * malloc_points(int size){
    point * A = malloc(sizeof(point));
    A->n = size;
    printf("%d\n",A->n);
    A->x = malloc(sizeof(float)*A->n);
    A->y = malloc(sizeof(float)*A->n);
    A->z = malloc(sizeof(float)*A->n);

    // for(int i=0;i < A->n ;i++){
    //     A->x[i]=0;
    //     A->y[i]=0;
    //     A->z[i]=0;
    // }
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
    #pragma acc enter data create(A[0:1])
    #pragma acc enter data create(A->x[A->n],A->y[A->n],A->z[A->n])

    #pragma acc update device(A->n)
}

void move_from_device(point *A){
    #pragma acc exit data copyout(A->x[A->n],A->y[A->n],A->z[A->n])
    #pragma acc exit data delete(A[0:1])
}

void vecaddgpu(point *A, float* base){
// #pragma acc parallel loop copyin(A[0:1]) copyout(A->x[0:A->n],A->y[0:A->n],A->z[0:A->n]) copyin(base[0:A->n])
#pragma acc parallel loop present(A) present(base[0:A->n])
    for(int i=0 ; i<A->n ; i++){
        A->x[i] = base[i];
        A->y[i] = sqrtf(base[i]);
        A->z[i] = 0;
    }
}