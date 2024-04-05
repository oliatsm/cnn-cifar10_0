# Φόρτωση των δεδομένων του struct conv_layer στην GPU
Δημιουργία θέσης μνήμης στη συσκευή για struct με μέλη pointers:

```c
Conv_Layer * make_conv_layer(int W, int H, int D,int K, int M, int S, int P){
    
    Conv_Layer *layer=malloc(sizeof(Conv_Layer));
#pragma acc enter data create(layer[0:1])

    layer->in_width=W;
    /* con_layer parameters...*/

    int size = K*K*M*D;
    layer->weights=malloc(sizeof(float)*size);
#pragma acc enter data create(layer->weights[0:size])

    layer->bias=malloc(sizeof(float)*M);
#pragma acc enter data create(layer->bias[0:M])

#pragma acc update device(layer[0:1])
    return layer;
}
/* Free struct */
void free_conv(Conv_Layer * l){
    int size = l->in_depth*l->in_height*l->in_width;
#pragma acc exit data delete(l->bias)
    free(l->bias);
#pragma acc exit data delete(l->weights)
    free(l->weights);
#pragma acc exit data delete(l)
    free(l);
}
```


```c
    //Loading Layers' parameters
    load_conv(L1,"./snapshot/layer1_conv.txt");
    int size = L1->filter_width*L1->filter_height*L1->num_filters*L1->in_depth;
#pragma acc update device(L1->weights[0:size],L1->bias[0:L1->out_depth])
//Test3: add 1 to Weights, then copy from the device the correct weights
#pragma acc parallel loop
    for(int i=0;i<size;i++){
        L1->weights[i]+=1;
    }
#pragma acc update self(L1->weights[0:size])
    arr2txt(L1->weights,1,size,"L1-self.txt");
//Test3^
```