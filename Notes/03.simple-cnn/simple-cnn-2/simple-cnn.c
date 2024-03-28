#include <stdio.h>
#include <stdlib.h>

#include "layers.h"

int load_data(int n,int m,float *data_array, char * file_name){
    printf("Loading Data...\n");
    FILE * fp;
    fp=fopen(file_name,"r");
    if(fp==NULL){
        printf("Error opening file!\n");
        return 1;
    }

    int number;
    for(int i=0;i<n*n*m;i++){
        fscanf(fp,"%d",&number);
        data_array[i]=number;
        // printf("%d ",number);
    }
    // printf(".\n");

fclose(fp);
return 0;

}


void convLayer_forward(int N,int C, float* X,int M, int K, float* Weights,float *bias, int N_out,float* Y,int S,int P) {
// void convLayer_forward(float* X, ConvLayer *l, float* Y) {

    for(int m=0;m<M;m++){
        int x_j=-P;
        for(int j=0;j<N_out;j++, x_j+=S){
            int x_i=-P;
            for(int i=0;i<N_out;i++,x_i+=S){
                int y_idx=i+(N_out*j)+ (N_out*N_out)*m;
                Y[y_idx]=0.0;
                // float sum=0.f;
                for(int c=0;c<C;c++){
                    for(int f_j=0;f_j<K;f_j++){
                        for(int f_i=0;f_i<K;f_i++){
                            int f_idx=m*(K*K*C)+f_i+(f_j*K)+c*(K*K);
                            if((x_j+f_j)>=0&&(x_i+f_i)>=0 && (x_j+f_j)<N&&(x_i+f_i)<N){
                                int x_idx= c*N*N+(x_j+f_j)*N+(x_i+f_i);                            
                                Y[y_idx]+=Weights[f_idx]*X[x_idx];
                            // printf("Y:%d W:%d ",y_idx,f_idx);
                            // printf("X:%d\n",x_idx);
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

void print_map(int n,int m,float *x){

    for(int k=0;k<m;k++){
            for(int j=0;j<n;j++){
                for(int i=0;i<n;i++){
                    int idx=i+(n*j)+(n*n)*k;
                    printf("%2.f ",x[idx]);
                }
                putchar('\n');
            }
            putchar('\n');
        }
        //putchar('\n');
}

int main() {
    float *Input = malloc(sizeof(float)*C_in*N_in*N_in);
    if (Input == NULL) {
        printf("Memory allocation failed for Input\n");
        return 1;
    }

    load_data(N_in,C_in,Input,"../data/input.txt");
    // print_map(N_in,C_in,Input[0]);

    
    float * filters1=(float *)malloc(sizeof(float)*M1*C_in*K1*K1);
    if (filters1 == NULL) {
        printf("Memory allocation failed for filters1\n");
        return 1;
    }
    load_data(K1,M1*C_in,filters1,"../data/weights.txt");
    // print_map(K1,M1*C_in,filters1);
    float * bias1=(float *)malloc(sizeof(float)*M1);
    bias1[0]=1;
    bias1[1]=0;

    float * O1=(float *)malloc(sizeof(float)*M1*N1*N1);
    if (O1 == NULL) {
        printf("Memory allocation failed for O1\n");
        return 1;
    }
    printf("Conv: X[%d][%d][%d],W[%d][%d][%d],Y[%d][%d][%d]\n",
                    N_in,N_in,C_in,K1,K1,C_in,N1,N1,M1);
    convLayer_forward(N_in,C_in,Input,M1,K1,filters1,bias1,N1,O1,S1,P1);

    print_map(N1,M1,O1);



    

    free(Input);
    free(filters1);
    free(O1);
    return 0;
}
