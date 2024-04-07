#include "tests.h"
//Test2: Add 1 to all Conv parameters on host, and load corrext data from device
/*
printf("L1:Conv:(%d,%d,%d)->(%d,%d,%d)\n\tFilters:(%d,%d)x%d s:%d,p:%d\n",
    L1->in_width,L1->in_height,L1->in_depth,L1->out_width,L1->out_height,L1->out_depth,
    L1->filter_width,L1->filter_height,L1->num_filters,L1->stride,L1->padding);

    L1->in_width++;L1->in_height++;L1->in_depth++;L1->out_width++;L1->out_height++;L1->out_depth++;
    L1->filter_width++;L1->filter_height++;L1->num_filters++;L1->stride++;L1->padding++;
#pragma acc update self(L1->in_width,L1->in_height,L1->in_depth,L1->out_width,L1->out_height,L1->out_depth,L1->filter_width,L1->filter_height,L1->num_filters,L1->stride,L1->padding)
printf("After\n Conv:(%d,%d,%d)->(%d,%d,%d)\n\tFilters:(%d,%d)x%d s:%d,p:%d\n",
    L1->in_width,L1->in_height,L1->in_depth,L1->out_width,L1->out_height,L1->out_depth,
    L1->filter_width,L1->filter_height,L1->num_filters,L1->stride,L1->padding);
*/
//Test2^  

//Test2: Add 1 to all Conv parameters on host, and load corrext data from device
void test2(Conv_Layer * l){
printf("L1:Conv:(%d,%d,%d)->(%d,%d,%d)\n\tFilters:(%d,%d)x%d s:%d,p:%d\n",
    l->in_width,l->in_height,l->in_depth,l->out_width,l->out_height,l->out_depth,
    l->filter_width,l->filter_height,l->num_filters,l->stride,l->padding);

    l->in_width++;l->in_height++;l->in_depth++;l->out_width++;l->out_height++;l->out_depth++;
    l->filter_width++;l->filter_height++;l->num_filters++;l->stride++;l->padding++;
#pragma acc update self(l->in_width,l->in_height,l->in_depth,l->out_width,l->out_height,l->out_depth,l->filter_width,l->filter_height,l->num_filters,l->stride,l->padding)
printf("After\n Conv:(%d,%d,%d)->(%d,%d,%d)\n\tFilters:(%d,%d)x%d s:%d,p:%d\n",
    l->in_width,l->in_height,l->in_depth,l->out_width,l->out_height,l->out_depth,
    l->filter_width,l->filter_height,l->num_filters,l->stride,l->padding);
}
//Test2^  

//Test3: add 1 to Weights, then copy from the device the correct weights
void test3(Conv_Layer * l,int size){
#pragma acc parallel loop copyin(size) present(l->weights[0:size],l->bias[0:l->out_depth])
    for(int i=0;i<size;i++){
        l->weights[i]+=1;
    }
#pragma acc update self(l->weights[0:size])
}
//Test3^
