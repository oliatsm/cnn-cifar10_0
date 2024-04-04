#include <stdio.h>
#include <stdlib.h>

#include "layers.h"

int load_data(float *data_array, int size, char * file_name){

    FILE * fp;
    fp=fopen(file_name,"r");
    if(fp==NULL){
        printf("Error opening file!\n");
        return 1;
    }

    int number;
    
    for(int i=0;i<size;i++){
        fscanf(fp,"%d",&number);
        data_array[i]=number;
    }

    fclose(fp);
    return 0;
}


void print_map(float * x, int W, int H, int D ){

    for(int k=0;k<D;k++){
        for(int j=0;j<H;j++){
            for(int i=0;i<W;i++){
                int indx=(j*H)+i+(W*H)*k;
                printf("%2.f ",x[indx]);
            }
        putchar('\n');
        }
    putchar('\n');
    }
}

int main() {

    float *Input = (float *)malloc(sizeof(float)*(C_in*N_in*N_in));
    if (Input == NULL) {
        printf("Memory allocation failed for Input\n");
        return 1;
    }

    load_data(Input,N_in*N_in*C_in,"./data/input.txt");
    

    // float * filters1=(float *)malloc(sizeof(float)*M1*C_in*K1*K1);
    // if (filters1 == NULL) {
    //     printf("Memory allocation failed for filters1\n");
    //     return 1;
    // }
    // load_data(K1,M1*C_in,filters1,"../data/weights.txt");

    // float * bias1=(float *)malloc(sizeof(float)*M1);
    // bias1[0]=1;
    // bias1[1]=0;
    ConvLayer * L1 =make_conv_layer(N_in,N_in,C_in,K1,M1,S1,P1);
        load_data(L1->weights,K1*K1*M1*C_in,"./data/weights.txt");
    L1->bias[0]=1;
    L1->bias[1]=0;

    float * O1=(float *)malloc(sizeof(float)*L1->out_height*L1->out_width*L1->out_depth);
    if (O1 == NULL) {
        printf("Memory allocation failed for O1\n");
        return 1;
    }
    // printf("Conv: X[%d][%d][%d],W[%d][%d][%d],Y[%d][%d][%d]\n",
    //                 N_in,N_in,C_in,K1,K1,C_in,N1,N1,M1);

    PoolLayer *L2 =make_pool_layer(N_in,N_in,C_in,2,2,1);
    float * O2=(float *)malloc(sizeof(float)*L2->out_height*L2->out_width*L2->out_depth);

    
    

for(int i=0;i<NUM_IMG;i++){
    printf("O1:\n");
    print_map(Input,N_in,N_in,C_in);
    printf("\n");

    // convLayer_forward(Input,L1,O1);
    pool_forward(Input,L2,O2);
    printf("O1:\n");
    // print_map(O1,L1->out_width,L1->out_height,M1);
        print_map(O2,L2->out_width,L2->out_height,L2->out_depth);

    printf("\n");
}

    free(L2);
    free(L1->bias);
    free(L1->weights);
    free(L1);
    free(Input);
    free(O1);
    

    return 0;
}
