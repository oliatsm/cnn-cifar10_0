# Parallel, managed, if
## Code
```c
void conv_forward(float* restrict X, Conv_Layer* l, float* restrict Y) {
  
    // For each output feature map
    #pragma acc parallel loop
    for (int m = 0; m < l->out_depth; m++) {
      #pragma acc loop 
      for (int j = 0; j < l->out_height; j++) {
        #pragma acc loop 
        for (int i = 0; i < l->out_width; i++) {
          int y_idx = i + (l->out_width * (j + m * l->out_height)); 
          // Calculate dot product of Weights*Input
          float sum = 0.0f;
          #pragma acc loop reduction(+:sum) 
          for (int c = 0; c < l->in_depth; c++) {

```


## Minfo
```
$ make
nvc -acc=gpu -gpu=mem:managed -Minfo=all -c11 -Wall -Wextra -march=native -c main.c -o main.o
arr2txt:
    331, Zero trip check eliminated
arr2txt_2:
    353, Zero trip check eliminated
nvc -acc=gpu -gpu=mem:managed -Minfo=all -c11 -Wall -Wextra -march=native -c layers.c -o layers.o
conv_forward:
     46, Generating implicit firstprivate(m)
         Generating NVIDIA GPU code
         50, #pragma acc loop gang /* blockIdx.x */
         52, #pragma acc loop seq
         54, #pragma acc loop seq
         59, #pragma acc loop seq
         60, #pragma acc loop seq
         61, #pragma acc loop vector(128) /* threadIdx.x */
             Generating reduction(+:sum)
     46, Generating implicit copyin(l) [if not already present]
         Generating implicit copy(Y[:]) [if not already present]
         Generating implicit copyin(X[:]) [if not already present]
     52, Loop is parallelizable
     54, Loop is parallelizable
     59, Loop is parallelizable
     60, Loop is parallelizable
     61, Loop is parallelizable
pool_forward:
    152, Zero trip check eliminated
fc_forward:
    207, FMA (fused multiply-add) instruction(s) generated
nvc -acc=gpu -gpu=mem:managed -Minfo=all -c11 -Wall -Wextra -march=native -c malloc2D.c -o malloc2D.o
nvc -acc=gpu -gpu=mem:managed -Minfo=all -c11 -Wall -Wextra -march=native -c timer.c -o timer.o
cpu_timer_stop:
     11, FMA (fused multiply-add) instruction(s) generated
nvc -acc=gpu -gpu=mem:managed -Minfo=all -c11 -Wall -Wextra -march=native -o cnn-cifar10 main.o layers.o malloc2D.o timer.o

```

## Execution

```
$ ./cnn-cifar10 
Parallel (if) Code
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.516129 seconds
Create Network time:0.000595 seconds
Load Network Parameters time:0.008058 seconds
Create Ouputs time:0.000631 seconds

Net Forward total time:309.631899 seconds
    Time for conv1: 129.499650 seconds
    Time for relu1: 9.575164 seconds
    Time for pool1: 5.829847 seconds
    Time for conv2: 103.449449 seconds
    Time for relu2: 8.069406 seconds
    Time for pool2: 1.686345 seconds
    Time for conv3: 43.449361 seconds
    Time for relu3: 5.998202 seconds
    Time for pool3: 0.613076 seconds
    Time for fc: 1.429540 seconds
    Time for softmax: 0.013341 seconds

  Conv: 276.398460 seconds
  ReLU: 23.642772 seconds
  Pool: 8.129268 seconds
  FC:   1.429540 seconds
  Softmax: 0.013341 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000693 seconds
Free memory time:0.020704 seconds
Total time:310.178710 seconds
```

## Profiling
### NVprof

