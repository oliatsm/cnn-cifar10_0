#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <openacc.h>

typedef struct{
    int n;
    float *x, *y, *z;
}point;
void move_to_device( point *A );
void move_from_device( point* A );
void vecaddgpu( point *A, float* base );

point * init_point(int num_points);
void vecadd( point *A, float* base );
void dumpFile(point * A, char * file_name);

int main(){
    int size = 100;
    point * P = init_point(size);
    move_to_device(P);
    float * B = malloc(sizeof(float)*size);
    for(int i=0;i<size;i++){
        B[i]=(float)(i+1)*(i+1);
    }
#pragma acc enter data copyin(B[0:size])
    // vecaddgpu(P,B);
    // move_from_device(P);
    dumpFile(P,"output.txt");


    return 0;
}
void move_to_device( point *A ){
#pragma acc enter data copyin(A[0:1])
#pragma acc enter data create(A->x[0:A->n],A->y[0:A->n],A->z[0:A->n])
// A[0:1]
// A->x[0:A->n], A->y[0:A->n], A->z[0:A->n]
}
void move_from_device( point* A ){
#pragma acc enter data copyout(A->x[0:A->n],A->y[0:A->n],A->z[0:A->n])
#pragma acc enter data delete(A[0:1])
}

void vecaddgpu( point *A, float* base ){
#pragma acc parallel loop present(A[0:1]) present(A->x[0:A->n], A->y[0:A->n], A->z[0:A->n]) present(base[0:A->n])
    for( int i = 0; i < A->n; ++i ){
        A->x[i] = base[i];
        A->y[i] = sqrtf( base[i] );
        A->z[i] = 0;
    }
}

point * init_point(int num_points){

    point * A = malloc(sizeof(point));
    A->n=num_points;
    A->x=malloc(sizeof(float)*A->n);
    A->y=malloc(sizeof(float)*A->n);
    A->z=malloc(sizeof(float)*A->n);

    // for(int i=0;i<A->n;i++){
    //     A->x[i]=(i+1)*0.1;
    //     A->y[i]=(i+1)*1.0;
    //     A->z[i]=(i+1)*10.0;
    // }

    return A;
}

void vecadd( point *A, float* base ){
    for( int i = 0; i < A->n; ++i ){
        A->x[i] = base[i];
        A->y[i] = sqrtf( base[i] );
        A->z[i] = 0;
    }
}

void dumpFile(point * A, char * file_name) {
    FILE *file = fopen(file_name, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file,"x y z\n");
    for (int i = 0; i < A->n; ++i) {
        fprintf(file, "%.2f %.2f %.2f\n", A->x[i],A->y[i],A->z[i]);
    }
    
    fclose(file);
}