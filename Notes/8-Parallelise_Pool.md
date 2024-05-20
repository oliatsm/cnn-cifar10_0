```
void pool_forward(float * restrict X, Pool_Layer * l,float * restrict Y)

#pragma acc kernels present (X,l,Y)

```
```
pool_forward:
    162, Generating update device(X[:l->in_depth*(l->in_height*l->in_width)])
         Generating present(l[:],Y[:],X[:])
    164, Loop carried dependence due to exposed use of Y prevents parallelization
         Generating NVIDIA GPU code
        164, #pragma acc loop seq
        166, #pragma acc loop seq
        168, #pragma acc loop seq
        172, #pragma acc loop vector(128) collapse(2) /* threadIdx.x */
             Generating implicit reduction(max:max)
        173,   /* threadIdx.x auto-collapsed */
    166, Loop carried dependence due to exposed use of Y prevents parallelization
    168, Loop carried dependence due to exposed use of Y prevents parallelization
    172, Loop is parallelizable
    173, Loop is parallelizable
    190, Generating update self(Y[:l->out_size])
```

---

## Pool_forward

```c
void pool_forward(float* restrict X, Pool_Layer* l, float* restrict Y) {
#pragma acc update device(X[0:l->in_width*l->in_height*l->in_depth])
#pragma acc kernels present(X,l,Y)
{
            // For each output feature map
#pragma acc loop independent
    for (int m = 0; m < l->out_depth; m++) {
        for (int j = 0; j < l->out_height; j++) {
            for (int i = 0; i < l->out_width; i++) {
                int y_idx = i + l->out_width * (j + m * l->out_height); // Output index
                // Find Max in pooling filter
                float max = -INFINITY;
                for (int p_j = 0; p_j < l->pool_width; p_j++) {
                    for (int p_i = 0; p_i < l->pool_width; p_i++) {
                        int x_j = j * l->stride + p_j;                            // Input height index, increased by stride
                        int x_i = i * l->stride + p_i;                            // Input width index, increased by stride
                        int x_idx = x_i + (x_j + m * l->in_height) * l->in_width; // Input index
                        // If in range of input
                        if (x_i >= 0 && x_j >= 0 && x_i < l->in_width && x_j < l->in_height) {
                            if (X[x_idx] > max) {
                                max = X[x_idx];
                            } // if max
                        } // if in range
                    } // for p_i
                } // for p_j
                Y[y_idx] = max;
            } // for i
        } // for j
    } // for m
}
#pragma acc update self(Y[0:l->out_size])

}
```
nvc info:
```
pool_forward:
    161, Generating update device(X[:l->in_depth*(l->in_height*l->in_width)])
         Generating present(l[:],Y[:],X[:])
    164, Loop is parallelizable
         Generating NVIDIA GPU code
        164, #pragma acc loop gang /* blockIdx.x */
        165, #pragma acc loop seq
        166, #pragma acc loop seq
        171, #pragma acc loop vector(128) collapse(2) /* threadIdx.x */
             Generating implicit reduction(max:max)
        172,   /* threadIdx.x auto-collapsed */
    165, Loop carried dependence of Y-> prevents parallelization
         Loop carried backward dependence of Y-> prevents vectorization
    166, Loop carried dependence of Y-> prevents parallelization
         Loop carried backward dependence of Y-> prevents vectorization
    171, Loop is parallelizable
    172, Loop is parallelizable
    191, Generating update self(Y[:l->out_size])
```

