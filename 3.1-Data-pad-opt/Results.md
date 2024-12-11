# Parallel, loop optimization 
## conv_forward, pad_input: gang, vector

```
$ ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
Load Data time:0.375312 seconds
Create Network time:0.130124 seconds
Load Network Parameters time:0.003406 seconds
Create Ouputs time:0.000179 seconds

Net Forward total time:93.426685 seconds
    Time for conv1: 66.565450 seconds
    Time for relu1: 0.219222 seconds
    Time for pool1: 0.575744 seconds
    Time for conv2: 19.559098 seconds
    Time for relu2: 0.081382 seconds
    Time for pool2: 0.187547 seconds
    Time for conv3: 6.016470 seconds
    Time for relu3: 0.030708 seconds
    Time for pool3: 0.048268 seconds
    Time for fc: 0.123813 seconds
    Time for softmax: 0.006452 seconds

  Conv: 92.141018 seconds
  ReLU: 0.331311 seconds
  Pool: 0.811560 seconds
  FC:   0.123813 seconds
  Softmax: 0.006452 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000280 seconds
Free memory time:0.030093 seconds
Total time:93.966078 seconds
```

### gang, worker, vector

```
$ ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.372779 seconds
Create Network time:0.121437 seconds
Load Network Parameters time:0.003348 seconds
Create Ouputs time:0.000163 seconds

Net Forward total time:29.113376 seconds
    Time for conv1: 17.131353 seconds
    Time for relu1: 0.228376 seconds
    Time for pool1: 0.574178 seconds
    Time for conv2: 7.636569 seconds
    Time for relu2: 0.081095 seconds
    Time for pool2: 0.188321 seconds
    Time for conv3: 3.053143 seconds
    Time for relu3: 0.030275 seconds
    Time for pool3: 0.048259 seconds
    Time for fc: 0.123732 seconds
    Time for softmax: 0.005619 seconds

  Conv: 27.821065 seconds
  ReLU: 0.339745 seconds
  Pool: 0.810759 seconds
  FC:   0.123732 seconds
  Softmax: 0.005619 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000254 seconds
Free memory time:0.030052 seconds
Total time:29.641410 seconds
```
## pad_input
gang,vector

```
$ ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
Load Data time:0.372732 seconds
Create Network time:0.138534 seconds
Load Network Parameters time:0.003331 seconds
Create Ouputs time:0.000164 seconds

Net Forward total time:29.141182 seconds
    Time for conv1: 17.154546 seconds
    Time for relu1: 0.223075 seconds
    Time for pool1: 0.573827 seconds
    Time for conv2: 7.647840 seconds
    Time for relu2: 0.082821 seconds
    Time for pool2: 0.188009 seconds
    Time for conv3: 3.049227 seconds
    Time for relu3: 0.030980 seconds
    Time for pool3: 0.048247 seconds
    Time for fc: 0.123956 seconds
    Time for softmax: 0.006164 seconds

  Conv: 27.851613 seconds
  ReLU: 0.336876 seconds
  Pool: 0.810082 seconds
  FC:   0.123956 seconds
  Softmax: 0.006164 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000257 seconds
Free memory time:0.030000 seconds
Total time:29.686201 seconds
```

> δεν έχει διαφορά σε σχέση με σκέτο parallel, 0.02 sec πιο αργό

### gang collapse(2), vector
Κακό! κάνει πολύ ώρα, δεν ξέρω για αποτελέσματα

### gang worker collapse(2) vector
Λάθος αποτελέσματα

## pad_input με kernels, independent

```
pad_input:
     62, Generating present(l[:],X[:])
     65, Loop is parallelizable
         Generating NVIDIA GPU code
         65, #pragma acc loop gang /* blockIdx.x */
         67, #pragma acc loop vector(128) collapse(2) /* threadIdx.x */
         69,   /* threadIdx.x auto-collapsed */
     67, Loop is parallelizable
     69, Loop is parallelizable

Total time:29.685539 seconds
```

με parallel loop present(X,l) gang vector_length(128)
  vector collapse(2)

Total time:29.700127 seconds
Total time:29.675678 seconds
Total time:29.679011 seconds

