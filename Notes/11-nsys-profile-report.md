```
olia@krylov100:~/Diplomatiki/cnn-cifar10_0$ nsys profile -t openacc --stats=true  
./cnn-cifar10 
WARNING: CUDA tracing has been automatically enabled since it is a prerequisite for tracing OpenACC.
WARNING: CPU IP/backtrace sampling not supported, disabling.
Try the 'nsys status --environment' command to learn more.

WARNING: CPU context switch tracing not supported, disabling.
Try the 'nsys status --environment' command to learn more.

CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.817865 seconds
Load Data to device time:0.899111 seconds
Create Network time:0.040386 seconds
Load Network Parameters time:0.007608 seconds
Create Ouputs time:0.028961 seconds

Net Forward total time:672.012109 seconds
    Time for conv1: 199.664522 seconds
    Time for relu1: 5.575034 seconds
    Time for pool1: 5.473774 seconds
    Time for conv2: 311.699695 seconds
    Time for relu2: 5.492178 seconds
    Time for pool2: 5.004348 seconds
    Time for conv3: 91.435645 seconds
    Time for relu3: 5.452302 seconds
    Time for pool3: 5.238415 seconds
    Time for fc: 5.323796 seconds
    Time for softmax: 20.270920 seconds

  Conv: 602.799862 seconds
  ReLU: 16.519514 seconds
  Pool: 15.716537 seconds
  FC:   5.323796 seconds
  Softmax: 20.270920 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000000 seconds
Free memory time:0.060050 seconds
Total time:672.230360 seconds
END!
Generating '/tmp/nsys-report-9910.qdstrm'
[1/7] [========================100%] report1.nsys-rep
[2/7] [========================100%] report1.sqlite
[3/7] Executing 'cuda_api_sum' stats report

 Time (%)  Total Time (ns)  Num Calls    Avg (ns)      Med (ns)     Min (ns)    Max (ns)    StdDev (ns)          Name        
 --------  ---------------  ---------  ------------  ------------  ----------  -----------  -----------  --------------------
     89.9   53,844,375,934  1,150,037      46,819.7       4,392.0         558   16,001,421    304,699.2  cuStreamSynchronize 
      4.3    2,558,656,274    600,002       4,264.4       3,824.0       2,769    2,332,282      6,807.3  cuLaunchKernel      
      3.0    1,769,081,461    150,038      11,790.9       8,007.0       2,674  143,410,021    370,320.9  cuMemcpyHtoDAsync_v2
      2.3    1,352,755,909    100,001      13,527.4      13,218.0       9,960    2,143,297     11,046.5  cuMemcpyDtoHAsync_v2
      0.5      295,738,886    100,000       2,957.4       2,731.0       1,681    2,162,771      8,073.6  cuMemsetD32Async    
      0.1       38,796,333          1  38,796,333.0  38,796,333.0  38,796,333   38,796,333          0.0  cuMemHostAlloc      
      0.0        8,074,498          2   4,037,249.0   4,037,249.0     246,248    7,828,250  5,361,285.0  cuModuleLoadDataEx  
      0.0        1,325,271          1   1,325,271.0   1,325,271.0   1,325,271    1,325,271          0.0  cuMemAllocHost_v2   
      0.0          824,133         38      21,687.7       2,678.0       1,998      196,991     51,139.8  cuMemAlloc_v2       
      0.0            2,261          3         753.7         375.0         226        1,660        788.4  cuCtxSetCurrent     

[4/7] Executing 'cuda_gpu_kern_sum' stats report

 Time (%)  Total Time (ns)  Instances  Avg (ns)  Med (ns)  Min (ns)  Max (ns)  StdDev (ns)                          Name                        
 --------  ---------------  ---------  --------  --------  --------  --------  -----------  ----------------------------------------------------
     26.7      575,960,694    150,000   3,839.7   3,808.0     3,327    17,600        346.1  _8layers_c_relu_forward_118_gpu                     
     21.8      470,369,854    150,000   3,135.8   2,688.0     2,303    15,231        729.3  _8layers_c_pool_forward_171_gpu                     
     10.4      225,463,744     50,000   4,509.3   4,512.0     3,967    17,792        292.9  _8layers_c_softmax_forward_407_gpu                  
     10.3      222,893,652     50,000   4,457.9   4,448.0     3,903    13,504        307.7  _8layers_c_softmax_forward_416_gpu                  
      8.9      191,594,875     50,000   3,831.9   3,839.0     3,359    13,376        335.6  _8layers_c_softmax_forward_424_gpu                  
      7.9      170,359,995     50,000   3,407.2   3,296.0     2,911    13,376        469.0  _8layers_c_fc_forward_246_gpu                       
      7.1      153,499,741     50,000   3,070.0   3,040.0     2,687    17,919        384.1  _8layers_c_softmax_forward_416_gpu__red             
      6.9      148,751,792     50,000   2,975.0   2,944.0     2,591    13,152        362.9  _8layers_c_softmax_forward_407_gpu__red             
      0.0            5,248          2   2,624.0   2,624.0     2,528     2,720        135.8  _21______src_cuda_fill_c___pgi_uacc_cuda_fill_44_gpu

[5/7] Executing 'cuda_gpu_mem_time_sum' stats report

 Time (%)  Total Time (ns)   Count   Avg (ns)  Med (ns)  Min (ns)   Max (ns)    StdDev (ns)           Operation          
 --------  ---------------  -------  --------  --------  --------  -----------  -----------  ----------------------------
     75.5      810,433,825  150,038   5,401.5   3,105.0       735  143,219,453    369,747.0  [CUDA memcpy Host-to-Device]
     16.6      178,285,603  100,001   1,782.8   1,792.0     1,024      155,391        877.8  [CUDA memcpy Device-to-Host]
      7.8       84,164,416  100,000     841.6     736.0       639       13,824        669.5  [CUDA memset]               

[6/7] Executing 'cuda_gpu_mem_size_sum' stats report

 Total (MB)   Count   Avg (MB)  Med (MB)  Min (MB)  Max (MB)  StdDev (MB)           Operation          
 ----------  -------  --------  --------  --------  --------  -----------  ----------------------------
  5,171.290  150,038     0.034     0.020     0.000   614.400        1.586  [CUDA memcpy Host-to-Device]
  1,077.200  100,001     0.011     0.016     0.005     2.000        0.008  [CUDA memcpy Device-to-Host]
      0.400  100,000     0.000     0.000     0.000     0.000        0.000  [CUDA memset]               

[7/7] Executing 'openacc_sum' stats report

 Time (%)  Total Time (ns)  Num Calls    Avg (ns)       Med (ns)      Min (ns)     Max (ns)    StdDev (ns)                Name             
 --------  ---------------  ---------  -------------  -------------  -----------  -----------  ------------  ------------------------------
     11.8   14,985,177,043    150,000       99,901.2       14,551.0       12,442    2,852,932     434,092.3  Compute Construct@layers.c:118
     11.1   14,186,525,207    150,000       94,576.8       12,141.0       10,196    2,834,525     427,430.8  Compute Construct@layers.c:168
     10.9   13,829,013,294    300,000       46,096.7        3,853.5        1,189    2,838,561     309,786.8  Wait@layers.c:118             
     10.3   13,155,874,746    150,000       87,705.8        5,443.0        1,655    2,826,219     426,963.1  Wait@layers.c:171             
      6.6    8,435,209,647    100,000       84,352.1        5,221.0        1,743   16,006,495     422,299.9  Wait@layers.c:407             
      3.9    4,968,272,103     50,000       99,365.4       17,661.0       14,827    3,222,333     423,393.8  Enter Data@layers.c:407       
      3.9    4,921,619,856     50,000       98,432.4       19,119.0       16,698   16,132,226     423,401.7  Compute Construct@layers.c:407
      3.7    4,757,059,292     50,000       95,141.2       18,065.0       15,914    3,333,075     412,180.8  Compute Construct@layers.c:416
      3.7    4,740,766,147     50,000       94,815.3       12,138.0       10,690    2,428,885     428,597.7  Compute Construct@layers.c:244
      3.5    4,402,613,398     50,000       88,052.3        5,964.0        1,678    2,407,920     428,122.2  Wait@layers.c:246             
      3.4    4,393,514,147     50,000       87,870.3       13,377.0       11,753    2,422,745     403,996.2  Compute Construct@layers.c:424
      3.3    4,142,520,302     50,000       82,850.4        6,949.0        1,817    3,318,873     411,350.4  Wait@layers.c:416             
      3.2    4,011,968,217     50,000       80,239.4        6,457.0        1,655    2,413,224     403,519.5  Wait@layers.c:424             
      2.8    3,612,158,452     50,000       72,243.2       36,220.0       25,047   11,724,991     220,153.2  Update@main.c:202             
      2.2    2,744,087,780     50,000       54,881.8       19,524.0       15,929    3,329,083     215,078.7  Update@main.c:218             
      1.9    2,436,069,849     50,000       48,721.4       14,199.0        2,207    2,314,233     207,755.3  Wait@main.c:202               
      1.7    2,117,436,456     50,000       42,348.7        8,197.0        1,942    3,296,532     214,563.0  Wait@main.c:218               
      1.6    2,025,468,683     50,000       40,509.4       12,483.0       10,606    2,311,187     166,643.3  Update@main.c:234             
      1.3    1,627,407,469     50,000       32,548.1        5,204.0        1,836    2,304,060     166,339.5  Wait@main.c:234               
      0.8    1,024,953,470     50,000       20,499.1       19,665.0        9,507    2,304,013      11,887.8  Enqueue Upload@main.c:202     
      0.8      999,190,079     50,000       19,983.8       18,679.0       16,617    2,149,687      12,680.9  Update@main.c:212             
      0.7      909,527,343    150,000        6,063.5        5,306.0        4,334    2,163,081       7,039.0  Enqueue Launch@layers.c:118   
      0.7      865,271,438     50,000       17,305.4       16,164.5       14,175      205,782       4,130.6  Update@main.c:228             
      0.6      791,554,298     50,000       15,831.1       14,773.0       13,186    2,145,244      11,970.8  Enqueue Download@main.c:212   
      0.6      742,042,791    150,000        4,947.0        4,460.0        3,788    2,203,090       6,158.4  Enqueue Launch@layers.c:171   
      0.5      662,056,563     50,000       13,241.1       12,336.0       10,733      175,218       3,377.3  Enqueue Download@main.c:228   
      0.5      658,832,669    150,000        4,392.2        3,990.0        3,551      868,811       2,700.8  Enter Data@layers.c:168       
      0.5      626,817,782    150,000        4,178.8        3,798.0        3,238       82,224       1,577.2  Enter Data@layers.c:118       
      0.4      513,855,881    100,000        5,138.6        4,725.0        3,595    2,333,586       9,619.1  Enqueue Launch@layers.c:407   
      0.4      496,024,652     50,000        9,920.5        9,003.0        6,135      132,491       4,178.7  Enqueue Upload@main.c:218     
      0.4      454,403,288    100,000        4,544.0        4,091.0        3,437    2,146,788       7,312.1  Enqueue Launch@layers.c:416   
      0.3      385,265,887    100,000        3,852.7        3,526.0        2,319    2,164,251       8,141.2  Enqueue Upload@layers.c:407   
      0.2      301,960,963    150,000        2,013.1        1,835.0        1,567       35,647         944.5  Exit Data@layers.c:118        
      0.2      298,534,630    150,000        1,990.2        1,745.0        1,573      861,592       2,413.0  Wait@layers.c:168             
      0.2      286,867,703     50,000        5,737.4        5,186.0        4,179       92,093       2,615.1  Enqueue Upload@main.c:234     
      0.2      283,229,141    150,000        1,888.2        1,720.0        1,474      107,592         869.0  Exit Data@layers.c:168        
      0.2      245,190,321     50,000        4,903.8        4,413.0        3,825    1,142,964       6,555.9  Enqueue Launch@layers.c:246   
      0.2      239,305,626     50,000        4,786.1        4,330.0        3,736      770,021       3,794.0  Exit Data@layers.c:407        
      0.2      238,952,541     50,000        4,779.1        4,339.0        3,653       59,534       1,592.4  Enqueue Launch@layers.c:424   
      0.2      216,273,426     50,000        4,325.5        3,948.0        3,540       38,350       1,410.6  Enter Data@layers.c:244       
      0.1      143,416,755          1  143,416,755.0  143,416,755.0  143,416,755  143,416,755           0.0  Enqueue Upload@main.c:127     
      0.1      106,401,549     50,000        2,128.0        1,891.0        1,690      718,059       3,324.0  Wait@main.c:212               
      0.1      104,015,326     50,000        2,080.3        1,849.0        1,660       27,693         897.6  Wait@main.c:228               
      0.1       97,837,519     50,000        1,956.8        1,718.0        1,550       35,819         911.5  Wait@layers.c:244             
      0.1       96,621,652     50,000        1,932.4        1,794.0        1,587       26,782         780.8  Exit Data@layers.c:244        
      0.0       39,094,227          9    4,343,803.0       19,530.0       15,062   38,876,659  12,949,832.8  Enter Data@layers.c:37        
      0.0       26,855,112          1   26,855,112.0   26,855,112.0   26,855,112   26,855,112           0.0  Enter Data@main.c:185         
      0.0        3,158,120          1    3,158,120.0    3,158,120.0    3,158,120    3,158,120           0.0  Update@main.c:255             
      0.0        2,135,741          1    2,135,741.0    2,135,741.0    2,135,741    2,135,741           0.0  Enqueue Download@main.c:255   
      0.0        1,213,174          1    1,213,174.0    1,213,174.0    1,213,174    1,213,174           0.0  Exit Data@main.c:348          
      0.0        1,001,869          1    1,001,869.0    1,001,869.0    1,001,869    1,001,869           0.0  Exit Data@main.c:310          
      0.0          280,471          1      280,471.0      280,471.0      280,471      280,471           0.0  Device Init@main.c:127        
      0.0          151,197         15       10,079.8        5,057.0        3,661       45,240      11,666.1  Enqueue Upload@layers.c:37    
      0.0           90,363          3       30,121.0       31,544.0       24,469       34,350       5,091.9  Update@layers.c:320           
      0.0           78,306          2       39,153.0       39,153.0       32,392       45,914       9,561.5  Enqueue Launch@(runtime):44   
      0.0           66,623          9        7,402.6        7,953.0        1,551       20,187       5,780.9  Exit Data@layers.c:48         
      0.0           59,303          1       59,303.0       59,303.0       59,303       59,303           0.0  Wait@main.c:127               
      0.0           58,658          3       19,552.7       15,067.0       15,058       28,533       7,777.2  Enter Data@layers.c:113       
      0.0           53,604          6        8,934.0        6,037.0        3,610       17,912       6,489.2  Enqueue Upload@layers.c:320   
      0.0           51,580          3       17,193.3       16,036.0       15,888       19,656       2,134.0  Enter Data@layers.c:235       
      0.0           51,436         12        4,286.3        4,327.5        3,385        5,752         728.6  Enqueue Upload@layers.c:48    
      0.0           49,968          2       24,984.0       24,984.0       23,155       26,813       2,586.6  Enqueue Upload@layers.c:443   
      0.0           46,511          3       15,503.7       15,063.0       14,756       16,692       1,040.5  Enter Data@layers.c:160       
      0.0           45,507          9        5,056.3        4,467.0        4,233        9,342       1,625.7  Wait@layers.c:37              
      0.0           38,633          2       19,316.5       19,316.5        2,178       36,455      24,237.5  Exit Data@layers.c:443        
      0.0           35,681          1       35,681.0       35,681.0       35,681       35,681           0.0  Enter Data@main.c:165         
      0.0           31,678          2       15,839.0       15,839.0       15,564       16,114         388.9  Enter Data@layers.c:397       
      0.0           22,118          3        7,372.7        8,424.0        3,952        9,742       3,034.8  Exit Data@layers.c:268        
      0.0           21,071          1       21,071.0       21,071.0       21,071       21,071           0.0  Update@layers.c:370           
      0.0           21,020          5        4,204.0        3,915.0        3,707        4,859         548.1  Enqueue Upload@layers.c:235   
      0.0           20,945          3        6,981.7        7,993.0        3,344        9,608       3,252.2  Wait@layers.c:320             
      0.0           19,668          4        4,917.0        4,862.0        3,863        6,081         907.7  Enqueue Upload@layers.c:268   
      0.0           16,813          1       16,813.0       16,813.0       16,813       16,813           0.0  Wait@main.c:185               
      0.0           13,877          3        4,625.7        4,714.0        4,405        4,758         192.4  Wait@layers.c:160             
      0.0           13,623          3        4,541.0        4,527.0        4,498        4,598          51.4  Wait@layers.c:113             
      0.0           13,180          3        4,393.3        4,367.0        4,260        4,553         148.3  Wait@layers.c:235             
      0.0           12,883          3        4,294.3        3,666.0        3,646        5,571       1,105.7  Enqueue Upload@layers.c:113   
      0.0           12,845          2        6,422.5        6,422.5        3,818        9,027       3,683.3  Enqueue Upload@layers.c:370   
      0.0           12,208          3        4,069.3        3,737.0        3,735        4,736         577.4  Enqueue Upload@layers.c:397   
      0.0           11,029          3        3,676.3        3,594.0        3,513        3,922         216.6  Enqueue Upload@layers.c:160   
      0.0           10,742          1       10,742.0       10,742.0       10,742       10,742           0.0  Enter Data@main.c:171         
      0.0            8,859          2        4,429.5        4,429.5        4,228        4,631         285.0  Wait@layers.c:397             
      0.0            8,759          1        8,759.0        8,759.0        8,759        8,759           0.0  Enter Data@main.c:167         
      0.0            8,256          1        8,256.0        8,256.0        8,256        8,256           0.0  Enter Data@main.c:181         
      0.0            8,219          1        8,219.0        8,219.0        8,219        8,219           0.0  Enter Data@main.c:173         
      0.0            8,078          1        8,078.0        8,078.0        8,078        8,078           0.0  Enter Data@main.c:175         
      0.0            7,970          1        7,970.0        7,970.0        7,970        7,970           0.0  Enter Data@main.c:169         
      0.0            7,793          1        7,793.0        7,793.0        7,793        7,793           0.0  Enter Data@main.c:177         
      0.0            7,769          1        7,769.0        7,769.0        7,769        7,769           0.0  Enter Data@main.c:183         
      0.0            7,688          1        7,688.0        7,688.0        7,688        7,688           0.0  Enter Data@main.c:179         
      0.0            6,180          3        2,060.0        2,053.0        1,715        2,412         348.6  Exit Data@layers.c:205        
      0.0            5,941          3        1,980.3        1,876.0        1,569        2,496         472.2  Exit Data@layers.c:132        
      0.0            5,107          1        5,107.0        5,107.0        5,107        5,107           0.0  Exit Data@main.c:312          
      0.0            4,663          1        4,663.0        4,663.0        4,663        4,663           0.0  Wait@main.c:255               
      0.0            4,644          1        4,644.0        4,644.0        4,644        4,644           0.0  Wait@layers.c:370             
      0.0            4,553          1        4,553.0        4,553.0        4,553        4,553           0.0  Exit Data@main.c:322          
      0.0            2,529          1        2,529.0        2,529.0        2,529        2,529           0.0  Exit Data@main.c:318          
      0.0            2,432          1        2,432.0        2,432.0        2,432        2,432           0.0  Exit Data@main.c:324          
      0.0            2,404          1        2,404.0        2,404.0        2,404        2,404           0.0  Exit Data@main.c:330          
      0.0            2,359          1        2,359.0        2,359.0        2,359        2,359           0.0  Exit Data@main.c:316          
      0.0            2,271          1        2,271.0        2,271.0        2,271        2,271           0.0  Exit Data@main.c:320          
      0.0            2,196          1        2,196.0        2,196.0        2,196        2,196           0.0  Exit Data@main.c:314          
      0.0            2,141          1        2,141.0        2,141.0        2,141        2,141           0.0  Exit Data@main.c:326          
      0.0            2,042          1        2,042.0        2,042.0        2,042        2,042           0.0  Exit Data@main.c:328          
      0.0            1,832          1        1,832.0        1,832.0        1,832        1,832           0.0  Wait@main.c:165               
      0.0            1,686          1        1,686.0        1,686.0        1,686        1,686           0.0  Wait@main.c:173               
      0.0            1,527          1        1,527.0        1,527.0        1,527        1,527           0.0  Wait@main.c:167               
      0.0            1,440          1        1,440.0        1,440.0        1,440        1,440           0.0  Wait@main.c:179               
      0.0            1,405          1        1,405.0        1,405.0        1,405        1,405           0.0  Wait@main.c:175               
      0.0            1,402          1        1,402.0        1,402.0        1,402        1,402           0.0  Wait@main.c:169               
      0.0            1,390          1        1,390.0        1,390.0        1,390        1,390           0.0  Wait@main.c:183               
      0.0            1,384          1        1,384.0        1,384.0        1,384        1,384           0.0  Wait@main.c:171               
      0.0            1,372          1        1,372.0        1,372.0        1,372        1,372           0.0  Wait@main.c:177               
      0.0            1,363          1        1,363.0        1,363.0        1,363        1,363           0.0  Wait@main.c:181               
      0.0                0          3            0.0            0.0            0            0           0.0  Alloc@layers.c:113            
      0.0                0          3            0.0            0.0            0            0           0.0  Alloc@layers.c:160            
      0.0                0          3            0.0            0.0            0            0           0.0  Alloc@layers.c:235            
      0.0                0          9            0.0            0.0            0            0           0.0  Alloc@layers.c:37             
      0.0                0          2            0.0            0.0            0            0           0.0  Alloc@layers.c:397            
      0.0                0          2            0.0            0.0            0            0           0.0  Alloc@layers.c:407            
      0.0                0          2            0.0            0.0            0            0           0.0  Alloc@main.c:127              
      0.0                0          1            0.0            0.0            0            0           0.0  Alloc@main.c:165              
      0.0                0          1            0.0            0.0            0            0           0.0  Alloc@main.c:167              
      0.0                0          1            0.0            0.0            0            0           0.0  Alloc@main.c:169              
      0.0                0          1            0.0            0.0            0            0           0.0  Alloc@main.c:171              
      0.0                0          1            0.0            0.0            0            0           0.0  Alloc@main.c:173              
      0.0                0          1            0.0            0.0            0            0           0.0  Alloc@main.c:175              
      0.0                0          1            0.0            0.0            0            0           0.0  Alloc@main.c:177              
      0.0                0          1            0.0            0.0            0            0           0.0  Alloc@main.c:179              
      0.0                0          1            0.0            0.0            0            0           0.0  Alloc@main.c:181              
      0.0                0          1            0.0            0.0            0            0           0.0  Alloc@main.c:183              
      0.0                0          2            0.0            0.0            0            0           0.0  Alloc@main.c:185              
      0.0                0          3            0.0            0.0            0            0           0.0  Create@layers.c:113           
      0.0                0          3            0.0            0.0            0            0           0.0  Create@layers.c:160           
      0.0                0          3            0.0            0.0            0            0           0.0  Create@layers.c:235           
      0.0                0          9            0.0            0.0            0            0           0.0  Create@layers.c:37            
      0.0                0          2            0.0            0.0            0            0           0.0  Create@layers.c:397           
      0.0                0    100,000            0.0            0.0            0            0           0.0  Create@layers.c:407           
      0.0                0          2            0.0            0.0            0            0           0.0  Create@main.c:127             
      0.0                0          1            0.0            0.0            0            0           0.0  Create@main.c:165             
      0.0                0          1            0.0            0.0            0            0           0.0  Create@main.c:167             
      0.0                0          1            0.0            0.0            0            0           0.0  Create@main.c:169             
      0.0                0          1            0.0            0.0            0            0           0.0  Create@main.c:171             
      0.0                0          1            0.0            0.0            0            0           0.0  Create@main.c:173             
      0.0                0          1            0.0            0.0            0            0           0.0  Create@main.c:175             
      0.0                0          1            0.0            0.0            0            0           0.0  Create@main.c:177             
      0.0                0          1            0.0            0.0            0            0           0.0  Create@main.c:179             
      0.0                0          1            0.0            0.0            0            0           0.0  Create@main.c:181             
      0.0                0          1            0.0            0.0            0            0           0.0  Create@main.c:183             
      0.0                0          2            0.0            0.0            0            0           0.0  Create@main.c:185             
      0.0                0          3            0.0            0.0            0            0           0.0  Delete@layers.c:132           
      0.0                0          3            0.0            0.0            0            0           0.0  Delete@layers.c:205           
      0.0                0          3            0.0            0.0            0            0           0.0  Delete@layers.c:268           
      0.0                0    100,000            0.0            0.0            0            0           0.0  Delete@layers.c:433           
      0.0                0          2            0.0            0.0            0            0           0.0  Delete@layers.c:443           
      0.0                0          9            0.0            0.0            0            0           0.0  Delete@layers.c:48            
      0.0                0          2            0.0            0.0            0            0           0.0  Delete@main.c:310             
      0.0                0          1            0.0            0.0            0            0           0.0  Delete@main.c:312             
      0.0                0          1            0.0            0.0            0            0           0.0  Delete@main.c:314             
      0.0                0          1            0.0            0.0            0            0           0.0  Delete@main.c:316             
      0.0                0          1            0.0            0.0            0            0           0.0  Delete@main.c:318             
      0.0                0          1            0.0            0.0            0            0           0.0  Delete@main.c:320             
      0.0                0          1            0.0            0.0            0            0           0.0  Delete@main.c:322             
      0.0                0          1            0.0            0.0            0            0           0.0  Delete@main.c:324             
      0.0                0          1            0.0            0.0            0            0           0.0  Delete@main.c:326             
      0.0                0          1            0.0            0.0            0            0           0.0  Delete@main.c:328             
      0.0                0          1            0.0            0.0            0            0           0.0  Delete@main.c:330             
      0.0                0          2            0.0            0.0            0            0           0.0  Delete@main.c:348             

Generated:
    /home/olia/Diplomatiki/cnn-cifar10_0/report1.nsys-rep
    /home/olia/Diplomatiki/cnn-cifar10_0/report1.sqlite
```