```
olia@krylov100:~/Diplomatiki/cnn-cifar10_0$ nvprof ./cnn-cifar10 
CNN for 1200 images
Loading input batch 1...
Load Data time:0.053188 seconds
==473701== NVPROF is profiling process 473701, command: ./cnn-cifar10
Load Data to device time:0.269779 seconds
Create Network time:0.072155 seconds
Load Network Parameters time:0.012003 seconds
Create Ouputs time:0.000000 seconds
Net Forward total time:107.372108 seconds
Net Accuracy: 78.25 % 
Net Accuracy time:0.004027 seconds
Free memory time:0.000000 seconds
Total time:107.676884 seconds
END!
==473701== Profiling application: ./cnn-cifar10
==473701== Profiling result:
            Type  Time(%)      Time     Calls       Avg       Min       Max  Name
 GPU activities:   97.63%  9.72138s      3600  2.7004ms  270.18us  9.4066ms  _8layers_c_pool_forward_164_gpu
                    0.64%  63.395ms      3600  17.609us  13.632us  23.392us  _8layers_c_relu_forward_109_gpu
                    0.40%  39.639ms      8438  4.6970us     640ns  3.0417ms  [CUDA memcpy HtoD]
                    0.27%  27.170ms      1200  22.641us  20.128us  26.273us  _8layers_c_softmax_forward_401_gpu
                    0.27%  26.668ms      1200  22.223us  19.680us  25.952us  _8layers_c_softmax_forward_392_gpu
                    0.27%  26.571ms     10800  2.4600us  1.0560us  19.136us  [CUDA memcpy DtoH]
                    0.19%  18.874ms      1200  15.728us  13.344us  19.265us  _8layers_c_softmax_forward_407_gpu
                    0.12%  12.238ms      1200  10.198us  9.6320us  12.992us  _8layers_c_softmax_forward_401_gpu__red
                    0.12%  12.099ms      1200  10.082us  9.4080us  12.864us  _8layers_c_softmax_forward_392_gpu__red
                    0.09%  8.8297ms      3600  2.4520us     639ns  14.497us  [CUDA memset]
                    0.00%  4.2240us         2  2.1120us  2.1120us  2.1120us  _21______src_cuda_fill_c___pgi_uacc_cuda_fill_44_gpu
      API calls:   97.22%  45.2037s     40836  1.1070ms     595ns  11.471ms  cuStreamSynchronize
                    1.39%  644.30ms     10800  59.657us  10.592us  1.0696ms  cuMemcpyDtoHAsync
                    0.50%  234.04ms      8438  27.736us  2.9550us  5.1907ms  cuMemcpyHtoDAsync
                    0.37%  171.39ms     13202  12.981us  3.6710us  1.1629ms  cuLaunchKernel
                    0.36%  165.63ms         1  165.63ms  165.63ms  165.63ms  cuDevicePrimaryCtxRetain
                    0.08%  36.638ms         1  36.638ms  36.638ms  36.638ms  cuMemHostAlloc
                    0.04%  17.847ms      3600  4.9570us  2.4120us  92.015us  cuMemsetD32Async
                    0.02%  9.3067ms     14400     646ns     182ns  58.701us  cuOccupancyMaxActiveBlocksPerMultiprocessor
                    0.02%  7.2850ms     10811     673ns     133ns  794.57us  cuDeviceGetAttribute
                    0.01%  3.7313ms         2  1.8656ms  1.3943ms  2.3370ms  cuModuleLoadDataEx
                    0.00%  1.2291ms         1  1.2291ms  1.2291ms  1.2291ms  cuMemAllocHost
                    0.00%  852.03us      2434     350ns     239ns  12.013us  cuPointerGetAttributes
                    0.00%  535.60us        37  14.475us  2.1950us  132.86us  cuMemAlloc
                    0.00%  8.8660us         1  8.8660us  8.8660us  8.8660us  cuDeviceGetPCIBusId
                    0.00%  8.5390us         1  8.5390us  8.5390us  8.5390us  cuCtxGetCurrent
                    0.00%  7.5930us         9     843ns     443ns  1.8050us  cuModuleGetFunction
                    0.00%  1.6310us         3     543ns     192ns  1.0390us  cuCtxSetCurrent
                    0.00%  1.4730us         3     491ns     166ns  1.0910us  cuDeviceGetCount
                    0.00%     705ns         3     235ns     145ns     363ns  cuDriverGetVersion
                    0.00%     614ns         2     307ns     154ns     460ns  cuDeviceGet
                    0.00%     378ns         1     378ns     378ns     378ns  cuDeviceComputeCapability
 OpenACC (excl):   33.05%  15.4505s      3600  4.2918ms  240.70us  11.472ms  acc_wait@layers.c:164
                   20.07%  9.38058s     10800  868.57us  1.2810us  4.3329ms  acc_wait@layers.c:109
                   13.97%  6.52996s      3600  1.8139ms  2.5280us  2.9067ms  acc_wait@layers.c:392
                   12.26%  5.73151s      7200  796.04us  1.2120us  2.5001ms  acc_wait@layers.c:161
                    9.13%  4.26766s      2400  1.7782ms  2.2310us  2.9086ms  acc_wait@layers.c:401
                    8.20%  3.83275s      3600  1.0647ms  1.7590us  2.4991ms  acc_wait@layers.c:407
                    0.54%  252.15ms      3600  70.042us  13.182us  1.0703ms  acc_enqueue_download@layers.c:118 (Y[:l->out_size])
                    0.53%  246.31ms      3600  68.418us  11.303us  1.0099ms  acc_enqueue_download@layers.c:191 (Y[:l->out_size])
                    0.33%  153.59ms      3600  42.664us  7.4750us  804.10us  acc_enqueue_upload@layers.c:109 (X[:l->out_size])
                    0.21%  96.692ms      3600  26.858us  5.8830us  841.47us  acc_enqueue_launch@layers.c:109 (_8layers_c_relu_forward_109_gpu)
                    0.18%  83.638ms      3600  23.232us  4.8070us  817.95us  acc_enqueue_upload@layers.c:161 (X[:l->in_depth*(l->in_height*l->in_width)])
                    0.13%  63.032ms      1200  52.526us  12.170us  1.0158ms  acc_enqueue_download@layers.c:417 (Y[:l->out_size])
                    0.12%  55.594ms      3600  15.442us  5.2380us  1.1660ms  acc_enqueue_launch@layers.c:164 (_8layers_c_pool_forward_164_gpu)
                    0.12%  53.904ms      1200  44.919us  11.431us  997.21us  acc_enqueue_download@layers.c:407 (total)
                    0.11%  49.993ms      1200  41.660us  12.738us  857.03us  acc_enqueue_download@layers.c:398 (max)
                    0.10%  45.038ms      3600  12.510us  2.0080us  242.91us  acc_update@layers.c:109
                    0.08%  36.822ms         9  4.0914ms  12.346us  36.673ms  acc_enter_data@layers.c:37
                    0.06%  30.383ms      3600  8.4390us  2.7520us  717.04us  acc_compute_construct@layers.c:109
                    0.05%  21.759ms      3600  6.0440us  1.6540us  159.13us  acc_exit_data@layers.c:161
                    0.04%  20.666ms      1200  17.222us  5.9400us  794.04us  acc_enqueue_upload@layers.c:392 (X[:l->in_depth*(l->in_height*l->in_width)])
                    0.04%  20.089ms      3600  5.5800us  2.2950us  101.33us  acc_enter_data@layers.c:109
                    0.04%  19.217ms         9  2.1352ms  1.3632ms  2.3667ms  acc_wait@layers.c:37
                    0.04%  18.273ms      3600  5.0750us  1.6940us  797.69us  acc_compute_construct@layers.c:161
                    0.04%  18.130ms      1200  15.108us  8.0820us  803.15us  acc_enqueue_launch@layers.c:392 (_8layers_c_softmax_forward_392_gpu)
                    0.03%  15.850ms      3600  4.4020us  1.4880us  81.116us  acc_update@layers.c:191
                    0.03%  15.460ms      3600  4.2940us  2.0790us  779.74us  acc_enter_data@layers.c:161
                    0.03%  14.640ms      3600  4.0660us  1.7670us  144.61us  acc_wait@layers.c:191
                    0.03%  14.303ms      3600  3.9730us  1.5280us  827.50us  acc_update@layers.c:118
                    0.03%  14.221ms      3600  3.9500us  1.6830us  158.59us  acc_exit_data@layers.c:109
                    0.03%  12.547ms      1200  10.455us  5.6730us  169.90us  acc_enter_data@layers.c:392
                    0.03%  11.897ms      1200  9.9140us  5.1870us  103.68us  acc_enqueue_upload@layers.c:392 (max)
                    0.02%  11.403ms      3600  3.1670us  1.8170us  822.33us  acc_wait@layers.c:118
                    0.02%  11.395ms      3600  3.1650us  1.4770us  47.334us  acc_update@layers.c:161
                    0.02%  10.383ms      1200  8.6520us  6.0280us  69.699us  acc_enqueue_launch@layers.c:401 (_8layers_c_softmax_forward_401_gpu)
                    0.02%  9.0600ms      1200  7.5490us  5.2510us  57.681us  acc_enqueue_launch@layers.c:392 (_8layers_c_softmax_forward_392_gpu__red)
                    0.02%  9.0514ms      1200  7.5420us  5.5160us  60.983us  acc_enqueue_launch@layers.c:407 (_8layers_c_softmax_forward_407_gpu)
                    0.02%  8.6960ms      1200  7.2460us  4.7840us  655.33us  acc_enqueue_launch@layers.c:401 (_8layers_c_softmax_forward_401_gpu__red)
                    0.02%  8.1817ms      1200  6.8180us  4.4010us  81.072us  acc_exit_data@layers.c:392
                    0.02%  7.7913ms      1200  6.4920us  3.8850us  764.56us  acc_enter_data@layers.c:401
                    0.02%  7.1774ms      1200  5.9810us  3.8620us  103.63us  acc_compute_construct@layers.c:392
                    0.02%  7.0854ms         3  2.3618ms  2.3510ms  2.3698ms  acc_wait@layers.c:104
                    0.02%  7.0812ms         3  2.3604ms  2.3536ms  2.3666ms  acc_wait@layers.c:153
                    0.02%  7.0533ms      1200  5.8770us  4.1760us  755.55us  acc_enter_data@layers.c:407
                    0.01%  6.8044ms      1200  5.6700us  2.6700us  100.57us  acc_update@layers.c:392
                    0.01%  6.1193ms      1200  5.0990us  3.0940us  764.77us  acc_compute_construct@layers.c:401
                    0.01%  5.7970ms      1200  4.8300us  3.3950us  93.100us  acc_enqueue_upload@layers.c:401 (total)
                    0.01%  5.5899ms      1200  4.6580us  3.4310us  64.139us  acc_exit_data@layers.c:401
                    0.01%  5.1945ms         1  5.1945ms  5.1945ms  5.1945ms  acc_enqueue_upload@main.c:124 (input[:1200][:3072])
                    0.01%  5.1607ms      1200  4.3000us  2.7240us  827.20us  acc_exit_data@layers.c:407
                    0.01%  4.9562ms      1200  4.1300us  3.1430us  83.696us  acc_enqueue_upload@layers.c:407 (total)
                    0.01%  4.3615ms      1200  3.6340us  2.7480us  28.483us  acc_compute_construct@layers.c:407
                    0.01%  4.0612ms         3  1.3537ms  10.235us  2.3237ms  acc_wait@layers.c:228
                    0.01%  3.5191ms      1200  2.9320us  1.8380us  855.39us  acc_wait@layers.c:417
                    0.01%  2.7251ms      1200  2.2700us  1.7980us  14.755us  acc_wait@layers.c:398
                    0.01%  2.7064ms      1200  2.2550us  1.6800us  18.315us  acc_update@layers.c:417
                    0.01%  2.5376ms         1  2.5376ms  2.5376ms  2.5376ms  acc_enter_data@main.c:182
                    0.01%  2.4012ms         1  2.4012ms  2.4012ms  2.4012ms  acc_enter_data@main.c:124
                    0.01%  2.3746ms         1  2.3746ms  2.3746ms  2.3746ms  acc_device_init@main.c:124
                    0.00%  271.52us         2  135.76us  117.48us  154.05us  acc_enqueue_launch@(runtime):44 (_21______src_cuda_fill_c___pgi_uacc_cuda_fill_44_gpu)
                    0.00%  194.38us         3  64.794us  15.095us  161.72us  acc_enqueue_upload@layers.c:305 (l->weights[:l->in_depth*(l->num_filters*(l->filter_width*l->filter_width))])
                    0.00%  152.32us         1  152.32us  152.32us  152.32us  acc_enter_data@main.c:162
                    0.00%  80.892us         1  80.892us  80.892us  80.892us  acc_wait@main.c:124
                    0.00%  74.603us         3  24.867us  3.7240us  57.763us  acc_update@layers.c:305
                    0.00%  72.440us        12  6.0360us     910ns  23.615us  acc_enqueue_upload@layers.c:37 (.attach.)
                    0.00%  54.776us         1  54.776us  54.776us  54.776us  acc_exit_data@main.c:246
                    0.00%  54.363us         3  18.121us  9.4150us  30.122us  acc_wait@layers.c:305
                    0.00%  47.274us         1  47.274us  47.274us  47.274us  acc_enter_data@main.c:164
                    0.00%  42.784us         3  14.261us  13.104us  15.593us  acc_enter_data@layers.c:153
                    0.00%  39.256us         1  39.256us  39.256us  39.256us  acc_enter_data@main.c:172
                    0.00%  38.236us         1  38.236us  38.236us  38.236us  acc_enter_data@main.c:178
                    0.00%  38.141us         3  12.713us  11.815us  13.998us  acc_enter_data@layers.c:104
                    0.00%  36.219us         1  36.219us  36.219us  36.219us  acc_enter_data@main.c:166
                    0.00%  34.713us         1  34.713us  34.713us  34.713us  acc_enter_data@main.c:176
                    0.00%  31.878us        12  2.6560us     872ns  4.8650us  acc_enqueue_upload@layers.c:48 (.detach.)
                    0.00%  30.132us         1  30.132us  30.132us  30.132us  acc_enqueue_upload@layers.c:355 (l->weights[:l->out_depth*l->in_neurons])
                    0.00%  30.105us         1  30.105us  30.105us  30.105us  acc_exit_data@main.c:284
                    0.00%  29.581us         3  9.8600us  8.4570us  12.160us  acc_enter_data@layers.c:228
                    0.00%  29.194us         1  29.194us  29.194us  29.194us  acc_enter_data@main.c:168
                    0.00%  26.014us         1  26.014us  26.014us  26.014us  acc_enter_data@main.c:170
                    0.00%  25.425us         3  8.4750us  4.0390us  14.249us  acc_enqueue_upload@layers.c:305 (l->bias[:l->out_depth])
                    0.00%  24.566us         9  2.7290us  1.7080us  4.6770us  acc_exit_data@layers.c:48
                    0.00%  22.572us         1  22.572us  22.572us  22.572us  acc_enter_data@main.c:180
                    0.00%  22.413us         2  11.206us  7.2820us  15.131us  acc_enter_data@layers.c:382
                    0.00%  22.108us         1  22.108us  22.108us  22.108us  acc_enter_data@main.c:174
                    0.00%  19.621us         2  9.8100us  2.1900us  17.431us  acc_enqueue_upload@layers.c:426 (.detach.)
                    0.00%  19.182us         2  9.5910us  9.3330us  9.8490us  acc_wait@layers.c:382
                    0.00%  17.796us         3  5.9320us  4.1590us  8.7860us  acc_enqueue_upload@layers.c:37 (layer[:1])
                    0.00%  16.523us         3  5.5070us  4.5040us  7.0980us  acc_enqueue_upload@layers.c:104 (layer[:1])
                    0.00%  15.192us         1  15.192us  15.192us  15.192us  acc_exit_data@main.c:258
                    0.00%  14.906us         3  4.9680us  4.6320us  5.2240us  acc_enqueue_upload@layers.c:153 (layer[:1])
                    0.00%  13.588us         1  13.588us  13.588us  13.588us  acc_update@layers.c:355
                    0.00%  11.822us         1  11.822us  11.822us  11.822us  acc_wait@main.c:182
                    0.00%  11.665us         4  2.9160us  1.0250us  4.9660us  acc_enqueue_upload@layers.c:228 (.attach.)
                    0.00%  10.591us         2  5.2950us  1.9230us  8.6680us  acc_exit_data@layers.c:426
                    0.00%  10.535us         4  2.6330us     853ns  4.6370us  acc_enqueue_upload@layers.c:253 (.detach.)
                    0.00%  10.490us         1  10.490us  10.490us  10.490us  acc_wait@layers.c:355
                    0.00%  8.0150us         3  2.6710us  1.6970us  3.5870us  acc_exit_data@layers.c:253
                    0.00%  7.7450us         1  7.7450us  7.7450us  7.7450us  acc_enqueue_upload@layers.c:355 (l->bias[:l->out_depth])
                    0.00%  6.0580us         1  6.0580us  6.0580us  6.0580us  acc_wait@main.c:162
                    0.00%  6.0290us         3  2.0090us  1.7530us  2.2350us  acc_exit_data@layers.c:198
                    0.00%  5.1160us         3  1.7050us  1.5870us  1.7960us  acc_exit_data@layers.c:125
                    0.00%  5.0330us         1  5.0330us  5.0330us  5.0330us  acc_wait@main.c:174
                    0.00%  4.7180us         2  2.3590us     851ns  3.8670us  acc_enqueue_upload@layers.c:382 (.attach.)
                    0.00%  4.5220us         1  4.5220us  4.5220us  4.5220us  acc_wait@main.c:176
                    0.00%  4.2750us         1  4.2750us  4.2750us  4.2750us  acc_enqueue_upload@layers.c:382 (layer[:1])
                    0.00%  4.2240us         1  4.2240us  4.2240us  4.2240us  acc_wait@main.c:178
                    0.00%  4.1340us         1  4.1340us  4.1340us  4.1340us  acc_wait@main.c:172
                    0.00%  3.8560us         1  3.8560us  3.8560us  3.8560us  acc_enqueue_upload@layers.c:228 (layer[:1])
                    0.00%  3.6140us         1  3.6140us  3.6140us  3.6140us  acc_wait@main.c:164
                    0.00%  3.5040us         1  3.5040us  3.5040us  3.5040us  acc_wait@main.c:170
                    0.00%  2.8070us         1  2.8070us  2.8070us  2.8070us  acc_wait@main.c:168
                    0.00%  2.5510us         1  2.5510us  2.5510us  2.5510us  acc_wait@main.c:166
                    0.00%  2.4900us         1  2.4900us  2.4900us  2.4900us  acc_exit_data@main.c:248
                    0.00%  2.4230us         1  2.4230us  2.4230us  2.4230us  acc_exit_data@main.c:250
                    0.00%  2.2610us         1  2.2610us  2.2610us  2.2610us  acc_exit_data@main.c:254
                    0.00%  2.1340us         1  2.1340us  2.1340us  2.1340us  acc_exit_data@main.c:264
                    0.00%  2.0910us         1  2.0910us  2.0910us  2.0910us  acc_exit_data@main.c:252
                    0.00%  2.0230us         1  2.0230us  2.0230us  2.0230us  acc_exit_data@main.c:256
                    0.00%  1.9470us         1  1.9470us  1.9470us  1.9470us  acc_exit_data@main.c:266
                    0.00%  1.9440us         1  1.9440us  1.9440us  1.9440us  acc_exit_data@main.c:262
                    0.00%  1.7400us         1  1.7400us  1.7400us  1.7400us  acc_exit_data@main.c:260
                    0.00%  1.5830us         1  1.5830us  1.5830us  1.5830us  acc_wait@main.c:180
                    0.00%       0ns      1200       0ns       0ns       0ns  acc_delete@layers.c:398
                    0.00%       0ns         2       0ns       0ns       0ns  acc_alloc@main.c:124
                    0.00%       0ns         2       0ns       0ns       0ns  acc_delete@main.c:284
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:162
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:164
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:166
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:168
                    0.00%       0ns         2       0ns       0ns       0ns  acc_create@layers.c:382
                    0.00%       0ns         9       0ns       0ns       0ns  acc_alloc@layers.c:37
                    0.00%       0ns         9       0ns       0ns       0ns  acc_create@layers.c:37
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:170
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:172
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:174
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:176
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:178
                    0.00%       0ns      1200       0ns       0ns       0ns  acc_create@layers.c:392
                    0.00%       0ns         3       0ns       0ns       0ns  acc_create@layers.c:153
                    0.00%       0ns         3       0ns       0ns       0ns  acc_alloc@layers.c:104
                    0.00%       0ns         3       0ns       0ns       0ns  acc_alloc@layers.c:228
                    0.00%       0ns         1       0ns       0ns       0ns  acc_create@main.c:180
                    0.00%       0ns         2       0ns       0ns       0ns  acc_create@main.c:182
                    0.00%       0ns         3       0ns       0ns       0ns  acc_delete@layers.c:198
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:162
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:164
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:166
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:168
                    0.00%       0ns         9       0ns       0ns       0ns  acc_delete@layers.c:48
                    0.00%       0ns         2       0ns       0ns       0ns  acc_delete@main.c:246
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:248
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:170
                    0.00%       0ns         3       0ns       0ns       0ns  acc_delete@layers.c:125
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:172
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:174
                    0.00%       0ns         2       0ns       0ns       0ns  acc_create@main.c:124
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:176
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:178
                    0.00%       0ns      1200       0ns       0ns       0ns  acc_delete@layers.c:407
                    0.00%       0ns         3       0ns       0ns       0ns  acc_create@layers.c:104
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:250
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:252
                    0.00%       0ns         3       0ns       0ns       0ns  acc_create@layers.c:228
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:254
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:256
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:258
                    0.00%       0ns         3       0ns       0ns       0ns  acc_delete@layers.c:253
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@main.c:180
                    0.00%       0ns         2       0ns       0ns       0ns  acc_alloc@main.c:182
                    0.00%       0ns      1200       0ns       0ns       0ns  acc_delete@layers.c:414
                    0.00%       0ns         2       0ns       0ns       0ns  acc_alloc@layers.c:382
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:260
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:262
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:264
                    0.00%       0ns         1       0ns       0ns       0ns  acc_delete@main.c:266
                    0.00%       0ns         2       0ns       0ns       0ns  acc_delete@layers.c:426
                    0.00%       0ns         1       0ns       0ns       0ns  acc_alloc@layers.c:392
                    0.00%       0ns         3       0ns       0ns       0ns  acc_alloc@layers.c:153
                    0.00%       0ns      1200       0ns       0ns       0ns  acc_create@layers.c:401
                    0.00%       0ns      1200       0ns       0ns       0ns  acc_create@layers.c:407
```