### code
```c
void pad_input(float* restrict X, Conv_Layer* l) {

#pragma acc parallel loop present(X,l) gang vector_length(128)
  for ( int c = 0; c < l->in_depth; c++) {
    #pragma acc loop vector collapse(2)
    for (int j = 0; j < l->in_height; j++) {
      for (int i = 0; i < l->in_width; i++) {

...

void conv_forward(float* restrict X, Conv_Layer* l, float* restrict Y){

  int in_size = l->in_width*l->in_height*l->in_depth;
#pragma acc data copyin(X[0:in_size]) present(l) copyout(Y[0:l->out_size])
{
    pad_input(X, l); 
   // For each output feature map
#pragma acc parallel loop gang 
    for ( int m = 0; m < l->out_depth; m++) {
      #pragma acc loop worker
      for (int j = 0; j < l->out_height; j++) {
       #pragma acc loop
        for (int i = 0; i < l->out_width; i++) {
          int y_idx = i + (l->out_width * (j + m * l->out_height)); 
          // Calculate dot product of Weights*Input
          float sum = 0.0f;
        #pragma acc loop reduction(+:sum) vector
          for (int c = 0; c < l->in_depth; c++) {
            for (int f_j = 0; f_j < l->filter_width; f_j++) {
              for (int f_i = 0; f_i < l->filter_width; f_i++) {
...

```

### Minfo

```
$ make
nvc -acc -Minfo=all -c11 -Wall -Wextra -march=native -c layers.c -o layers.o
make_conv_layer:
     42, Generating enter data copyin(layer[:1])
         Generating enter data create(layer->weights[:layer->weights_size])
         Generating enter data copyin(layer->in_padded[:layer->padded_size])
         Generating enter data create(layer->bias[:M])
free_conv:
     53, Generating exit data delete(l->bias[:l->out_depth],l->in_padded[:l->padded_size],l[:1],l->weights[:l->weights_size])
pad_input:
     60, Generating present(l[:],X[:])
         Generating NVIDIA GPU code
         63, #pragma acc loop gang /* blockIdx.x */
         65, #pragma acc loop vector(128) collapse(2) /* threadIdx.x */
         66,   /* threadIdx.x collapsed */
     65, Loop is parallelizable
     66, Loop is parallelizable
conv_forward:
     82, Generating present(l[:])
         Generating copyout(Y[:l->out_size]) [if not already present]
         Generating copyin(X[:in_size]) [if not already present]
     83, Generating NVIDIA GPU code
         86, #pragma acc loop gang /* blockIdx.x */
         88, #pragma acc loop worker(4) /* threadIdx.y */
         90, #pragma acc loop seq
         95, #pragma acc loop vector(32) /* threadIdx.x */
             Generating reduction(+:sum)
             Vector barrier inserted to share data across vector lanes
         96, #pragma acc loop seq
         97, #pragma acc loop seq
        104, Vector barrier inserted for vector loop reduction
     88, Loop is parallelizable
     90, Loop is parallelizable
     95, Loop is parallelizable
     96, Loop is parallelizable
     97, Loop is parallelizable
    102, FMA (fused multiply-add) instruction(s) generated
pool_forward:
    185, Zero trip check eliminated
fc_forward:
    240, FMA (fused multiply-add) instruction(s) generated
load_conv:
    302, Generating update device(l->weights[:l->weights_size],l->bias[:l->out_depth])
nvc -acc -Minfo=all -c11 -Wall -Wextra -march=native -o cnn-cifar10 main.o layers.o malloc2D.o timer.o
```

### Execution
```
$ ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.376332 seconds
Create Network time:0.131757 seconds
Load Network Parameters time:0.003346 seconds
Create Ouputs time:0.000161 seconds

Net Forward total time:29.115312 seconds
    Time for conv1: 17.143570 seconds
    Time for relu1: 0.224217 seconds
    Time for pool1: 0.574458 seconds
    Time for conv2: 7.633959 seconds
    Time for relu2: 0.076912 seconds
    Time for pool2: 0.188694 seconds
    Time for conv3: 3.057452 seconds
    Time for relu3: 0.026063 seconds
    Time for pool3: 0.048287 seconds
    Time for fc: 0.123468 seconds
    Time for softmax: 0.005771 seconds

  Conv: 27.834981 seconds
  ReLU: 0.327192 seconds
  Pool: 0.811439 seconds
  FC:   0.123468 seconds
  Softmax: 0.005771 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000269 seconds
Free memory time:0.031898 seconds
Total time:29.659076 seconds
```

