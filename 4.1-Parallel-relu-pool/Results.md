```
$ ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:1.000450 seconds
Create Network time:0.040167 seconds
Load Network Parameters time:0.008800 seconds
Create Ouputs time:0.000356 seconds

Net Forward total time:11.089048 seconds
    Time for conv1: 2.103111 seconds
    Time for relu1: 0.790436 seconds
    Time for pool1: 0.650691 seconds
    Time for conv2: 1.887330 seconds
    Time for relu2: 0.562898 seconds
    Time for pool2: 0.546121 seconds
    Time for conv3: 1.409779 seconds
    Time for relu3: 0.503335 seconds
    Time for pool3: 0.510057 seconds
    Time for fc: 0.539010 seconds
    Time for softmax: 1.563625 seconds

  Conv: 5.400220 seconds
  ReLU: 1.856669 seconds
  Pool: 1.706870 seconds
  FC:   0.539010 seconds
  Softmax: 1.563625 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000694 seconds
Free memory time:0.049288 seconds
Total time:12.188802 seconds
END!
```
## Profile

### nvprof

```
$ nvprof ./cnn-cifar10-profile 
Parallel (pad) Code
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
==2641197== NVPROF is profiling process 2641197, command: ./cnn-cifar10-profile
Load Data time:1.375875 seconds
Create Network time:0.037855 seconds
Load Network Parameters time:0.008372 seconds
Create Ouputs time:0.000320 seconds

Net Forward total time:19.474113 seconds
    Time for conv1: 3.285483 seconds
    Time for relu1: 1.309537 seconds
    Time for pool1: 1.144444 seconds
    Time for conv2: 3.024486 seconds
    Time for relu2: 1.059439 seconds
    Time for pool2: 1.025816 seconds
    Time for conv3: 2.469370 seconds
    Time for relu3: 0.971316 seconds
    Time for pool3: 1.000859 seconds
    Time for fc: 1.068881 seconds
    Time for softmax: 3.082240 seconds

  Conv: 8.779339 seconds
  ReLU: 3.340293 seconds
  Pool: 3.171119 seconds
  FC:   1.068881 seconds
  Softmax: 3.082240 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000717 seconds
Free memory time:0.059393 seconds
Total time:20.956644 seconds
END!
==2641197== Profiling application: ./cnn-cifar10-profile
==2641197== Profiling result:
            Type  Time(%)      Time     Calls       Avg       Min       Max  Name
 GPU activities:   44.43%  2.51786s    150000  16.785us  7.7760us  25.440us  _8layers_c_conv_forward_77_gpu
                   16.89%  957.24ms    150000  6.3810us  6.3350us  13.536us  _8layers_c_pad_input_60_gpu
                   13.67%  774.42ms    150000  5.1620us  2.4630us  13.536us  _8layers_c_relu_forward_130_gpu
                   11.29%  639.61ms    150000  4.2640us  3.0070us  13.536us  _8layers_c_pool_forward_174_gpu
                    3.16%  179.21ms     50000  3.5840us  3.5510us  13.569us  _8layers_c_fc_forward_237_gpu
                    2.58%  145.98ms        47  3.1059ms     735ns  145.93ms  [CUDA memcpy HtoD]
                    2.55%  144.41ms     50000  2.8880us  2.8470us  13.376us  _8layers_c_softmax_forward_399_gpu
                    2.30%  130.21ms     50000  2.6040us  2.5590us  13.440us  _8layers_c_softmax_forward_392_gpu
                    1.83%  103.49ms     50000  2.0690us  2.0150us  13.472us  _8layers_c_softmax_forward_408_gpu
                    1.31%  74.025ms    100000     740ns     703ns  1.2480us  [CUDA memset]
                    0.00%  163.65us         3  54.549us  2.3690us  155.17us  [CUDA memcpy DtoH]
                    0.00%  5.3430us         2  2.6710us  2.6240us  2.7190us  _21______src_cuda_fill_c___pgi_uacc_cuda_fill_44_gpu
      API calls:   63.84%  8.01164s   1500030  5.3400us     755ns  4.7821ms  cuStreamSynchronize
                   28.29%  3.55087s    800002  4.4380us  3.3410us  15.004ms  cuLaunchKernel
                    2.16%  270.59ms    100000  2.7050us  1.9060us  2.6104ms  cuMemsetD32Async
                    1.33%  166.32ms         1  166.32ms  166.32ms  166.32ms  cuDevicePrimaryCtxRetain
                    1.32%  165.56ms    600000     275ns     184ns  744.84us  cuOccupancyMaxActiveBlocksPerMultiprocessor
                    1.28%  160.10ms    800011     200ns     128ns  793.39us  cuDeviceGetAttribute
                    1.17%  146.38ms        47  3.1145ms  2.7460us  146.12ms  cuMemcpyHtoDAsync
                    0.30%  37.173ms         1  37.173ms  37.173ms  37.173ms  cuMemHostAlloc
                    0.28%  35.527ms    100039     355ns     233ns  855.10us  cuPointerGetAttributes
                    0.02%  2.1509ms         3  716.96us  46.646us  1.9550ms  cuMemcpyDtoHAsync
                    0.01%  1.2630ms         1  1.2630ms  1.2630ms  1.2630ms  cuMemAllocHost
                    0.01%  1.2071ms         2  603.56us  104.49us  1.1026ms  cuModuleLoadDataEx
                    0.01%  849.21us        40  21.230us  1.8030us  217.48us  cuMemAlloc
                    0.00%  12.094us         1  12.094us  12.094us  12.094us  cuDeviceGetPCIBusId
                    0.00%  6.4310us        10     643ns     297ns  1.5780us  cuModuleGetFunction
                    0.00%  3.2370us         3  1.0790us     223ns  1.8250us  cuCtxSetCurrent
                    0.00%  2.7970us         3     932ns     260ns  2.2050us  cuDeviceGetCount
                    0.00%     985ns         2     492ns     208ns     777ns  cuDeviceGet
                    0.00%     932ns         3     310ns     159ns     441ns  cuDriverGetVersion
                    0.00%     676ns         1     676ns     676ns     676ns  cuDeviceComputeCapability
                    0.00%     638ns         1     638ns     638ns     638ns  cuCtxGetCurrent
 OpenACC (excl):  100.00%  1.7e+10s         1  1.7e+10s  1.7e+10s  1.7e+10s  acc_enter_data@main.c:121
                    0.00%  3.23746s    300000  10.791us  1.5650us  4.8172ms  acc_wait@layers.c:77
                    0.00%  1.65982s    300000  5.5320us  1.5770us  1.0036ms  acc_wait@layers.c:60
                    0.00%  1.48624s    300000  4.9540us  1.5700us  811.50us  acc_wait@layers.c:130
                    0.00%  1.33828s    300000  4.4600us  1.5610us  1.0189ms  acc_wait@layers.c:174
                    0.00%  825.72ms    150000  5.5040us  4.4100us  866.90us  acc_enqueue_launch@layers.c:60 (_8layers_c_pad_input_60_gpu)
                    0.00%  823.39ms    150000  5.4890us  4.3500us  2.7176ms  acc_enqueue_launch@layers.c:77 (_8layers_c_conv_forward_77_gpu)
                    0.00%  821.64ms    150000  5.4770us  4.4060us  2.8755ms  acc_enqueue_launch@layers.c:174 (_8layers_c_pool_forward_174_gpu)
                    0.00%  818.02ms    150000  5.4530us  4.4870us  7.5451ms  acc_enqueue_launch@layers.c:130 (_8layers_c_relu_forward_130_gpu)
                    0.00%  446.14ms    100000  4.4610us  1.8320us  4.6620ms  acc_wait@layers.c:392
                    0.00%  425.07ms    150000  2.8330us  2.4150us  787.61us  acc_compute_construct@layers.c:60
                    0.00%  422.97ms    100000  4.2290us  1.5590us  880.34us  acc_wait@layers.c:237
                    0.00%  411.88ms    150000  2.7450us  2.3790us  781.77us  acc_compute_construct@layers.c:77
                    0.00%  311.99ms     50000  6.2390us  5.6600us  861.87us  acc_enter_data@layers.c:392
                    0.00%  311.70ms    150000  2.0780us  1.7070us  798.47us  acc_enter_data@layers.c:77
                    0.00%  306.31ms    150000  2.0420us  1.7940us  779.51us  acc_enter_data@layers.c:130
                    0.00%  302.79ms     50000  6.0550us  4.8350us  932.73us  acc_enqueue_launch@layers.c:392 (_8layers_c_softmax_forward_392_gpu)
                    0.00%  295.57ms    150000  1.9700us  1.7370us  637.56us  acc_enter_data@layers.c:174
                    0.00%  289.36ms     50000  5.7870us  4.4000us  15.007ms  acc_enqueue_launch@layers.c:237 (_8layers_c_fc_forward_237_gpu)
                    0.00%  283.39ms     50000  5.6670us  1.8330us  412.43us  acc_wait@layers.c:399
                    0.00%  280.21ms    150000  1.8680us  1.5320us  828.27us  acc_compute_construct@layers.c:130
                    0.00%  278.70ms    150000  1.8570us  1.5340us  871.10us  acc_exit_data@layers.c:130
                    0.00%  277.44ms    150000  1.8490us  1.5730us  795.39us  acc_compute_construct@layers.c:174
                    0.00%  273.56ms     50000  5.4710us  4.2510us  3.4487ms  acc_enqueue_launch@layers.c:408 (_8layers_c_softmax_forward_408_gpu)
                    0.00%  269.75ms     50000  5.3950us  4.3250us  966.58us  acc_enqueue_launch@layers.c:399 (_8layers_c_softmax_forward_399_gpu)
                    0.00%  269.30ms    150000  1.7950us  1.4500us  887.28us  acc_enter_data@layers.c:60
                    0.00%  265.14ms    150000  1.7670us  1.5340us  756.42us  acc_exit_data@layers.c:174
                    0.00%  259.99ms    150000  1.7330us  1.5140us  764.96us  acc_exit_data@layers.c:77
                    0.00%  243.86ms     50000  4.8770us  1.8290us  775.08us  acc_wait@layers.c:408
                    0.00%  219.52ms    150000  1.4630us  1.2640us  745.18us  acc_exit_data@layers.c:60
                    0.00%  212.77ms     50000  4.2550us  3.4610us  807.70us  acc_exit_data@layers.c:392
                    0.00%  192.79ms     50000  3.8550us  3.0130us  2.6118ms  acc_enqueue_upload@layers.c:392 (max)
                    0.00%  177.17ms     50000  3.5430us  2.5900us  814.83us  acc_enqueue_upload@layers.c:392 (total)
                    0.00%  146.13ms         1  146.13ms  146.13ms  146.13ms  acc_enqueue_upload@main.c:121 (input[:50000][:3072])
                    0.00%  105.87ms     50000  2.1170us  1.5720us  784.65us  acc_compute_construct@layers.c:237
                    0.00%  105.32ms     50000  2.1060us  1.8630us  734.71us  acc_enter_data@layers.c:237
                    0.00%  91.379ms     50000  1.8270us  1.6500us  750.33us  acc_compute_construct@layers.c:392
                    0.00%  88.371ms     50000  1.7670us  1.5890us  21.040us  acc_exit_data@layers.c:237
                    0.00%  86.540ms     50000  1.7300us  1.5390us  852.95us  acc_compute_construct@layers.c:399
                    0.00%  83.382ms     50000  1.6670us  1.5090us  105.99us  acc_compute_construct@layers.c:408
                    0.00%  37.394ms         9  4.1549ms  8.1590us  37.228ms  acc_enter_data@layers.c:42
                    0.00%  29.985ms         4  7.4963ms  18.649us  29.917ms  acc_enter_data@main.c:181
                    0.00%  1.9591ms         1  1.9591ms  1.9591ms  1.9591ms  acc_enqueue_download@main.c:248 (O11[:50000][:L11->out_size])
                    0.00%  1.1905ms         1  1.1905ms  1.1905ms  1.1905ms  acc_device_init@main.c:121
                    0.00%  1.1880ms         1  1.1880ms  1.1880ms  1.1880ms  acc_update@main.c:248
                    0.00%  1.0523ms         1  1.0523ms  1.0523ms  1.0523ms  acc_exit_data@main.c:342
                    0.00%  977.55us         4  244.39us  4.2700us  957.57us  acc_exit_data@main.c:314
                    0.00%  151.58us         1  151.58us  151.58us  151.58us  acc_enqueue_download@main.c:241 (O1[:L1->out_size])
                    0.00%  91.352us         2  45.676us  39.027us  52.325us  acc_enqueue_launch@(runtime):44 (_21______src_cuda_fill_c___pgi_uacc_cuda_fill_44_gpu)
                    0.00%  80.696us        18  4.4830us     921ns  25.308us  acc_enqueue_upload@layers.c:42 (.attach.)
                    0.00%  66.073us         1  66.073us  66.073us  66.073us  acc_wait@main.c:121
                    0.00%  60.410us         9  6.7120us  4.4530us  10.172us  acc_wait@layers.c:42
                    0.00%  47.999us         1  47.999us  47.999us  47.999us  acc_enqueue_download@main.c:241 (O4[:L4->out_size])
                    0.00%  42.786us         3  14.262us  8.9070us  19.279us  acc_enqueue_upload@layers.c:308 (l->weights[:l->weights_size])
                    0.00%  41.896us        18  2.3270us     831ns  4.3640us  acc_enqueue_upload@layers.c:53 (.detach.)
                    0.00%  32.435us         3  10.811us  7.9030us  12.525us  acc_enqueue_upload@layers.c:42 (layer->in_padded[:layer->padded_size])
                    0.00%  29.502us         3  9.8340us  8.8170us  10.574us  acc_enter_data@layers.c:125
                    0.00%  28.273us         2  14.136us  2.6570us  25.616us  acc_enqueue_upload@layers.c:423 (.detach.)
                    0.00%  25.969us         3  8.6560us  4.0850us  17.518us  acc_enqueue_upload@layers.c:42 (layer[:1])
                    0.00%  25.640us         9  2.8480us  1.5320us  4.8840us  acc_exit_data@layers.c:53
                    0.00%  24.549us         2  12.274us  7.7750us  16.774us  acc_enter_data@layers.c:232
                    0.00%  24.294us         3  8.0980us  4.2710us  11.112us  acc_wait@layers.c:308
                    0.00%  22.002us         3  7.3340us  6.8720us  8.0680us  acc_enter_data@layers.c:169
                    0.00%  21.145us         1  21.145us  21.145us  21.145us  acc_update@main.c:241
                    0.00%  15.223us         2  7.6110us  7.5270us  7.6960us  acc_enter_data@layers.c:382
                    0.00%  14.739us         3  4.9130us  4.7330us  5.0100us  acc_wait@layers.c:169
                    0.00%  14.348us         3  4.7820us  4.7690us  4.8030us  acc_wait@layers.c:125
                    0.00%  13.468us         3  4.4890us  2.5810us  7.8020us  acc_update@layers.c:308
                    0.00%  13.221us         3  4.4070us  4.0620us  4.6280us  acc_enqueue_upload@layers.c:125 (layer[:1])
                    0.00%  13.181us         2  6.5900us  1.8760us  11.305us  acc_exit_data@layers.c:423
                    0.00%  11.824us         3  3.9410us  3.8440us  4.1200us  acc_enqueue_upload@layers.c:169 (layer[:1])
                    0.00%  11.404us         3  3.8010us  3.4750us  4.1500us  acc_enqueue_upload@layers.c:308 (l->bias[:l->out_depth])
                    0.00%  11.107us         4  2.7760us     848ns  5.2150us  acc_enqueue_upload@layers.c:259 (.detach.)
                    0.00%  10.689us         1  10.689us  10.689us  10.689us  acc_enqueue_upload@layers.c:356 (l->weights[:l->out_depth*l->in_neurons])
                    0.00%  10.445us         4  2.6110us  1.4220us  5.3890us  acc_wait@main.c:181
                    0.00%  10.267us         4  2.5660us     960ns  4.3240us  acc_enqueue_upload@layers.c:232 (.attach.)
                    0.00%  9.5110us         2  4.7550us  4.7390us  4.7720us  acc_wait@layers.c:232
                    0.00%  9.1530us         2  4.5760us  4.4450us  4.7080us  acc_wait@layers.c:382
                    0.00%  7.1630us         2  3.5810us  1.7340us  5.4290us  acc_exit_data@layers.c:259
                    0.00%  5.5080us         3  1.8360us  1.6400us  2.0740us  acc_exit_data@layers.c:204
                    0.00%  5.5030us         2  2.7510us     932ns  4.5710us  acc_enqueue_upload@layers.c:382 (.attach.)
                    0.00%  5.4990us         1  5.4990us  5.4990us  5.4990us  acc_wait@main.c:248
                    0.00%  5.0740us         3  1.6910us  1.5010us  2.0160us  acc_exit_data@layers.c:142
                    0.00%  5.0110us         1  5.0110us  5.0110us  5.0110us  acc_wait@layers.c:356
                    0.00%  4.3540us         1  4.3540us  4.3540us  4.3540us  acc_enqueue_upload@layers.c:382 (layer[:1])
                    0.00%  3.9680us         1  3.9680us  3.9680us  3.9680us  acc_update@layers.c:356
                    0.00%  3.9520us         1  3.9520us  3.9520us  3.9520us  acc_enqueue_upload@layers.c:232 (layer[:1])
                    0.00%  3.5330us         1  3.5330us  3.5330us  3.5330us  acc_enqueue_upload@layers.c:356 (l->bias[:l->out_depth])
                    0.00%  2.1460us         1  2.1460us  2.1460us  2.1460us  acc_wait@main.c:241
                    0.00%       0ns        12       0ns       0ns       0ns  acc_delete@main.c:314
                    0.00%       0ns         2       0ns       0ns       0ns  acc_alloc@main.c:121
                    0.00%       0ns         3       0ns       0ns       0ns  acc_alloc@layers.c:169
                    0.00%       0ns         3       0ns       0ns       0ns  acc_delete@layers.c:204
                    0.00%       0ns         2       0ns       0ns       0ns  acc_create@layers.c:382
                    0.00%       0ns    100000       0ns       0ns       0ns  acc_create@layers.c:392
                    0.00%       0ns        12       0ns       0ns       0ns  acc_alloc@layers.c:42
                    0.00%       0ns        12       0ns       0ns       0ns  acc_create@layers.c:42
                    0.00%       0ns         2       0ns       0ns       0ns  acc_delete@main.c:342
                    0.00%       0ns        12       0ns       0ns       0ns  acc_create@main.c:181
                    0.00%       0ns         3       0ns       0ns       0ns  acc_create@layers.c:169
                    0.00%       0ns         3       0ns       0ns       0ns  acc_alloc@layers.c:232
                    0.00%       0ns         3       0ns       0ns       0ns  acc_alloc@layers.c:125
                    0.00%       0ns         2       0ns       0ns       0ns  acc_create@main.c:121
                    0.00%       0ns        12       0ns       0ns       0ns  acc_delete@layers.c:53
                    0.00%       0ns        12       0ns       0ns       0ns  acc_alloc@main.c:181
                    0.00%       0ns         3       0ns       0ns       0ns  acc_delete@layers.c:259
                    0.00%       0ns    100000       0ns       0ns       0ns  acc_delete@layers.c:415
                    0.00%       0ns         2       0ns       0ns       0ns  acc_alloc@layers.c:382
                    0.00%       0ns         3       0ns       0ns       0ns  acc_create@layers.c:232
                    0.00%       0ns         3       0ns       0ns       0ns  acc_delete@layers.c:142
                    0.00%       0ns         2       0ns       0ns       0ns  acc_delete@layers.c:423
                    0.00%       0ns         2       0ns       0ns       0ns  acc_alloc@layers.c:392
                    0.00%       0ns         3       0ns       0ns       0ns  acc_create@layers.c:125
```

