
#include <stdio.h>
#include <stdlib.h>

#include "layers.h"

void convLayer_forward(int N,int C, double* X,int M, int K, double* Weights,double *bias, int N_out,double* Y,int S,int P) {
// void convLayer_forward(double* X, ConvLayer *l, double* Y) {

    for(int m=0;m<M;m++){
        int x_j=-P;
        for(int j=0;j<N_out;j++, x_j+=S){
            int x_i=-P;
            for(int i=0;i<N_out;i++,x_i+=S){
                int y_idx=i+(N_out*j)+ (N_out*N_out)*m;
                Y[y_idx]=0.0;
                // double sum=0.f;
                for(int c=0;c<C;c++){
                    for(int f_j=0;f_j<K;f_j++){
                        for(int f_i=0;f_i<K;f_i++){
                            int f_idx=m*(K*K*C)+f_i+(f_j*K)+c*(K*K);
                            if((x_j+f_j)>=0&&(x_i+f_i)>=0 && (x_j+f_j)<N&&(x_i+f_i)<N){
                                int x_idx= c*N*N+(x_j+f_j)*N+(x_i+f_i);                            
                                Y[y_idx]+=Weights[f_idx]*X[x_idx];
                            printf("Y:%d W:%d ",y_idx,f_idx);
                            printf("X:%d\n",x_idx);
                            printf("%0.f*%0.f=%0.f\n",Weights[f_idx],X[x_idx],Y[y_idx]);
                            }
                        }
                    }
                }
                // Y[y_idx]=sum;
                Y[y_idx]+=bias[m];
            }
        }
    }
}