# Conv_forward

## gang collapse(3), vector
### code
```c
void conv_forward(float* restrict X, Conv_Layer* l, float* restrict Y){

  int in_size = l->in_width*l->in_height*l->in_depth;
#pragma acc data copyin(X[0:in_size]) present(l) copyout(Y[0:l->out_size])
{
    pad_input(X, l); //Create input with zero-padding
   // For each output feature map
#pragma acc parallel loop gang collapse(3)
    for ( int m = 0; m < l->out_depth; m++) {
      for (int j = 0; j < l->out_height; j++) {
        for (int i = 0; i < l->out_width; i++) {
          int y_idx = i + (l->out_width * (j + m * l->out_height)); 
          // Calculate dot product of Weights*Input
          float sum = 0.0f;
        #pragma acc loop reduction(+:sum) vector
          for (int c = 0; c < l->in_depth; c++) {
            for (int f_j = 0; f_j < l->filter_width; f_j++) {
              for (int f_i = 0; f_i < l->filter_width; f_i++) {
```
### Minfo

```
$ make 
nvc -acc -Minfo=all -c11 -Wall -Wextra -march=native -c layers.c -o layers.o
make_conv_layer:
     42, Generating enter data copyin(layer[:1])
         Generating enter data create(layer->weights[:layer->weights_size])
         Generating enter data copyin(layer->in_padded[:layer->padded_size])
         Generating enter data create(layer->bias[:M])
free_conv:
     53, Generating exit data delete(l->bias[:l->out_depth],l->in_padded[:l->padded_size],l[:1],l->weights[:l->weights_size])
pad_input:
     60, Generating present(l[:],X[:])
         Generating NVIDIA GPU code
         63, #pragma acc loop gang /* blockIdx.x */
         65, #pragma acc loop vector(128) collapse(2) /* threadIdx.x */
         66,   /* threadIdx.x collapsed */
     65, Loop is parallelizable
     66, Loop is parallelizable
conv_forward:
     82, Generating present(l[:])
         Generating copyout(Y[:l->out_size]) [if not already present]
         Generating copyin(X[:in_size]) [if not already present]
     83, Generating NVIDIA GPU code
         86, #pragma acc loop gang collapse(3) /* blockIdx.x */
         88,   /* blockIdx.x collapsed */
         90,   /* blockIdx.x collapsed */
         95, #pragma acc loop vector(128) /* threadIdx.x */
             Generating reduction(+:sum)
         96, #pragma acc loop seq
         97, #pragma acc loop seq
     95, Loop is parallelizable
     96, Loop is parallelizable
     97, Loop is parallelizable
    102, FMA (fused multiply-add) instruction(s) generated
pool_forward:
    185, Zero trip check eliminated
fc_forward:
    240, FMA (fused multiply-add) instruction(s) generated
load_conv:
    302, Generating update device(l->weights[:l->weights_size],l->bias[:l->out_depth])
nvc -acc -Minfo=all -c11 -Wall -Wextra -march=native -o cnn-cifar10 main.o layers.o malloc2D.o timer.o
```

### execution


```
$ ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.377410 seconds
Create Network time:0.125079 seconds
Load Network Parameters time:0.003342 seconds
Create Ouputs time:0.000159 seconds

Net Forward total time:12.662713 seconds
    Time for conv1: 6.308805 seconds
    Time for relu1: 0.222762 seconds
    Time for pool1: 0.575287 seconds
    Time for conv2: 3.348064 seconds
    Time for relu2: 0.081357 seconds
    Time for pool2: 0.187759 seconds
    Time for conv3: 1.720088 seconds
    Time for relu3: 0.028884 seconds
    Time for pool3: 0.048232 seconds
    Time for fc: 0.123255 seconds
    Time for softmax: 0.005744 seconds

  Conv: 11.376957 seconds
  ReLU: 0.333003 seconds
  Pool: 0.811278 seconds
  FC:   0.123255 seconds
  Softmax: 0.005744 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000279 seconds
Free memory time:0.031821 seconds
Total time:13.200804 seconds
```
### nsys

