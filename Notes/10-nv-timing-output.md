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