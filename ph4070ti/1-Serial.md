# Serial Execution
## -Minfo
```
$ make
nvc -Minfo=all -c11 -Wall -Wextra -march=native -c main_serial.c -o main_serial.o
nvc -Minfo=all -c11 -Wall -Wextra -march=native -c layers_serial.c -o layers_serial.o
conv_forward:
     62, FMA (fused multiply-add) instruction(s) generated
fc_forward:
    201, FMA (fused multiply-add) instruction(s) generated
nvc -Minfo=all -c11 -Wall -Wextra -march=native -c malloc2D.c -o malloc2D.o
nvc -Minfo=all -c11 -Wall -Wextra -march=native -c timer.c -o timer.o
cpu_timer_stop:
     11, FMA (fused multiply-add) instruction(s) generated
nvc -Minfo=all -c11 -Wall -Wextra -march=native -o cnn-cifar10-serial main_serial.o layers_serial.o malloc2D.o timer.o
```

## Execution
```
$ ./cnn-cifar10-serial 
Serial Code
CNN for 50000 images
Load Data time:0.540534 seconds
Create Network time:0.000006 seconds
Load Network Parameters time:0.003323 seconds
Create Ouputs time:0.000252 seconds

Net Forward total time:751.865668 seconds
    Time for conv1: 244.149581 seconds
    Time for relu1: 3.200438 seconds
    Time for pool1: 3.355876 seconds
    Time for conv2: 385.739643 seconds
    Time for relu2: 0.916781 seconds
    Time for pool2: 0.993138 seconds
    Time for conv3: 112.546422 seconds
    Time for relu3: 0.244944 seconds
    Time for pool3: 0.258361 seconds
    Time for fc: 0.439608 seconds
    Time for softmax: 0.008307 seconds

  Conv: 742.435646 seconds
  ReLU: 4.362163 seconds
  Pool: 4.607375 seconds
  FC:   0.439608 seconds
  Softmax: 0.008307 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.001710 seconds
Free memory time:0.039750 seconds
Total time:752.451243 seconds
```

## GProf