[x] 3.1-gang-collapse3-vector

## gang collapse(3), vector(32)

### Code
```c
60: void pad_input(float* restrict X, Conv_Layer* l) {

#pragma acc parallel loop present(X,l) gang vector_length(128)
  for ( int c = 0; c < l->in_depth; c++) {
    #pragma acc loop vector collapse(2)
    for (int j = 0; j < l->in_height; j++) {
      for (int i = 0; i < l->in_width; i++) {
...

78: void conv_forward(float* restrict X, Conv_Layer* l, float* restrict Y){

  int in_size = l->in_width*l->in_height*l->in_depth;
#pragma acc data copyin(X[0:in_size]) present(l) copyout(Y[0:l->out_size])
{
    pad_input(X, l); //Create input with zero-padding
   // For each output feature map
#pragma acc parallel loop gang collapse(3) vector_length(32)
    for ( int m = 0; m < l->out_depth; m++) {
      for (int j = 0; j < l->out_height; j++) {
        for (int i = 0; i < l->out_width; i++) {
          int y_idx = i + (l->out_width * (j + m * l->out_height)); 

...
```

### Minfo
```
$ make
nvc -acc -Minfo=all -c11 -Wall -Wextra -march=native -c layers.c -o layers.o
make_conv_layer:
     42, Generating enter data copyin(layer[:1])
         Generating enter data create(layer->weights[:layer->weights_size])
         Generating enter data copyin(layer->in_padded[:layer->padded_size])
         Generating enter data create(layer->bias[:M])
free_conv:
     53, Generating exit data delete(l->bias[:l->out_depth],l->in_padded[:l->padded_size],l[:1],l->weights[:l->weights_size])
pad_input:
     60, Generating present(l[:],X[:])
         Generating NVIDIA GPU code
         63, #pragma acc loop gang /* blockIdx.x */
         65, #pragma acc loop vector(128) collapse(2) /* threadIdx.x */
         66,   /* threadIdx.x collapsed */
     65, Loop is parallelizable
     66, Loop is parallelizable
conv_forward:
     82, Generating present(l[:])
         Generating copyout(Y[:l->out_size]) [if not already present]
         Generating copyin(X[:in_size]) [if not already present]
     83, Generating NVIDIA GPU code
         86, #pragma acc loop gang collapse(3) /* blockIdx.x */
         87,   /* blockIdx.x collapsed */
         88,   /* blockIdx.x collapsed */
         93, #pragma acc loop vector(32) /* threadIdx.x */
             Generating reduction(+:sum)
         94, #pragma acc loop seq
         95, #pragma acc loop seq
     93, Loop is parallelizable
     94, Loop is parallelizable
     95, Loop is parallelizable
    100, FMA (fused multiply-add) instruction(s) generated
pool_forward:
    183, Zero trip check eliminated
fc_forward:
    238, FMA (fused multiply-add) instruction(s) generated
load_conv:
    300, Generating update device(l->weights[:l->weights_size],l->bias[:l->out_depth])
nvc -acc -Minfo=all -c11 -Wall -Wextra -march=native -o cnn-cifar10 main.o layers.o malloc2D.o timer.o

```

### execution
```
$ ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.375801 seconds
Create Network time:0.123056 seconds
Load Network Parameters time:0.003363 seconds
Create Ouputs time:0.000164 seconds

Net Forward total time:8.323151 seconds
    Time for conv1: 3.314643 seconds
    Time for relu1: 0.227602 seconds
    Time for pool1: 0.574781 seconds
    Time for conv2: 2.264616 seconds
    Time for relu2: 0.081323 seconds
    Time for pool2: 0.191381 seconds
    Time for conv3: 1.446953 seconds
    Time for relu3: 0.031110 seconds
    Time for pool3: 0.048339 seconds
    Time for fc: 0.123672 seconds
    Time for softmax: 0.006268 seconds

  Conv: 7.026212 seconds
  ReLU: 0.340034 seconds
  Pool: 0.814500 seconds
  FC:   0.123672 seconds
  Softmax: 0.006268 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000265 seconds
Free memory time:0.031137 seconds
Total time:8.856938 seconds
```

### nsys 

[x] 