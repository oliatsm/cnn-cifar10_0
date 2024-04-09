# Φόρτωση των δεδομένων του struct conv_layer στην GPU
Δημιουργία θέσης μνήμης στη συσκευή για struct με μέλη pointers:
**WORKING**
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
#pragma acc exit data delete(l->bias[0:l->out_depth])
    free(l->bias);
#pragma acc exit data delete(l->weights[0:size])
    free(l->weights);
#pragma acc exit data delete(l[0:1])
    free(l);
}
```
---
## TEST
Φορτώνω τα βάρη του πρώτου επιπέδου στον host. 
Μεταφέρω τα βάρη στην συσκευή.
Αυξάνω τα βάρη στον host κατά ένα. 
Μεταφέρω τα σωστά βάρη από τη συσκευή στον host.
**WORKING**
```c
    //Loading Layers' parameters
    load_conv(L1,"./snapshot/layer1_conv.txt");
    int size = L1->filter_width*L1->filter_height*L1->num_filters*L1->in_depth;
#pragma acc update device(L1->weights[0:size],L1->bias[0:L1->out_depth])
//Test3: add 1 to Weights, then copy from the device the correct weights
    for(int i=0;i<size;i++){
        L1->weights[i]+=1;
    }
#pragma acc update self(L1->weights[0:size])
    arr2txt(L1->weights,1,size,"L1-self.txt");
//Test3^
```

---
**ΔΕΝ ΔΟΥΛΕΥΕΙ**
```c
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
```
CNN for 1200 images
Loading input batch 1...
L1:Conv:(32,32,3)->(32,32,16)
        Filters:(5,5)x16 s:1,p:2
After
 Conv:(32,32,3)->(32,32,16)
        Filters:(5,5)x16 s:1,p:2
Failing in Thread:1
Accelerator Fatal Error: call to cuStreamSynchronize returned error 700 (CUDA_ERROR_ILLEGAL_ADDRESS): Illegal address during kernel execution
 File: /home/olia/Diplomatiki/cnn-cifar10_0/main.c
 Function: main:101
 Line: 158
 ```