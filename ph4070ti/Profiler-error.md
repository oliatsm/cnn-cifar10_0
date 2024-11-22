$ nsys profile ./cnn-cifar10 
WARNING: CPU IP/backtrace sampling not supported, disabling.
Try the 'nsys status --environment' command to learn more.

WARNING: CPU context switch tracing not supported, disabling.
Try the 'nsys status --environment' command to learn more.

Parallel (pad) Code
CNN for 50000 images
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.302270 seconds
Create Network time:0.000845 seconds
Load Network Parameters time:0.003410 seconds
Create Ouputs time:0.000356 seconds

Net Forward total time:149.180191 seconds
    Time for conv1: 52.680619 seconds
    Time for relu1: 18.761636 seconds
    Time for pool1: 2.416772 seconds
    Time for conv2: 35.159452 seconds
    Time for relu2: 14.195736 seconds
    Time for pool2: 2.924655 seconds
    Time for conv3: 13.642143 seconds
    Time for relu3: 7.962635 seconds
    Time for pool3: 1.282157 seconds
    Time for fc: 0.131982 seconds
    Time for softmax: 0.009569 seconds

  Conv: 101.482214 seconds
  ReLU: 40.920006 seconds
  Pool: 6.623584 seconds
  FC:   0.131982 seconds
  Softmax: 0.009569 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000289 seconds
Free memory time:0.016606 seconds
Total time:149.503967 seconds
END!
Generating '/tmp/nsys-report-e958.qdstrm'
FATAL ERROR: /build/agent/work/323cb361ab84164c/QuadD/Common/GpuTraits/Src/GpuTicksConverter.cpp(376): Throw in function QuadDCommon::TimestampType GpuTraits::GpuTicksConverter::ConvertToCpuTime(const QuadDCommon::Uuid&, uint64_t&) const
Dynamic exception type: boost::wrapexcept<QuadDCommon::NotFoundException>
std::exception::what: NotFoundException
[QuadDCommon::tag_message*] = No GPU associated to the given UUID

---

$ ncu ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
==PROF== Connected to process 1929595 (/home/gskondras/cifar/cnn-cifar10_0/2.2-Data-pad/cnn-cifar10)
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.332911 seconds
Create Network time:0.000719 seconds
Load Network Parameters time:0.004553 seconds
Create Ouputs time:0.000297 seconds
==ERROR== ERR_NVGPUCTRPERM - The user does not have permission to access NVIDIA GPU Performance Counters on the target device 0. For instructions on enabling permissions and to get more information see https://developer.nvidia.com/ERR_NVGPUCTRPERM


...

Total time:171.063028 seconds
END!
==PROF== Disconnected from process 1929595
==WARNING== No kernels were profiled.
==WARNING== Profiling kernels launched by child processes requires the --target-processes all option.

---

$ ncu --target-processes all ./cnn-cifar10 
Parallel (pad) Code
CNN for 50000 images
==PROF== Connected to process 1929941 (/home/gskondras/cifar/cnn-cifar10_0/2.2-Data-pad/cnn-cifar10)
Loading input batch 1...
Loading input batch 2...
Loading input batch 3...
Loading input batch 4...
Loading input batch 5...
Load Data time:0.278231 seconds
Create Network time:0.000742 seconds
Load Network Parameters time:0.003430 seconds
Create Ouputs time:0.000267 seconds
==ERROR== ERR_NVGPUCTRPERM - The user does not have permission to access NVIDIA GPU Performance Counters on the target device 0. For instructions on enabling permissions and to get more information see https://developer.nvidia.com/ERR_NVGPUCTRPERM

Net Forward total time:170.659984 seconds
    Time for conv1: 66.970184 seconds
    Time for relu1: 10.867897 seconds
    Time for pool1: 1.550094 seconds
    Time for conv2: 48.545372 seconds
    Time for relu2: 7.868796 seconds
    Time for pool2: 1.744851 seconds
    Time for conv3: 27.744245 seconds
    Time for relu3: 4.503982 seconds
    Time for pool3: 0.711507 seconds
    Time for fc: 0.130789 seconds
    Time for softmax: 0.009143 seconds

  Conv: 143.259802 seconds
  ReLU: 23.240675 seconds
  Pool: 4.006453 seconds
  FC:   0.130789 seconds
  Softmax: 0.009143 seconds

Net Accuracy: 78.84 % 
Net Accuracy time:0.000270 seconds
Free memory time:0.016426 seconds
Total time:170.959351 seconds
END!
==PROF== Disconnected from process 1929941
==WARNING== No kernels were profiled.

---


