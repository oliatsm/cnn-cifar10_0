```
olia@krylov100:~/Diplomatiki/cnn-cifar10_0$ ./cnn-cifar10 
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.715507 seconds
CUPTI ERROR: cuptiActivityEnable(CUPTI_ACTIVITY_KIND_KERNEL) returned: CUPTI_ERROR_INSUFFICIENT_PRIVILEGES, 
         at ../../src-cupti/prof_cuda_cupti.c:338.
Load Data to device time:0.304298 seconds
Create Network time:0.040310 seconds
Load Network Parameters time:0.007767 seconds
Create Ouputs time:0.015998 seconds

Net Forward total time:576.306746 seconds
    Time for conv1: 184.509476 seconds
    Time for relu1: 0.956613 seconds
    Time for pool1: 1.072371 seconds
    Time for conv2: 291.122556 seconds
    Time for relu2: 1.048269 seconds
    Time for pool2: 0.913789 seconds
    Time for conv3: 83.046778 seconds
    Time for relu3: 1.036649 seconds
    Time for pool3: 0.876816 seconds
    Time for fc: 0.959507 seconds
    Time for softmax: 4.938006 seconds

  Conv: 558.678810 seconds
  ReLU: 3.041531 seconds
  Pool: 2.862976 seconds
  FC:   0.959507 seconds
  Softmax: 4.938006 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000000 seconds
Free memory time:0.056067 seconds
Total time:576.015679 seconds
END!

Accelerator Kernel Timing data
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  make_conv_layer  NVIDIA  devicenum=0
    time(us): 165
    37: data region reached 9 times
        37: data copyin transfers: 15
             device time(us): total=165 max=35 min=3 avg=11
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  free_conv  NVIDIA  devicenum=0
    time(us): 85
    48: data region reached 9 times
        48: data copyin transfers: 12
             device time(us): total=85 max=11 min=3 avg=7
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  make_relu_layer  NVIDIA  devicenum=0
    time(us): 14
    113: data region reached 3 times
        113: data copyin transfers: 3
             device time(us): total=14 max=6 min=4 avg=4
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  relu_forward  NVIDIA  devicenum=0
    time(us): 0
    118: compute region reached 150000 times
        118: kernel launched 150000 times
            grid: [1280]  block: [128]
            elapsed time(us): total=2,041,325 max=1,041 min=12 avg=13
    118: data region reached 300000 times
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  free_relu  NVIDIA  devicenum=0
    time(us): 0
    132: data region reached 3 times
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  make_pool_layer  NVIDIA  devicenum=0
    time(us): 9
    160: data region reached 3 times
        160: data copyin transfers: 3
             device time(us): total=9 max=3 min=3 avg=3
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  pool_forward  NVIDIA  devicenum=0
    time(us): 0
    168: compute region reached 150000 times
        171: kernel launched 150000 times
            grid: [16-20]  block: [128]
            elapsed time(us): total=1,903,071 max=677 min=11 avg=12
    168: data region reached 300000 times
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  free_pool  NVIDIA  devicenum=0
    time(us): 0
    205: data region reached 3 times
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  make_fc_layer  NVIDIA  devicenum=0
    time(us): 33
    235: data region reached 3 times
        235: data copyin transfers: 5
             device time(us): total=33 max=12 min=3 avg=6
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  fc_forward  NVIDIA  devicenum=0
    time(us): 0
    244: compute region reached 50000 times
        246: kernel launched 50000 times
            grid: [10]  block: [128]
            elapsed time(us): total=652,477 max=58 min=12 avg=13
    244: data region reached 100000 times
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  free_fc  NVIDIA  devicenum=0
    time(us): 47
    268: data region reached 3 times
        268: data copyin transfers: 4
             device time(us): total=47 max=20 min=4 avg=11
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  load_conv  NVIDIA  devicenum=0
    time(us): 56
    320: update directive reached 3 times
        320: data copyin transfers: 6
             device time(us): total=56 max=21 min=3 avg=9
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  load_fc  NVIDIA  devicenum=0
    time(us): 12
    370: update directive reached 1 time
        370: data copyin transfers: 2
             device time(us): total=12 max=9 min=3 avg=6
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  make_softmax_layer  NVIDIA  devicenum=0
    time(us): 22
    397: data region reached 2 times
        397: data copyin transfers: 3
             device time(us): total=22 max=13 min=4 avg=7
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  softmax_forward  NVIDIA  devicenum=0
    time(us): 316,821
    407: compute region reached 50000 times
        407: kernel launched 50000 times
            grid: [1280]  block: [128]
            elapsed time(us): total=707,527 max=59 min=13 avg=14
        407: reduction kernel launched 50000 times
            grid: [1]  block: [256]
            elapsed time(us): total=616,447 max=347 min=11 avg=12
    407: data region reached 100000 times
        407: data copyin transfers: 100000
             device time(us): total=316,821 max=25 min=2 avg=3
    416: compute region reached 50000 times
        416: kernel launched 50000 times
            grid: [1280]  block: [128]
            elapsed time(us): total=695,624 max=43 min=13 avg=13
        416: reduction kernel launched 50000 times
            grid: [1]  block: [256]
            elapsed time(us): total=614,814 max=50 min=11 avg=12
    424: compute region reached 50000 times
        424: kernel launched 50000 times
            grid: [1280]  block: [128]
            elapsed time(us): total=665,052 max=54 min=12 avg=13
/home/olia/Diplomatiki/cnn-cifar10_0/layers.c
  free_softmax  NVIDIA  devicenum=0
    time(us): 35
    443: data region reached 2 times
        443: data copyin transfers: 2
             device time(us): total=35 max=21 min=14 avg=17
/home/olia/Diplomatiki/cnn-cifar10_0/main.c
  main  NVIDIA  devicenum=0
    time(us): 3,239,106
    127: data region reached 1 time
        44: kernel launched 1 time
            grid: [391]  block: [128]
            elapsed time(us): total=47 max=47 min=47 avg=47
        127: data copyin transfers: 1
             device time(us): total=151,378 max=151,378 min=151,378 avg=151,378
    165: data region reached 1 time
    167: data region reached 1 time
    169: data region reached 1 time
    171: data region reached 1 time
    173: data region reached 1 time
    175: data region reached 1 time
    177: data region reached 1 time
    179: data region reached 1 time
    181: data region reached 1 time
    183: data region reached 1 time
    185: data region reached 1 time
        44: kernel launched 1 time
            grid: [391]  block: [128]
            elapsed time(us): total=36 max=36 min=36 avg=36
    202: update directive reached 50000 times
        202: data copyin transfers: 50000
             device time(us): total=1,266,830 max=1,149 min=20 avg=25
    212: update directive reached 50000 times
        212: data copyout transfers: 50000
             device time(us): total=569,250 max=411 min=9 avg=11
    218: update directive reached 50000 times
        218: data copyin transfers: 50000
             device time(us): total=532,080 max=131 min=7 avg=10
    228: update directive reached 50000 times
        228: data copyout transfers: 50000
             device time(us): total=460,179 max=42 min=7 avg=9
    234: update directive reached 50000 times
        234: data copyin transfers: 50000
             device time(us): total=257,483 max=42 min=4 avg=5
    255: update directive reached 1 time
        255: data copyout transfers: 1
             device time(us): total=1,906 max=1,906 min=1,906 avg=1,906
    310: data region reached 1 time
    312: data region reached 1 time
    314: data region reached 1 time
    316: data region reached 1 time
    318: data region reached 1 time
    320: data region reached 1 time
    322: data region reached 1 time
    324: data region reached 1 time
    326: data region reached 1 time
    328: data region reached 1 time
    330: data region reached 1 time
    348: data region reached 1 time
    ```
