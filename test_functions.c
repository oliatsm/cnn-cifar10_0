#include <stdio.h>
#include <stdlib.h>


void img2txt(float **image, int *label, int N) {
    FILE *file = fopen("image.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int n = 0; n < N; n+=5000) {
        // fprintf(file, "%d: %d \n",n,label[n]);
        for (int k = 0; k < 3; ++k) {
            for (int j = 0; j < 32; ++j) {
                for (int i = 0; i < 32; ++i) {
                    fprintf(file, "%.4f ", image[n][((j*32)+i)+1024*k]);
                }
                fprintf(file, "\n");
            }
        }
    }

    fclose(file);
}

void arr2txt(float *arr, int N,int M, char * file_name) {
    FILE *file = fopen(file_name, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file,"%d,%d,%d\n",N,N,M);
    for (int k = 0; k < M; ++k) {
        for (int j = 0; j < N; ++j) {
            for (int i = 0; i < N; ++i) {
                int idx = ((j*N)+i)+(N*N)*k;
                fprintf(file, "%f ", arr[idx]);
                // printf("%d\n",idx);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

int load_weights(float * w,float * b ,char * file_name){
    printf("Loading Conv Layer 1 Weights\n %dx(%d,%d,%d)\n",M1,K1,K1,C_in);

    int filter_width, filter_height, depth, filters;
    
    FILE *fin = fopen(file_name, "r");
    if (fin == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fscanf(fin, "%d %d %d %d", &filter_width, &filter_height, &depth, &filters);
    printf("%d %d %d %d\n", filter_width, filter_height, depth, filters);
    assert(filter_width==K1);
    assert(filter_height==K1);
    assert(depth==C_in);
    assert(filters==M1);

    double val;
    for(int f = 0; f < filters; f++) {
        for (int i = 0; i < filter_width; i++) {
            for (int j = 0; j < filter_height; j++) {
                for (int d = 0; d < depth; d++) {
                    fscanf(fin, "%lf", &val);
                    int idx=i+j*K1+(d+f*C_in)*(K1*K1);
                    w[idx]=(float)val;
                    // printf("%d, %lf->%f\n",idx,val,w[idx]);
                }
            }
        }

    }

    for(int d = 0; d < M1; d++) {
        fscanf(fin, "%lf", &val);
        int idx=d;
        b[idx]=(float)val;
        // printf("%d\n",idx);
    }

    fclose(fin);
    
    return 0;
}

void print_map(int n,int m,int f,float *x){

    for(int l=0;l<f;l++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<m;k++){
                    int idx=i+(n*j)+(n*n)*k+(n*n*m)*l;
                    printf("%f \n",x[idx]);
                }
                // putchar('\n');
            }
            // putchar('\n');
        }
        // putchar('\n');
    }
}
