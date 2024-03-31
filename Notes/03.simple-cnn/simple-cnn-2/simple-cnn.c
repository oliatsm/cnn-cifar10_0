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
    }

    fclose(fp);
    return 0;
}

int load_input(int n,int m,float **data_array, char * file_name){
    printf("Loading Data...\n");
    // FILE * fp;
    // fp=fopen(file_name,"r");
    // if(fp==NULL){
    //     printf("Error opening file!\n");
    //     return 1;
    // }

    for(int img=0;img<NUM_IMG;img++){
        // int number;        
        for(int i=0;i<n*n*m;i++){
            // fscanf(fp,"%d",&number);
            // data_array[img][i]=number;
            // printf("%d ",number);
            // printf("(%d) %d\n",img,i);
            data_array[img][i]=rand()%3;
        }
    }
// fclose(fp);
return 0;

}


void print_map(int n,int m,float *x){

    for(int k=0;k<m;k++){
            for(int j=0;j<n;j++){
                for(int i=0;i<n;i++){
                    int idx=i+(n*j)+(n*n)*k;
                    printf("%.0f ",x[idx]);
                }
                putchar('\n');
            }
            putchar('\n');
        }
        putchar('\n');
}

int main() {
    float **Input = (float **)malloc(sizeof(float*)*NUM_IMG+sizeof(float)*(C_in*N_in*N_in)*NUM_IMG);
    if (Input == NULL) {
        printf("Memory allocation failed for Input\n");
        return 1;
    }

    Input[0]=(float *)(Input+NUM_IMG);
    for(int i=1;i<NUM_IMG;i++){
        Input[i]=Input[i-1]+(C_in*N_in*N_in);
    }

    load_input(N_in,C_in,Input,"../data/input.txt");
    

    float * filters1=(float *)malloc(sizeof(float)*M1*C_in*K1*K1);
    if (filters1 == NULL) {
        printf("Memory allocation failed for filters1\n");
        return 1;
    }
    load_data(K1,M1*C_in,filters1,"../data/weights.txt");

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
    

for(int i=0;i<NUM_IMG;i++){
    printf("O1:\n");
    print_map(N_in,C_in,Input[i]);
    printf("\n");

    convLayer_forward(N_in,C_in,Input[i],M1,K1,filters1,bias1,N1,O1,S1,P1);
    printf("O1:\n");
    print_map(N1,M1,O1);
    printf("\n");
}

    free(Input);
    free(filters1);
    free(bias1);
    free(O1);

    return 0;
}