```
    $ nvprof ./cnn-cifar10 
CNN for 1200 images
Loading input batch 1...
Load Data time:0.019853 seconds
==2744568== NVPROF is profiling process 2744568, command: ./cnn-cifar10
Load Data to device time:0.223540 seconds
Create Network time:0.038436 seconds
Load Network Parameters time:0.008331 seconds
Create Ouputs time:0.002067 seconds

Net Forward total time:2.769450 seconds
    Time for conv1: 1.233335 seconds
    Time for relu1: 0.067530 seconds
    Time for pool1: 0.186459 seconds
    Time for conv2: 0.513872 seconds
    Time for relu2: 0.058870 seconds
    Time for pool2: 0.085990 seconds
    Time for conv3: 0.209081 seconds
    Time for relu3: 0.055108 seconds
    Time for pool3: 0.063483 seconds
    Time for fc: 0.063884 seconds
    Time for softmax: 0.200057 seconds

  Conv: 1.956288 seconds
  ReLU: 0.181508 seconds
  Pool: 0.335932 seconds
  FC:   0.063884 seconds
  Softmax: 0.200057 seconds

Net Accuracy: 78.25 % 
Net Accuracy time:0.000048 seconds
Free memory time:0.007249 seconds
Total time:3.029268 seconds
END!
==2744568== Profiling application: ./cnn-cifar10
==2744568== Profiling result:
            Type  Time(%)      Time     Calls       Avg       Min       Max  Name
 GPU activities:   84.06%  851.75ms      3600  236.60us  44.287us  561.12us  _8layers_c_conv_forward_85_gpu
                   10.70%  108.40ms      3600  30.112us  5.4710us  75.776us  _8layers_c_pool_forward_190_gpu
                    1.27%  12.912ms      3600  3.5860us  2.4950us  12.959us  _8layers_c_add_padding_62_gpu
                    1.25%  12.615ms      3600  3.5040us  3.3910us  4.3520us  _8layers_c_relu_forward_137_gpu
                    0.48%  4.8620ms      1200  4.0510us  3.9360us  4.9600us  _8layers_c_softmax_forward_421_gpu
                    0.47%  4.8070ms      1200  4.0050us  3.9030us  5.2800us  _8layers_c_softmax_forward_428_gpu
                    0.41%  4.1627ms      1200  3.4680us  3.3910us  4.4160us  _8layers_c_softmax_forward_436_gpu
                    0.37%  3.7070ms      1200  3.0890us  3.0070us  4.3520us  _8layers_c_fc_forward_260_gpu
                    0.34%  3.4100ms        47  72.553us     640ns  3.3587ms  [CUDA memcpy HtoD]
                    0.33%  3.3193ms      1200  2.7660us  2.6870us  3.4880us  _8layers_c_softmax_forward_428_gpu__red
                    0.32%  3.2657ms      1200  2.7210us  2.6550us  3.4560us  _8layers_c_softmax_forward_421_gpu__red
                    0.00%  4.6090us         1  4.6090us  4.6090us  4.6090us  [CUDA memcpy DtoH]
                    0.00%  4.1920us         2  2.0960us  1.8560us  2.3360us  _21______src_cuda_fill_c___pgi_uacc_cuda_fill_44_gpu
      API calls:   75.92%  1.05030s     36040  29.142us     719ns  571.37us  cuStreamSynchronize
                   10.73%  148.45ms         1  148.45ms  148.45ms  148.45ms  cuDevicePrimaryCtxRetain
                    9.00%  124.46ms     21602  5.7610us  3.5120us  1.1005ms  cuLaunchKernel
                    2.73%  37.747ms         1  37.747ms  37.747ms  37.747ms  cuMemHostAlloc
                    0.76%  10.456ms     21600     484ns     210ns  849.56us  cuOccupancyMaxActiveBlocksPerMultiprocessor
                    0.36%  4.9229ms     19211     256ns     126ns  866.09us  cuDeviceGetAttribute
                    0.28%  3.8526ms        47  81.971us  3.0130us  3.5515ms  cuMemcpyHtoDAsync
                    0.09%  1.2850ms         1  1.2850ms  1.2850ms  1.2850ms  cuMemAllocHost
                    0.06%  862.29us      2437     353ns     241ns  16.565us  cuPointerGetAttributes
                    0.04%  512.96us         2  256.48us  98.402us  414.55us  cuModuleLoadDataEx
                    0.03%  407.32us        41  9.9340us  2.0520us  133.87us  cuMemAlloc
                    0.01%  136.32us         1  136.32us  136.32us  136.32us  cuMemcpyDtoHAsync
                    0.00%  24.643us        12  2.0530us     367ns  15.315us  cuModuleGetFunction
                    0.00%  13.916us         1  13.916us  13.916us  13.916us  cuDeviceGetPCIBusId
                    0.00%  9.0580us         1  9.0580us  9.0580us  9.0580us  cuCtxGetCurrent
                    0.00%  1.6500us         3     550ns     253ns     989ns  cuCtxSetCurrent
                    0.00%  1.4590us         3     486ns     168ns  1.0970us  cuDeviceGetCount
                    0.00%     929ns         2     464ns     232ns     697ns  cuDeviceGet
                    0.00%     550ns         3     183ns     149ns     248ns  cuDriverGetVersion
                    0.00%     516ns         1     516ns     516ns     516ns  cuDeviceComputeCapability
 OpenACC (excl):   58.57%  860.06ms      3600  238.90us  5.1460us  572.09us  acc_wait@layers.c:85
                    8.05%  118.26ms      3600  32.850us  2.2240us  1.0035ms  acc_wait@layers.c:190
                    2.58%  37.937ms        12  3.1614ms  7.0610us  37.769ms  acc_enter_data@layers.c:44
                    2.14%  31.463ms      7200  4.3690us  1.7700us  767.25us  acc_wait@layers.c:62
                    2.09%  30.687ms      7200  4.2620us  1.8030us  831.72us  acc_wait@layers.c:137
                    1.87%  27.392ms      3600  7.6080us  4.8130us  873.80us  acc_enqueue_launch@layers.c:137 (_8layers_c_relu_forward_137_gpu)
                    1.83%  26.830ms      3600  7.4520us  4.6760us  1.1025ms  acc_enqueue_launch@layers.c:85 (_8layers_c_conv_forward_85_gpu)
                    1.81%  26.591ms      3600  7.3860us  4.8020us  887.62us  acc_enqueue_launch@layers.c:62 (_8layers_c_add_padding_62_gpu)
                    1.69%  24.798ms      3600  6.8880us  4.6650us  113.91us  acc_enqueue_launch@layers.c:190 (_8layers_c_pool_forward_190_gpu)
                    1.10%  16.162ms      3600  4.4890us  2.7260us  955.96us  acc_compute_construct@layers.c:62
                    1.04%  15.280ms      3600  4.2440us  2.7440us  989.29us  acc_compute_construct@layers.c:137
                    0.83%  12.176ms      3600  3.3820us  2.0150us  992.97us  acc_enter_data@layers.c:137
                    0.77%  11.370ms      3600  3.1580us  1.7630us  1.1005ms  acc_compute_construct@layers.c:187
                    0.76%  11.208ms      3600  3.1130us  1.9990us  1.0784ms  acc_enter_data@layers.c:83
                    0.70%  10.299ms      3600  2.8600us  2.0430us  20.437us  acc_enter_data@layers.c:187
                    0.69%  10.143ms      3600  2.8170us  1.7800us  868.74us  acc_compute_construct@layers.c:83
                    0.69%  10.114ms      2400  4.2130us  1.8050us  901.91us  acc_wait@layers.c:421
                    0.67%  9.8432ms      3600  2.7340us  1.7650us  783.54us  acc_wait@layers.c:187
                    0.65%  9.5833ms      1200  7.9860us  4.8450us  1.0051ms  acc_enter_data@layers.c:421
                    0.65%  9.4759ms      1200  7.8960us  5.0960us  762.72us  acc_enqueue_launch@layers.c:421 (_8layers_c_softmax_forward_421_gpu)
                    0.62%  9.1702ms      1200  7.6410us  4.6800us  962.95us  acc_enqueue_launch@layers.c:428 (_8layers_c_softmax_forward_428_gpu)
                    0.62%  9.1427ms      1200  7.6180us  4.6840us  857.10us  acc_enqueue_launch@layers.c:260 (_8layers_c_fc_forward_260_gpu)
                    0.61%  8.9501ms      3600  2.4860us  1.7160us  142.76us  acc_enter_data@layers.c:62
                    0.61%  8.9498ms      3600  2.4860us  1.7370us  18.573us  acc_wait@layers.c:83
                    0.60%  8.7391ms      3600  2.4270us  1.7240us  13.430us  acc_exit_data@layers.c:187
                    0.59%  8.6180ms      3600  2.3930us  1.7210us  18.547us  acc_exit_data@layers.c:137
                    0.58%  8.5883ms      3600  2.3850us  1.6270us  22.375us  acc_exit_data@layers.c:83
                    0.56%  8.2593ms      1200  6.8820us  4.7340us  34.803us  acc_enqueue_launch@layers.c:436 (_8layers_c_softmax_forward_436_gpu)
                    0.55%  8.0645ms      3600  2.2400us  1.3870us  875.95us  acc_exit_data@layers.c:62
                    0.55%  8.0292ms      1200  6.6900us  4.4910us  22.390us  acc_enqueue_launch@layers.c:421 (_8layers_c_softmax_forward_421_gpu__red)
                    0.54%  7.9819ms      1200  6.6510us  4.5170us  41.588us  acc_enqueue_launch@layers.c:428 (_8layers_c_softmax_forward_428_gpu__red)
                    0.49%  7.2653ms      1200  6.0540us  3.8530us  790.31us  acc_exit_data@layers.c:421
                    0.47%  6.9080ms      1200  5.7560us  4.3600us  21.985us  acc_wait@layers.c:436
                    0.43%  6.3438ms      1200  5.2860us  3.9800us  21.692us  acc_wait@layers.c:260
                    0.43%  6.2497ms      1200  5.2080us  3.0810us  12.102us  acc_wait@layers.c:428
                    0.38%  5.5194ms      1200  4.5990us  3.2130us  91.839us  acc_compute_construct@layers.c:421
                    0.36%  5.2826ms      1200  4.4020us  2.5350us  781.72us  acc_compute_construct@layers.c:436
                    0.36%  5.2624ms      1200  4.3850us  2.9520us  110.97us  acc_compute_construct@layers.c:428
                    0.29%  4.2115ms      1200  3.5090us  2.0670us  808.82us  acc_enter_data@layers.c:258
                    0.24%  3.5553ms         1  3.5553ms  3.5553ms  3.5553ms  acc_enqueue_upload@main.c:130 (input[:1200][:3072])
                    0.21%  3.0227ms      1200  2.5180us  1.7760us  7.5140us  acc_compute_construct@layers.c:258
                    0.20%  2.9241ms      1200  2.4360us  1.7310us  5.6740us  acc_wait@layers.c:258
                    0.19%  2.7691ms      1200  2.3070us  1.6530us  8.5510us  acc_exit_data@layers.c:258
                    0.13%  1.8384ms         1  1.8384ms  1.8384ms  1.8384ms  acc_enter_data@main.c:188
                    0.08%  1.1796ms         1  1.1796ms  1.1796ms  1.1796ms  acc_enter_data@main.c:130
                    0.03%  453.28us         1  453.28us  453.28us  453.28us  acc_device_init@main.c:130
                    0.01%  142.42us         1  142.42us  142.42us  142.42us  acc_enqueue_download@main.c:262 (O11[:1200][:L11->out_size])
                    0.01%  119.89us         1  119.89us  119.89us  119.89us  acc_update@main.c:262
                    0.01%  98.062us        18  5.4470us  1.9430us  9.7640us  acc_enqueue_upload@layers.c:56 (.detach.)
                    0.01%  83.980us         2  41.990us  38.090us  45.890us  acc_enqueue_launch@(runtime):44 (_21______src_cuda_fill_c___pgi_uacc_cuda_fill_44_gpu)
                    0.01%  82.747us        18  4.5970us     838ns  26.506us  acc_enqueue_upload@layers.c:44 (.attach.)
                    0.00%  68.413us        12  5.7010us  4.2760us  9.3480us  acc_wait@layers.c:44
                    0.00%  67.288us         1  67.288us  67.288us  67.288us  acc_exit_data@main.c:317
                    0.00%  66.354us         1  66.354us  66.354us  66.354us  acc_exit_data@main.c:355
                    0.00%  66.315us         1  66.315us  66.315us  66.315us  acc_wait@main.c:130
                    0.00%  56.313us        12  4.6920us  3.0650us  5.5570us  acc_exit_data@layers.c:56
                    0.00%  44.589us         2  22.294us  9.4590us  35.130us  acc_enqueue_upload@layers.c:455 (.detach.)
                    0.00%  41.652us         3  13.884us  12.364us  16.651us  acc_enter_data@layers.c:132
                    0.00%  40.783us         3  13.594us  7.4390us  18.506us  acc_enqueue_upload@layers.c:334 (l->weights[:l->in_depth*(l->num_filters*(l->filter_width*l->filter_width))])
                    0.00%  40.596us         3  13.532us  8.3960us  20.364us  acc_enter_data@layers.c:179
                    0.00%  32.199us         3  10.733us  7.3620us  12.654us  acc_enter_data@layers.c:249
                    0.00%  30.260us         3  10.086us  7.2820us  12.040us  acc_enqueue_upload@layers.c:44 (layer->padded_input[:layer->padded_size])
                    0.00%  27.019us         2  13.509us  12.064us  14.955us  acc_enter_data@layers.c:411
                    0.00%  23.336us         4  5.8340us  2.0160us  10.144us  acc_enqueue_upload@layers.c:282 (.detach.)
                    0.00%  21.722us         1  21.722us  21.722us  21.722us  acc_enter_data@main.c:168
                    0.00%  21.648us         3  7.2160us  3.8250us  9.2690us  acc_wait@layers.c:334
                    0.00%  18.243us         3  6.0810us  4.0010us  10.112us  acc_enqueue_upload@layers.c:44 (layer[:1])
                    0.00%  15.032us         3  5.0100us  3.1900us  6.4490us  acc_exit_data@layers.c:282
                    0.00%  14.950us         3  4.9830us  2.8210us  8.5990us  acc_update@layers.c:334
                    0.00%  14.740us         2  7.3700us  3.3380us  11.402us  acc_exit_data@layers.c:455
                    0.00%  14.329us         3  4.7760us  4.6490us  4.9560us  acc_wait@layers.c:132
                    0.00%  13.941us         1  13.941us  13.941us  13.941us  acc_enter_data@main.c:186
                    0.00%  13.405us         3  4.4680us  4.1810us  4.7170us  acc_wait@layers.c:249
                    0.00%  13.284us         3  4.4280us  4.1650us  4.9410us  acc_enqueue_upload@layers.c:132 (layer[:1])
                    0.00%  12.576us         3  4.1920us  2.5450us  5.1970us  acc_wait@layers.c:179
                    0.00%  12.120us         3  4.0400us  3.8700us  4.3140us  acc_enqueue_upload@layers.c:334 (l->bias[:l->out_depth])
                    0.00%  11.827us         3  3.9420us  3.8960us  4.0280us  acc_enqueue_upload@layers.c:179 (layer[:1])
                    0.00%  11.595us         1  11.595us  11.595us  11.595us  acc_enter_data@main.c:172
                    0.00%  11.538us         1  11.538us  11.538us  11.538us  acc_enter_data@main.c:174
                    0.00%  11.387us         1  11.387us  11.387us  11.387us  acc_enter_data@main.c:170
                    0.00%  11.355us         1  11.355us  11.355us  11.355us  acc_enter_data@main.c:182
                    0.00%  11.304us         1  11.304us  11.304us  11.304us  acc_enter_data@main.c:176
                    0.00%  11.195us         3  3.7310us  3.4280us  4.3000us  acc_exit_data@layers.c:219
                    0.00%  10.958us         1  10.958us  10.958us  10.958us  acc_enter_data@main.c:178
                    0.00%  10.558us         3  3.5190us  3.0600us  4.2780us  acc_exit_data@layers.c:151
                    0.00%  10.467us         4  2.6160us     911ns  4.4300us  acc_enqueue_upload@layers.c:249 (.attach.)
                    0.00%  9.8810us         1  9.8810us  9.8810us  9.8810us  acc_enqueue_upload@layers.c:384 (l->weights[:l->out_depth*l->in_neurons])
                    0.00%  9.1110us         2  4.5550us  4.4270us  4.6840us  acc_wait@layers.c:411
                    0.00%  6.5420us         1  6.5420us  6.5420us  6.5420us  acc_enter_data@main.c:184
                    0.00%  6.2300us         1  6.2300us  6.2300us  6.2300us  acc_enter_data@main.c:180
                    0.00%  5.6960us         1  5.6960us  5.6960us  5.6960us  acc_wait@main.c:188
                    0.00%  5.6280us         2  2.8140us     893ns  4.7350us  acc_enqueue_upload@layers.c:411 (.attach.)
                    0.00%  5.2720us         1  5.2720us  5.2720us  5.2720us  acc_wait@main.c:262
                    0.00%  4.9270us         1  4.9270us  4.9270us  4.9270us  acc_wait@layers.c:384
                    0.00%  4.7280us         1  4.7280us  4.7280us  4.7280us  acc_enqueue_upload@layers.c:249 (layer[:1])
                    0.00%  4.3320us         1  4.3320us  4.3320us  4.3320us  acc_exit_data@main.c:319
                    0.00%  4.2320us         1  4.2320us  4.2320us  4.2320us  acc_enqueue_upload@layers.c:411 (layer[:1])
                    0.00%  3.9610us         1  3.9610us  3.9610us  3.9610us  acc_enqueue_upload@layers.c:384 (l->bias[:l->out_depth])
                    0.00%  3.7200us         1  3.7200us  3.7200us  3.7200us  acc_update@layers.c:384
                    0.00%  3.6800us         1  3.6800us  3.6800us  3.6800us  acc_exit_data@main.c:327
                    0.00%  3.5820us         1  3.5820us  3.5820us  3.5820us  acc_exit_data@main.c:331
                    0.00%  3.5770us         1  3.5770us  3.5770us  3.5770us  acc_exit_data@main.c:323
                    0.00%  3.4450us         1  3.4450us  3.4450us  3.4450us  acc_exit_data@main.c:335
                    0.00%  3.4310us         1  3.4310us  3.4310us  3.4310us  acc_exit_data@main.c:325
                    0.00%  3.4290us         1  3.4290us  3.4290us  3.4290us  acc_exit_data@main.c:321
                    0.00%  3.2760us         1  3.2760us  3.2760us  3.2760us  acc_exit_data@main.c:329
                    0.00%  3.2270us         1  3.2270us  3.2270us  3.2270us  acc_exit_data@main.c:333
                    0.00%  3.2030us         1  3.2030us  3.2030us  3.2030us  acc_exit_data@main.c:337
                    0.00%  1.8850us         1  1.8850us  1.8850us  1.8850us  acc_wait@main.c:168
                    0.00%  1.8090us         1  1.8090us  1.8090us  1.8090us  acc_wait@main.c:170
                    0.00%  1.6510us         1  1.6510us  1.6510us  1.6510us  acc_wait@main.c:180
                    0.00%  1.6260us         1  1.6260us  1.6260us  1.6260us  acc_wait@main.c:176
                    0.00%  1.6060us         1  1.6060us  1.6060us  1.6060us  acc_wait@main.c:172
                    0.00%  1.5510us         1  1.5510us  1.5510us  1.5510us  acc_wait@main.c:174
                    0.00%  1.5220us         1  1.5220us  1.5220us  1.5220us  acc_wait@main.c:178
                    0.00%  1.4910us         1  1.4910us  1.4910us  1.4910us  acc_wait@main.c:182
                    0.00%  1.4910us         1  1.4910us  1.4910us  1.4910us  acc_wait@main.c:186
                    0.00%  1.3780us         1  1.3780us  1.3780us  1.3780us  acc_wait@main.c:184
                    0.00%       0ns         3       0ns       0ns       0ns  acc_delete@layers.c:151
                    0.00%       0ns         2       0ns       0ns       0ns  acc_delete@main.c:317
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:319
                    0.00%       0ns         3       0ns       0ns       0ns  acc_create@layers.c:132
                    0.00%       0ns         2       0ns       0ns       0ns  acc_create@layers.c:411
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:321
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:323
                    0.00%       0ns         3       0ns       0ns       0ns  acc_delete@layers.c:282
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:325
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:327
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:329
                    0.00%       0ns      2400       0ns       0ns       0ns  acc_delete@layers.c:445
                    0.00%       0ns         2       0ns       0ns       0ns  acc_alloc@main.c:130
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:168
                    0.00%       0ns      2400       0ns       0ns       0ns  acc_create@layers.c:421
                    0.00%       0ns         3       0ns       0ns       0ns  acc_alloc@layers.c:179
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:331
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:333
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:335
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:337
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:170
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:172
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:174
                    0.00%       0ns         2       0ns       0ns       0ns  acc_delete@layers.c:455
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:176
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:178
                    0.00%       0ns         3       0ns       0ns       0ns  acc_delete@layers.c:219
                    0.00%       0ns        12       0ns       0ns       0ns  acc_alloc@layers.c:44
                    0.00%       0ns        12       0ns       0ns       0ns  acc_create@layers.c:44
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:180
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:182
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:184
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:186
                    0.00%       0ns         2       0ns       0ns       0ns  acc_create@main.c:188
                    0.00%       0ns         2       0ns       0ns       0ns  acc_delete@main.c:355
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:168
                    0.00%       0ns         3       0ns       0ns       0ns  acc_create@layers.c:179
                    0.00%       0ns         3       0ns       0ns       0ns  acc_alloc@layers.c:249
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:170
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:172
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:174
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:176
                    0.00%       0ns        12       0ns       0ns       0ns  acc_delete@layers.c:56
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:178
                    0.00%       0ns         3       0ns       0ns       0ns  acc_alloc@layers.c:132
                    0.00%       0ns         2       0ns       0ns       0ns  acc_alloc@layers.c:411
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:180
                    0.00%       0ns         2       0ns       0ns       0ns  acc_create@main.c:130
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:182
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:184
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:186
                    0.00%       0ns         2       0ns       0ns       0ns  acc_alloc@main.c:188
                    0.00%       0ns         2       0ns       0ns       0ns  acc_alloc@layers.c:421
                    0.00%       0ns         3       0ns       0ns       0ns  acc_create@layers.c:249
```