# $ nvaccelinfo 
```
CUDA Driver Version:           12020
NVRM version:                  NVIDIA UNIX x86_64 Kernel Module  535.183.01  Sun May 12 19:39:15 UTC 2024

Device Number:                 0
Device Name:                   NVIDIA GeForce RTX 4070 Ti
Device Revision Number:        8.9
Global Memory Size:            12590645248
Number of Multiprocessors:     60
Concurrent Copy and Execution: Yes
Total Constant Memory:         65536
Total Shared Memory per Block: 49152
Registers per Block:           65536
Warp Size:                     32
Maximum Threads per Block:     1024
Maximum Block Dimensions:      1024, 1024, 64
Maximum Grid Dimensions:       2147483647 x 65535 x 65535
Maximum Memory Pitch:          2147483647B
Texture Alignment:             512B
Clock Rate:                    2625 MHz
Execution Timeout:             No
Integrated Device:             No
Can Map Host Memory:           Yes
Compute Mode:                  default
Concurrent Kernels:            Yes
ECC Enabled:                   No
Memory Clock Rate:             10501 MHz
Memory Bus Width:              192 bits
L2 Cache Size:                 50331648 bytes
Max Threads Per SMP:           1536
Async Engines:                 2
Unified Addressing:            Yes
Managed Memory:                Yes
Concurrent Managed Memory:     Yes
Preemption Supported:          Yes
Cooperative Launch:            Yes
  Multi-Device:                Yes
Default Target:                cc86
```

# $ lscpu 
```
Architecture:             x86_64
  CPU op-mode(s):         32-bit, 64-bit
  Address sizes:          48 bits physical, 48 bits virtual
  Byte Order:             Little Endian
CPU(s):                   16
  On-line CPU(s) list:    0-15
Vendor ID:                AuthenticAMD
  Model name:             AMD Ryzen 7 5800X 8-Core Processor
    CPU family:           25
    Model:                33
    Thread(s) per core:   2
    Core(s) per socket:   8
    Socket(s):            1
    Stepping:             2
    Frequency boost:      enabled
    CPU max MHz:          4850,1948
    CPU min MHz:          2200,0000
    BogoMIPS:             7586.45
    Flags:                fpu vme de pse tsc msr pae mce cx8 apic se
                          p mtrr pge mca cmov pat pse36 clflush mmx 
                          fxsr sse sse2 ht syscall nx mmxext fxsr_op
                          t pdpe1gb rdtscp lm constant_tsc rep_good 
                          nopl nonstop_tsc cpuid extd_apicid aperfmp
                          erf rapl pni pclmulqdq monitor ssse3 fma c
                          x16 sse4_1 sse4_2 x2apic movbe popcnt aes 
                          xsave avx f16c rdrand lahf_lm cmp_legacy e
                          xtapic cr8_legacy abm sse4a misalignsse 3d
                          nowprefetch osvw ibs skinit wdt tce topoex
                          t perfctr_core perfctr_nb bpext perfctr_ll
                          c mwaitx cpb cat_l3 cdp_l3 hw_pstate ssbd 
                          mba ibrs ibpb stibp vmmcall fsgsbase bmi1 
                          avx2 smep bmi2 erms invpcid cqm rdt_a rdse
                          ed adx smap clflushopt clwb sha_ni xsaveop
                          t xsavec xgetbv1 xsaves cqm_llc cqm_occup_
                          llc cqm_mbm_total cqm_mbm_local user_shstk
                           clzero irperf xsaveerptr rdpru wbnoinvd a
                          rat npt lbrv svm_lock nrip_save tsc_scale 
                          vmcb_clean flushbyasid decodeassists pause
                          filter pfthreshold avic v_vmsave_vmload vg
                          if v_spec_ctrl umip pku ospke vaes vpclmul
                          qdq rdpid overflow_recov succor smca fsrm 
                          debug_swap
Caches (sum of all):      
  L1d:                    256 KiB (8 instances)
  L1i:                    256 KiB (8 instances)
  L2:                     4 MiB (8 instances)
  L3:                     32 MiB (1 instance)
NUMA:                     
  NUMA node(s):           1
  NUMA node0 CPU(s):      0-15
Vulnerabilities:          
  Gather data sampling:   Not affected
  Itlb multihit:          Not affected
  L1tf:                   Not affected
  Mds:                    Not affected
  Meltdown:               Not affected
  Mmio stale data:        Not affected
  Reg file data sampling: Not affected
  Retbleed:               Not affected
  Spec rstack overflow:   Vulnerable: Safe RET, no microcode
  Spec store bypass:      Mitigation; Speculative Store Bypass disab
                          led via prctl
  Spectre v1:             Mitigation; usercopy/swapgs barriers and _
                          _user pointer sanitization
  Spectre v2:             Mitigation; Retpolines; IBPB conditional; 
                          IBRS_FW; STIBP always-on; RSB filling; PBR
                          SB-eIBRS Not affected; BHI Not affected
  Srbds:                  Not affected
  Tsx async abort:        Not affected
```

```

$ cat /sys/devices/virtual/dmi/id/board_vendor
Gigabyte Technology Co., Ltd.

$ cat /sys/devices/virtual/dmi/id/product_name
B550 GAMING X V2

$ nvidia-smi 
Mon Nov 18 21:16:46 2024       
+---------------------------------------------------------------------------------------+
| NVIDIA-SMI 535.183.01             Driver Version: 535.183.01   CUDA Version: 12.2     |
|-----------------------------------------+----------------------+----------------------+
| GPU  Name                 Persistence-M | Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp   Perf          Pwr:Usage/Cap |         Memory-Usage | GPU-Util  Compute M. |
|                                         |                      |               MIG M. |
|=========================================+======================+======================|
|   0  NVIDIA GeForce RTX 4070 Ti     Off | 00000000:05:00.0 Off |                  N/A |
|  0%   30C    P8              10W / 285W |      1MiB / 12282MiB |      0%      Default |
|                                         |                      |                  N/A |
+-----------------------------------------+----------------------+----------------------+
                                                                                         
+---------------------------------------------------------------------------------------+
| Processes:                                                                            |
|  GPU   GI   CI        PID   Type   Process name                            GPU Memory |
|        ID   ID                                                             Usage      |
|=======================================================================================|
|  No running processes found                                                           |
+---------------------------------------------------------------------------------------+

$ nvc --version

nvc 22.11-0 64-bit target on x86-64 Linux -tp zen3 
NVIDIA Compilers and Tools
Copyright (c) 2022, NVIDIA CORPORATION & AFFILIATES.  All rights reserved.

$  free -h
               total        used        free      shared  buff/cache   available
Mem:            31Gi       1,8Gi        13Gi       3,0Mi        15Gi        28Gi
Swap:          2,0Gi        44Mi       2,0Gi

$ uname -a
Linux ph4070ti 6.8.0-48-generic #48~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Mon Oct  7 11:24:13 UTC 2 x86_64 x86_64 x86_64 GNU/Linux

$ lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 22.04.5 LTS
Release:        22.04
Codename:       jammy

$ gprof --version
GNU gprof (GNU Binutils for Ubuntu) 2.38
Based on BSD gprof, copyright 1983 Regents of the University of California.
This program is free software.  This program has absolutely no warranty.

$ gdb --version
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

$ nvprof --version
nvprof: NVIDIA (R) Cuda command line profiler
Copyright (c) 2012 - 2022 NVIDIA Corporation
Release version 11.8.87 (21)

```