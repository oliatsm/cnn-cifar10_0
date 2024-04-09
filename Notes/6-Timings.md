# Make Output
```
$ make
nvc -acc -Minfo=acc -c11 -Wall -Wextra -march=native -g -o cnn-cifar10 main.c layers.c malloc2D.c
main.c:
main:
    131, Generating enter data create(input[:50000][:3072])
    136, Generating update device(input[:50000][:3072])
    157, Generating enter data create(O1[:L1->out_depth*(L1->out_width*L1->out_height)])
    159, Generating enter data create(O2[:L2->out_depth*(L2->out_width*L2->out_height)])
    161, Generating enter data create(O3[:L3->out_depth*(L3->out_width*L3->out_height)])
    163, Generating enter data create(O4[:L4->out_depth*(L4->out_width*L4->out_height)])
    165, Generating enter data create(O5[:L5->out_depth*(L5->out_width*L5->out_height)])
    167, Generating enter data create(O6[:L6->out_depth*(L6->out_width*L6->out_height)])
    169, Generating enter data create(O7[:L7->out_depth*(L7->out_width*L7->out_height)])
    171, Generating enter data create(O8[:L8->out_depth*(L8->out_width*L8->out_height)])
    173, Generating enter data create(O9[:L9->out_depth*(L9->out_width*L9->out_height)])
    175, Generating enter data create(O10[:L10->out_depth*(L10->out_width*L10->out_height)])
    178, Generating enter data create(O11[:50000][:L11->out_depth])
    185, Generating update device(O1[:L1->out_depth*(L1->out_width*L1->out_height)])
    187, Generating update self(O2[:L2->out_depth*(L2->out_width*L2->out_height)])
    228, Generating exit data delete(O11[:50000][:L11->out_depth])
    230, Generating exit data delete(O10[:L10->out_depth*(L10->out_width*L10->out_height)])
    232, Generating exit data delete(O9[:L9->out_depth*(L9->out_width*L9->out_height)])
    234, Generating exit data delete(O8[:L8->out_depth*(L8->out_width*L8->out_height)])
    236, Generating exit data delete(O7[:L7->out_depth*(L7->out_width*L7->out_height)])
    238, Generating exit data delete(O6[:L6->out_depth*(L6->out_width*L6->out_height)])
    240, Generating exit data delete(O5[:L5->out_depth*(L5->out_width*L5->out_height)])
    242, Generating exit data delete(O4[:L4->out_depth*(L4->out_width*L4->out_height)])
    244, Generating exit data delete(O3[:L3->out_depth*(L3->out_width*L3->out_height)])
    246, Generating exit data delete(O2[:L2->out_depth*(L2->out_width*L2->out_height)])
    248, Generating exit data delete(O1[:L1->out_depth*(L1->out_width*L1->out_height)])
    267, Generating exit data delete(input[:50000][:3072])
layers.c:
make_conv_layer:
     11, Generating enter data create(layer[:1])
     30, Generating enter data create(layer->weights[:size])
     36, Generating enter data create(layer->bias[:M])
         Generating update device(layer->num_filters,layer->out_depth,layer->out_height,layer->filter_width,layer->in_depth,layer->in_height,layer->out_width,layer->stride,layer->padding,layer->in_width,layer->filter_height)
free_conv:
     42, Generating exit data delete(l->bias[:l->out_depth])
     44, Generating exit data delete(l->weights[:size])
     46, Generating exit data delete(l[:1])
make_relu_layer:
     80, Generating enter data create(layer[:1])
     88, Generating update device(layer->in_width,layer->out_depth,layer->out_width,layer->out_height,layer->in_depth,layer->in_height)
relu_forward:
     93, Generating present(Y[:],l[:],X[:])
         Generating copyin(size) [if not already present]
         Generating implicit firstprivate(i)
         Generating NVIDIA GPU code
         95, #pragma acc loop gang, vector(128) /* blockIdx.x threadIdx.x */
free_relu:
    103, Generating exit data delete(l[:1])
make_pool_layer:
    109, Generating enter data create(layer[:1])
    122, Generating update device(layer->in_width,layer->out_depth,layer->out_height,layer->out_width,layer->stride,layer->pool_width,layer->padding,layer->in_depth,layer->in_height)
free_pool:
    152, Generating exit data delete(l[:1])
make_fc_layer:
    158, Generating enter data create(layer[:1])
    170, Generating enter data create(layer->weights[:layer->out_depth*layer->in_neurons])
    175, Generating enter data create(layer->bias[:layer->out_depth])
         Generating update device(layer->in_width,layer->out_depth,layer->out_width,layer->out_height,layer->in_depth,layer->in_neurons,layer->in_height)
free_fc:
    195, Generating exit data delete(l->bias[:l->out_depth])
    197, Generating exit data delete(l->weights[:l->out_depth*l->in_neurons])
    199, Generating exit data delete(l[:1])
load_conv:
    242, Generating update device(l->weights[:l->in_depth*(l->num_filters*(l->filter_width*l->filter_height))],l->bias[:l->out_depth])
load_fc:
    277, Generating update device(l->weights[:l->out_depth*l->in_neurons],l->bias[:l->out_depth])
make_softmax_layer:
    284, Generating enter data create(layer[:1])
    295, Generating enter data create(layer->likelihoods[:layer->out_depth])
         Generating update device(layer->in_width,layer->out_depth,layer->out_height,layer->out_width,layer->in_depth,layer->in_height)
free_softmax:
    327, Generating exit data delete(l->likelihoods[:l->out_depth])
    329, Generating exit data delete(l[:1])
malloc2D.c:
```
## Timming

```
export NV_ACC_TIME=1
```

