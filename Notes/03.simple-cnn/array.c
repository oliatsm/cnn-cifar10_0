#include <stdio.h>

#define W 4
#define H 4
#define D 3
#define M 2
#define K 2

#define P 1
#define S 2


void fill_arr(int x[D][H][W]){//,int w[M][D][H][W]){
    for (int k=0;k<D;k++){
        for (int j=0;j<H;j++){
            for (int i=0;i<W;i++){
                x[k][j][i]=i+j*H+k*(W*H);

            }//printf("\n");
        }//printf("\n");
    }

}

void print_arr(int arr[D][H][W]){
    for (int k=0;k<D;k++){
        int x_j=-P;
        for (int j=0;j<H;j++){
            int x_i=-P;
            for (int i=0;i<W;i++){
                if((x_i>=-P)&&(x_j>=-P)&&(x_i<(W+P)&&(x_j<(H+P)))){
                // printf("Y(%d,%d) ",i,j);//%2d ",i,j,arr[k][j][i]);
                printf(">(%d,%d) \n",x_i,x_j);
                for (int p = 0; p < K; p++) { // KxK filter
                        for (int q = 0; q < K; q++) {
                            printf("(%d,%d)*(%d,%d) \n",q,p,x_i+q,p+x_j);
                        }
                    }
                x_i+=S;
            }}//printf("\n");
            x_j+=S;
        }//printf("\n");
    }
}

void print_gold(void){
    for (int k=0;k<D;k++){
        for (int j=-P;j<H+P;j+=S){
            for (int i=-P;i<W+P;i+=S){
                printf(">(%d,%d) \n",i,j);
                for (int p = 0; p < K; p++) { // KxK filter
                        for (int q = 0; q < K; q++) {
                            printf("(%d,%d)*(%d,%d) \n",q,p,i+q,p+j);
                        }
                    }
            }}//printf("\n");
        }//printf("\n");
    }



int main(){

    int X[D][H][W];
    int weights[M][D][K][K];

    print_gold();
    // fill_arr(X);
    printf("ARRAY\n");
    print_arr(X);

    return 0;

}