```
$ ./cnn-cifar10-serial-profile 
Serial Code
CNN for 50000 images
Load Data time:0.538620 seconds
Create Network time:0.000006 seconds
Load Network Parameters time:0.003312 seconds
Create Ouputs time:0.000252 seconds

Net Forward total time:792.083721 seconds
    Time for conv1: 257.857886 seconds
    Time for relu1: 3.017700 seconds
    Time for pool1: 3.371451 seconds
    Time for conv2: 406.165904 seconds
    Time for relu2: 0.859824 seconds
    Time for pool2: 1.006675 seconds
    Time for conv3: 118.838808 seconds
    Time for relu3: 0.229953 seconds
    Time for pool3: 0.271156 seconds
    Time for fc: 0.439602 seconds
    Time for softmax: 0.009686 seconds

  Conv: 782.862598 seconds
  ReLU: 4.107478 seconds
  Pool: 4.649283 seconds
  FC:   0.439602 seconds
  Softmax: 0.009686 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.001717 seconds
Free memory time:0.040406 seconds
Total time:792.668035 seconds
END!

$ gprof ./cnn-cifar10-serial-profile 
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 98.78    782.85   782.85   150000     5.22     5.22  conv_forward
  0.58    787.48     4.63   150000     0.03     0.03  pool_forward
  0.53    791.69     4.21   150000     0.03     0.03  relu_forward
  0.06    792.20     0.51        1   510.00   510.00  load_data
  0.04    792.55     0.35    50000     0.01     0.01  fc_forward
  0.00    792.55     0.00   550007     0.00     0.00  cpu_timer_start
  0.00    792.55     0.00   550007     0.00     0.00  cpu_timer_stop
  0.00    792.55     0.00    50000     0.00     0.00  softmax_forward
  0.00    792.55     0.00        3     0.00     0.00  free_conv
  0.00    792.55     0.00        3     0.00     0.00  free_pool
  0.00    792.55     0.00        3     0.00     0.00  free_relu
  0.00    792.55     0.00        3     0.00     0.00  load_conv
  0.00    792.55     0.00        3     0.00     0.00  make_conv_layer
  0.00    792.55     0.00        3     0.00     0.00  make_pool_layer
  0.00    792.55     0.00        3     0.00     0.00  make_relu_layer
  0.00    792.55     0.00        2     0.00     0.00  malloc2D
  0.00    792.55     0.00        1     0.00     0.00  free_fc
  0.00    792.55     0.00        1     0.00     0.00  free_softmax
  0.00    792.55     0.00        1     0.00     0.00  load_fc
  0.00    792.55     0.00        1     0.00     0.00  make_fc_layer
  0.00    792.55     0.00        1     0.00     0.00  make_softmax_layer

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.

 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
           else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this
           function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
           the function in the gprof listing. If the index is
           in parenthesis it shows where it would appear in
           the gprof listing if it were to be printed.


Copyright (C) 2012-2022 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.


                     Call graph (explanation follows)


granularity: each sample hit covers 4 byte(s) for 0.00% of 792.55 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.00  792.55                 main [1]
              782.85    0.00  150000/150000      conv_forward [2]
                4.63    0.00  150000/150000      pool_forward [3]
                4.21    0.00  150000/150000      relu_forward [4]
                0.51    0.00       1/1           load_data [5]
                0.35    0.00   50000/50000       fc_forward [6]
                0.00    0.00  550007/550007      cpu_timer_start [7]
                0.00    0.00  550007/550007      cpu_timer_stop [8]
                0.00    0.00   50000/50000       softmax_forward [9]
                0.00    0.00       3/3           make_conv_layer [14]
                0.00    0.00       3/3           make_relu_layer [16]
                0.00    0.00       3/3           make_pool_layer [15]
                0.00    0.00       3/3           load_conv [13]
                0.00    0.00       3/3           free_pool [11]
                0.00    0.00       3/3           free_conv [10]
                0.00    0.00       3/3           free_relu [12]
                0.00    0.00       2/2           malloc2D [17]
                0.00    0.00       1/1           make_fc_layer [21]
                0.00    0.00       1/1           make_softmax_layer [22]
                0.00    0.00       1/1           load_fc [20]
                0.00    0.00       1/1           free_fc [18]
                0.00    0.00       1/1           free_softmax [19]
-----------------------------------------------
              782.85    0.00  150000/150000      main [1]
[2]     98.8  782.85    0.00  150000         conv_forward [2]
-----------------------------------------------
                4.63    0.00  150000/150000      main [1]
[3]      0.6    4.63    0.00  150000         pool_forward [3]
-----------------------------------------------
                4.21    0.00  150000/150000      main [1]
[4]      0.5    4.21    0.00  150000         relu_forward [4]
-----------------------------------------------
                0.51    0.00       1/1           main [1]
[5]      0.1    0.51    0.00       1         load_data [5]
-----------------------------------------------
                0.35    0.00   50000/50000       main [1]
[6]      0.0    0.35    0.00   50000         fc_forward [6]
-----------------------------------------------
                0.00    0.00  550007/550007      main [1]
[7]      0.0    0.00    0.00  550007         cpu_timer_start [7]
-----------------------------------------------
                0.00    0.00  550007/550007      main [1]
[8]      0.0    0.00    0.00  550007         cpu_timer_stop [8]
-----------------------------------------------
                0.00    0.00   50000/50000       main [1]
[9]      0.0    0.00    0.00   50000         softmax_forward [9]
-----------------------------------------------
                0.00    0.00       3/3           main [1]
[10]     0.0    0.00    0.00       3         free_conv [10]
-----------------------------------------------
                0.00    0.00       3/3           main [1]
[11]     0.0    0.00    0.00       3         free_pool [11]
-----------------------------------------------
                0.00    0.00       3/3           main [1]
[12]     0.0    0.00    0.00       3         free_relu [12]
-----------------------------------------------
                0.00    0.00       3/3           main [1]
[13]     0.0    0.00    0.00       3         load_conv [13]
-----------------------------------------------
                0.00    0.00       3/3           main [1]
[14]     0.0    0.00    0.00       3         make_conv_layer [14]
-----------------------------------------------
                0.00    0.00       3/3           main [1]
[15]     0.0    0.00    0.00       3         make_pool_layer [15]
-----------------------------------------------
                0.00    0.00       3/3           main [1]
[16]     0.0    0.00    0.00       3         make_relu_layer [16]
-----------------------------------------------
                0.00    0.00       2/2           main [1]
[17]     0.0    0.00    0.00       2         malloc2D [17]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[18]     0.0    0.00    0.00       1         free_fc [18]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[19]     0.0    0.00    0.00       1         free_softmax [19]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[20]     0.0    0.00    0.00       1         load_fc [20]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[21]     0.0    0.00    0.00       1         make_fc_layer [21]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[22]     0.0    0.00    0.00       1         make_softmax_layer [22]
-----------------------------------------------

 This table describes the call tree of the program, and was sorted by
 the total amount of time spent in each function and its children.

 Each entry in this table consists of several lines.  The line with the
 index number at the left hand margin lists the current function.
 The lines above it list the functions that called this function,
 and the lines below it list the functions this one called.
 This line lists:
     index      A unique number given to each element of the table.
                Index numbers are sorted numerically.
                The index number is printed next to every function name so
                it is easier to look up where the function is in the table.

     % time     This is the percentage of the `total' time that was spent
                in this function and its children.  Note that due to
                different viewpoints, functions excluded by options, etc,
                these numbers will NOT add up to 100%.

     self       This is the total amount of time spent in this function.

     children   This is the total amount of time propagated into this
                function by its children.

     called     This is the number of times the function was called.
                If the function called itself recursively, the number
                only includes non-recursive calls, and is followed by
                a `+' and the number of recursive calls.

     name       The name of the current function.  The index number is
                printed after it.  If the function is a member of a
                cycle, the cycle number is printed between the
                function's name and the index number.


 For the function's parents, the fields have the following meanings:

     self       This is the amount of time that was propagated directly
                from the function into this parent.

     children   This is the amount of time that was propagated from
                the function's children into this parent.

     called     This is the number of times this parent called the
                function `/' the total number of times the function
                was called.  Recursive calls to the function are not
                included in the number after the `/'.

     name       This is the name of the parent.  The parent's index
                number is printed after it.  If the parent is a
                member of a cycle, the cycle number is printed between
                the name and the index number.

 If the parents of the function cannot be determined, the word
 `<spontaneous>' is printed in the `name' field, and all the other
 fields are blank.

 For the function's children, the fields have the following meanings:

     self       This is the amount of time that was propagated directly
                from the child into the function.

     children   This is the amount of time that was propagated from the
                child's children to the function.

     called     This is the number of times the function called
                this child `/' the total number of times the child
                was called.  Recursive calls by the child are not
                listed in the number after the `/'.

     name       This is the name of the child.  The child's index
                number is printed after it.  If the child is a
                member of a cycle, the cycle number is printed
                between the name and the index number.

 If there are any cycles (circles) in the call graph, there is an
 entry for the cycle-as-a-whole.  This entry shows who called the
 cycle (as parents) and the members of the cycle (as children.)
 The `+' recursive calls entry shows the number of function calls that
 were internal to the cycle, and the calls entry for each member shows,
 for that member, how many times it was called from other members of
 the cycle.


Copyright (C) 2012-2022 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.


Index by function name

   [2] conv_forward           [12] free_relu              [15] make_pool_layer
   [7] cpu_timer_start        [19] free_softmax           [16] make_relu_layer
   [8] cpu_timer_stop         [13] load_conv              [22] make_softmax_layer
   [6] fc_forward              [5] load_data              [17] malloc2D
  [10] free_conv              [20] load_fc                 [3] pool_forward
  [18] free_fc                [14] make_conv_layer         [4] relu_forward
  [11] free_pool              [21] make_fc_layer           [9] softmax_forward
```

---
# Final acceleration

```
serial2parallel-3.2-full$ ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.612413 seconds
Create Network time:0.000247 seconds
Load Network Parameters time:0.003377 seconds
Create Ouputs time:0.000169 seconds

Net Forward total time:7.108899 seconds
    Time for conv1: 1.403592 seconds
    Time for relu1: 0.470102 seconds
    Time for pool1: 0.460670 seconds
    Time for conv2: 1.076372 seconds
    Time for relu2: 0.356371 seconds
    Time for pool2: 0.365225 seconds
    Time for conv3: 0.775531 seconds
    Time for relu3: 0.325080 seconds
    Time for pool3: 0.334027 seconds
    Time for fc: 0.348964 seconds
    Time for softmax: 1.176221 seconds

  Conv: 3.255494 seconds
  ReLU: 1.151553 seconds
  Pool: 1.159922 seconds
  FC:   0.348964 seconds
  Softmax: 1.176221 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000247 seconds
Free memory time:0.040184 seconds
Total time:7.765537 seconds
END!
```