### NV_TIME

```
$ ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
CUPTI ERROR: cuptiActivityEnable(CUPTI_ACTIVITY_KIND_KERNEL) returned: CUPTI_ERROR_INSUFFICIENT_PRIVILEGES, 
         at ../../src-cupti/prof_cuda_cupti.c:338.
Load Data time:1.192056 seconds
Create Network time:0.037300 seconds
Load Network Parameters time:0.007847 seconds
Create Ouputs time:0.000304 seconds

Net Forward total time:15.723068 seconds
    Time for conv1: 2.602402 seconds
    Time for relu1: 1.032834 seconds
    Time for pool1: 0.902946 seconds
    Time for conv2: 2.376796 seconds
    Time for relu2: 0.798665 seconds
    Time for pool2: 0.792291 seconds
    Time for conv3: 1.900151 seconds
    Time for relu3: 0.738716 seconds
    Time for pool3: 0.762574 seconds
    Time for fc: 0.787602 seconds
    Time for softmax: 3.004939 seconds

  Conv: 6.879349 seconds
  ReLU: 2.570215 seconds
  Pool: 2.457811 seconds
  FC:   0.787602 seconds
  Softmax: 3.004939 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000739 seconds
Free memory time:0.047962 seconds
Total time:17.009276 seconds
END!

Accelerator Kernel Timing data
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  make_conv_layer  NVIDIA  devicenum=0
    time(us): 217
    42: data region reached 9 times
        42: data copyin transfers: 24
             device time(us): total=217 max=26 min=3 avg=9
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  free_conv  NVIDIA  devicenum=0
    time(us): 127
    53: data region reached 9 times
        53: data copyin transfers: 18
             device time(us): total=127 max=12 min=3 avg=7
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  pad_input  NVIDIA  devicenum=0
    time(us): 0
    60: compute region reached 150000 times
        60: kernel launched 150000 times
            grid: [2560]  block: [32]
            elapsed time(us): total=2,206,008 max=3,646 min=14 avg=14
    60: data region reached 300000 times
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  conv_forward  NVIDIA  devicenum=0
    time(us): 0
    77: compute region reached 150000 times
        77: kernel launched 150000 times
            grid: [640]  block: [32x4]
            elapsed time(us): total=3,575,919 max=401 min=15 avg=23
    77: data region reached 300000 times
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  make_relu_layer  NVIDIA  devicenum=0
    time(us): 10
    125: data region reached 3 times
        125: data copyin transfers: 3
             device time(us): total=10 max=4 min=3 avg=3
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  relu_forward  NVIDIA  devicenum=0
    time(us): 0
    130: compute region reached 150000 times
        130: kernel launched 150000 times
            grid: [1]  block: [128]
            elapsed time(us): total=2,032,640 max=375 min=10 avg=13
    130: data region reached 300000 times
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  free_relu  NVIDIA  devicenum=0
    time(us): 0
    142: data region reached 3 times
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  make_pool_layer  NVIDIA  devicenum=0
    time(us): 9
    169: data region reached 3 times
        169: data copyin transfers: 3
             device time(us): total=9 max=3 min=3 avg=3
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  pool_forward  NVIDIA  devicenum=0
    time(us): 0
    174: compute region reached 150000 times
        174: kernel launched 150000 times
            grid: [80-1024]  block: [32x4]
            elapsed time(us): total=1,907,396 max=309 min=11 avg=12
    174: data region reached 300000 times
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  free_pool  NVIDIA  devicenum=0
    time(us): 0
    204: data region reached 3 times
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  make_fc_layer  NVIDIA  devicenum=0
    time(us): 33
    232: data region reached 2 times
        232: data copyin transfers: 5
             device time(us): total=33 max=12 min=3 avg=6
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  fc_forward  NVIDIA  devicenum=0
    time(us): 0
    237: compute region reached 50000 times
        237: kernel launched 50000 times
            grid: [10]  block: [32x4]
            elapsed time(us): total=606,824 max=383 min=11 avg=12
    237: data region reached 100000 times
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  free_fc  NVIDIA  devicenum=0
    time(us): 48
    259: data region reached 2 times
        259: data copyin transfers: 4
             device time(us): total=48 max=21 min=3 avg=12
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  load_conv  NVIDIA  devicenum=0
    time(us): 54
    308: update directive reached 3 times
        308: data copyin transfers: 6
             device time(us): total=54 max=22 min=3 avg=9
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  load_fc  NVIDIA  devicenum=0
    time(us): 12
    356: update directive reached 1 time
        356: data copyin transfers: 2
             device time(us): total=12 max=9 min=3 avg=6
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  make_softmax_layer  NVIDIA  devicenum=0
    time(us): 19
    382: data region reached 2 times
        382: data copyin transfers: 3
             device time(us): total=19 max=12 min=3 avg=6
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  softmax_forward  NVIDIA  devicenum=0
    time(us): 292,801
    392: compute region reached 50000 times
        392: kernel launched 50000 times
            grid: [1]  block: [10]
            elapsed time(us): total=557,109 max=46 min=10 avg=11
    392: data region reached 100000 times
        392: data copyin transfers: 100000
             device time(us): total=292,801 max=1,444 min=2 avg=2
    399: compute region reached 50000 times
        399: kernel launched 50000 times
            grid: [1]  block: [10]
            elapsed time(us): total=565,131 max=46 min=10 avg=11
    408: compute region reached 50000 times
        408: kernel launched 50000 times
            grid: [1]  block: [10]
            elapsed time(us): total=529,870 max=63 min=10 avg=10
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/layers.c
  free_softmax  NVIDIA  devicenum=0
    time(us): 37
    423: data region reached 2 times
        423: data copyin transfers: 2
             device time(us): total=37 max=22 min=15 avg=18
/home/olia/Diplomatiki/cnn-cifar10_0/serial2parallel-3.1-relu/main.c
  main  NVIDIA  devicenum=0
    time(us): 156,516
    121: data region reached 1 time
        44: kernel launched 1 time
            grid: [391]  block: [128]
            elapsed time(us): total=56 max=56 min=56 avg=56
        121: data copyin transfers: 1
             device time(us): total=154,407 max=154,407 min=154,407 avg=154,407
    181: data region reached 4 times
        44: kernel launched 1 time
            grid: [391]  block: [128]
            elapsed time(us): total=28 max=28 min=28 avg=28
    241: update directive reached 1 time
        241: data copyout transfers: 2
             device time(us): total=143 max=104 min=39 avg=71
    248: update directive reached 1 time
        248: data copyout transfers: 1
             device time(us): total=1,966 max=1,966 min=1,966 avg=1,966
    314: data region reached 4 times
    342: data region reached 1 time
```