```
Accelerator Kernel Timing data
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  make_conv_layer  NVIDIA  devicenum=0
    time(us): 757
    11: data region reached 3 times
    30: data region reached 3 times
        30: data copyin transfers: 6
             device time(us): total=550 max=261 min=4 avg=91
    50: data region reached 3 times
        50: data copyin transfers: 6
             device time(us): total=65 max=20 min=4 avg=10
    50: update directive reached 6 times
        50: data copyin transfers: 33
             device time(us): total=142 max=5 min=4 avg=4
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  free_conv  NVIDIA  devicenum=0
    time(us): 115
    56: data region reached 3 times
        56: data copyin transfers: 6
             device time(us): total=52 max=14 min=4 avg=8
    58: data region reached 3 times
        58: data copyin transfers: 6
             device time(us): total=63 max=26 min=4 avg=10
    60: data region reached 3 times
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  make_relu_layer  NVIDIA  devicenum=0
    time(us): 83
    94: data region reached 3 times
    102: update directive reached 3 times
        102: data copyin transfers: 18
             device time(us): total=83 max=5 min=4 avg=4
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  relu_forward  NVIDIA  devicenum=0
    time(us): 10
    107: compute region reached 1 time
        107: kernel launched 1 time
            grid: [128]  block: [128]
            elapsed time(us): total=94 max=94 min=94 avg=94
    107: data region reached 2 times
        107: data copyin transfers: 1
             device time(us): total=10 max=10 min=10 avg=10
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  free_relu  NVIDIA  devicenum=0
    time(us): 0
    117: data region reached 3 times
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  make_pool_layer  NVIDIA  devicenum=0
    time(us): 119
    123: data region reached 3 times
    136: update directive reached 3 times
        136: data copyin transfers: 27
             device time(us): total=119 max=5 min=4 avg=4
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  free_pool  NVIDIA  devicenum=0
    time(us): 0
    166: data region reached 3 times
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  make_fc_layer  NVIDIA  devicenum=0
    time(us): 63
    172: data region reached 1 time
    184: data region reached 1 time
        184: data copyin transfers: 2
             device time(us): total=17 max=13 min=4 avg=8
    189: data region reached 1 time
        189: data copyin transfers: 2
             device time(us): total=18 max=14 min=4 avg=9
    189: update directive reached 1 time
        189: data copyin transfers: 7
             device time(us): total=28 max=4 min=4 avg=4
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  free_fc  NVIDIA  devicenum=0
    time(us): 44
    209: data region reached 1 time
        209: data copyin transfers: 2
             device time(us): total=27 max=18 min=9 avg=13
    211: data region reached 1 time
        211: data copyin transfers: 2
             device time(us): total=17 max=13 min=4 avg=8
    213: data region reached 1 time
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  load_conv  NVIDIA  devicenum=0
    time(us): 238
    256: update directive reached 3 times
        256: data copyin transfers: 6
             device time(us): total=238 max=188 min=3 avg=39
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  load_fc  NVIDIA  devicenum=0
    time(us): 10
    291: update directive reached 1 time
        291: data copyin transfers: 2
             device time(us): total=10 max=6 min=4 avg=5
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  make_softmax_layer  NVIDIA  devicenum=0
    time(us): 44
    298: data region reached 1 time
    309: data region reached 1 time
        309: data copyin transfers: 2
             device time(us): total=19 max=14 min=5 avg=9
    309: update directive reached 1 time
        309: data copyin transfers: 6
             device time(us): total=25 max=5 min=4 avg=4
/home/olia/Documents/Programming/cnn-cifar10_0/layers.c
  free_softmax  NVIDIA  devicenum=0
    time(us): 505
    341: data region reached 1 time
        341: data copyin transfers: 2
             device time(us): total=505 max=257 min=248 avg=252
    343: data region reached 1 time
/home/olia/Documents/Programming/cnn-cifar10_0/main.c
  main  NVIDIA  devicenum=0
    time(us): 394,129
    131: data region reached 1 time
        42: kernel launched 1 time
            grid: [391]  block: [128]
            elapsed time(us): total=59 max=59 min=59 avg=59
    136: update directive reached 1 time
        136: data copyin transfers: 1
             device time(us): total=393,994 max=393,994 min=393,994 avg=393,994
    157: data region reached 1 time
    159: data region reached 1 time
    161: data region reached 1 time
    163: data region reached 1 time
    165: data region reached 1 time
    167: data region reached 1 time
    169: data region reached 1 time
    171: data region reached 1 time
    173: data region reached 1 time
    175: data region reached 1 time
    178: data region reached 1 time
        42: kernel launched 1 time
            grid: [391]  block: [128]
            elapsed time(us): total=224 max=224 min=224 avg=224
    185: update directive reached 1 time
        185: data copyin transfers: 1
             device time(us): total=38 max=38 min=38 avg=38
    187: update directive reached 1 time
        187: data copyout transfers: 1
             device time(us): total=97 max=97 min=97 avg=97
    228: data region reached 1 time
    230: data region reached 1 time
    232: data region reached 1 time
    234: data region reached 1 time
    236: data region reached 1 time
    238: data region reached 1 time
    240: data region reached 1 time
    242: data region reached 1 time
    244: data region reached 1 time
    246: data region reached 1 time
    248: data region reached 1 time
    267: data region reached 1 time
```

## Serial execution
```
$ ./cnn-cifar10 
CNN for 1200 images
Loading input batch 1...
Net Forward total time:42.932512 seconds
Net Accuracy: 78.25 % 
```
```
$ ./cnn-cifar10 
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Net Forward total time:406.492637 seconds
Net Accuracy: 78.84 % 
```