```
$ nvprof ./cnn-cifar10-profile 
Parallel (if) Code
CNN for 50000 images
==2641714== NVPROF is profiling process 2641714, command: ./cnn-cifar10-profile
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.584551 seconds
Create Network time:0.000683 seconds
Load Network Parameters time:0.008530 seconds
Create Ouputs time:0.000840 seconds

Net Forward total time:340.438726 seconds
    Time for conv1: 133.068567 seconds
    Time for relu1: 18.984666 seconds
    Time for pool1: 8.738945 seconds
    Time for conv2: 103.810045 seconds
    Time for relu2: 13.332291 seconds
    Time for pool2: 3.134427 seconds
    Time for conv3: 46.355367 seconds
    Time for relu3: 10.077168 seconds
    Time for pool3: 1.108418 seconds
    Time for fc: 1.775332 seconds
    Time for softmax: 0.022480 seconds

  Conv: 283.233980 seconds
  ReLU: 42.394124 seconds
  Pool: 12.981790 seconds
  FC:   1.775332 seconds
  Softmax: 0.022480 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000939 seconds
Free memory time:0.022109 seconds
Total time:341.056377 seconds
END!
==2641714== Profiling application: ./cnn-cifar10-profile
==2641714== Profiling result:
            Type  Time(%)      Time     Calls       Avg       Min       Max  Name
 GPU activities:  100.00%  279.125s    150000  1.8608ms  626.62us  7.3803ms  _8layers_c_conv_forward_46_gpu
      API calls:   99.49%  279.833s    300000  932.78us  1.1940us  7.5097ms  cuStreamSynchronize
                    0.38%  1.06798s    150000  7.1190us  4.7320us  1.5621ms  cuLaunchKernel
                    0.05%  130.98ms         1  130.98ms  130.98ms  130.98ms  cuDevicePrimaryCtxRetain
                    0.04%  105.06ms    300000     350ns     161ns  220.15us  cuOccupancyMaxActiveBlocksPerMultiprocessor
                    0.01%  39.302ms     50011     785ns     237ns  98.574us  cuPointerGetAttributes
                    0.01%  37.144ms    150009     247ns     116ns  16.946us  cuDeviceGetAttribute
                    0.01%  21.964ms         1  21.964ms  21.964ms  21.964ms  cuMemFree
                    0.01%  20.717ms         2  10.358ms  97.657us  20.619ms  cuMemAllocManaged
                    0.00%  1.2859ms         1  1.2859ms  1.2859ms  1.2859ms  cuMemAllocHost
                    0.00%  621.01us         1  621.01us  621.01us  621.01us  cuModuleLoadDataEx
                    0.00%  128.06us         1  128.06us  128.06us  128.06us  cuMemAlloc
                    0.00%  19.274us         1  19.274us  19.274us  19.274us  cuModuleGetFunction
                    0.00%  15.046us         1  15.046us  15.046us  15.046us  cuDeviceGetPCIBusId
                    0.00%  3.5450us         2  1.7720us     105ns  3.4400us  cuDeviceTotalMem
                    0.00%  2.8880us         3     962ns     214ns  1.5740us  cuCtxSetCurrent
                    0.00%  2.3490us         3     783ns     106ns  2.0900us  cuDeviceGetCount
                    0.00%     980ns         1     980ns     980ns     980ns  cuCtxGetCurrent
                    0.00%     831ns         3     277ns      96ns     401ns  cuDriverGetVersion
                    0.00%     521ns         2     260ns     112ns     409ns  cuDeviceGet
                    0.00%     442ns         1     442ns     442ns     442ns  cuDeviceComputeCapability
 OpenACC (excl):   99.02%  280.199s    300000  934.00us  1.8680us  7.5110ms  acc_wait@layers.c:46
                    0.47%  1.33204s    150000  8.8800us  5.8520us  1.9248ms  acc_enqueue_launch@layers.c:46 (_8layers_c_conv_forward_46_gpu)
                    0.21%  602.06ms    150000  4.0130us  2.9190us  1.5492ms  acc_compute_construct@layers.c:46
                    0.19%  547.10ms    150000  3.6470us  1.9860us  3.2879ms  acc_enter_data@layers.c:46
                    0.10%  292.74ms    150000  1.9510us  1.2980us  828.21us  acc_exit_data@layers.c:46
                    0.00%  703.62us         1  703.62us  703.62us  703.62us  acc_device_init

==2641714== Unified Memory profiling result:
Device "Tesla V100-PCIE-32GB (0)"
   Count  Avg Size  Min Size  Max Size  Total Size  Total Time  Name
 1015451  26.939KB  4.0000KB  0.9961MB  26.08832GB   4.618286s  Host To Device
 1810082  14.781KB  4.0000KB  252.00KB  25.51612GB   3.858506s  Device To Host
  238083         -         -         -           -  53.551726s  Gpu page fault groups
  590712  4.0000KB  4.0000KB  4.0000KB  2.253388GB           -  Memory thrashes
Total CPU Page faults: 1073940
Total CPU thrashes: 590712
```