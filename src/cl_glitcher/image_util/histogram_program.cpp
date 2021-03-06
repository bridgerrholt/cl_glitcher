//
// Created by bridg on 3/5/2021.
//

#include <image_util/histogram_program.h>

#include <gpu_util/build_program.h>
#include <gpu_util/buffer_wrapper.h>
#include <gpu_util/set_args.h>

#include <compute_kernels/image_util/histogram.h>
#include <gpu_util/init.h>

namespace clglitch::image_util {

namespace {

using namespace gpu_util;

std::array<unsigned int, 256> runHistogram(
  GpuHandle const & gpuHandle,
  cl::Program const & program,
  unsigned char const * imgArr,
  int imgSize)
{
  // apparently OpenCL only likes arrays ...
  // N holds the number of elements in the vectors we want to add
  int N[1] = {imgSize};

  // create buffers on device (allocate space on GPU)
  cl::Buffer buffer_A(gpuHandle.context, CL_MEM_READ_ONLY, sizeof(char) * imgSize);
  cl::Buffer buffer_C(gpuHandle.context, CL_MEM_READ_WRITE, sizeof(int) * 256);
  cl::Buffer buffer_N(gpuHandle.context, CL_MEM_READ_ONLY,  sizeof(int));
  // create a queue (a queue of commands that the GPU will execute)
  cl::CommandQueue queue(gpuHandle.context, gpuHandle.device);

  // push write commands to queue
  queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(char)*imgSize, imgArr);
  queue.enqueueWriteBuffer(buffer_N, CL_TRUE, 0, sizeof(int),   N);

  // RUN ZE KERNEL
  //cl::KernelFunctor simple_add(cl::Kernel(program, "simple_add"), queue, cl::NullRange, cl::NDRange(10), cl::NullRange);
  //simple_add(buffer_A, buffer_B, buffer_C, buffer_N);

  cl::Kernel simple_add(program, "histogram");
  simple_add.setArg(0, buffer_A);
  simple_add.setArg(1, buffer_N);
  simple_add.setArg(2, buffer_C);
  queue.enqueueNDRangeKernel(simple_add,cl::NullRange,cl::NDRange(16),cl::NullRange);

  std::array<unsigned int, 256> C {};
  // read result from GPU to here
  queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int)*256, C.data());
  queue.finish();

  return C;
}

}


HistogramProgram::HistogramProgram(gpu_util::GpuHandle const & gpuHandle) :
  program {gpu_util::buildProgram(
    gpuHandle, {{
      histogram_program::histogramStr.c_str(),
      histogram_program::histogramStr.size()
    }})} {}



std::array<unsigned int, 256> HistogramProgram::execute(
  gpu_util::GpuHandle const & gpuHandle,
  unsigned char const * img,
  int imgSize)
{
  using namespace gpu_util;

  GpuHandle data {init()};

  cl::Program p {buildProgram(data, {{histogram_program::histogramStr.c_str(), histogram_program::histogramStr.size()}})};

  constexpr int n = 100;

  auto C {runHistogram(data, p, img, imgSize)};

  return C;
}



/*std::array<unsigned int, 256> HistogramProgram::execute(
  gpu_util::GpuHandle const & gpuHandle,
  unsigned int const * img,
  int imgSize)
{
  using namespace gpu_util;

  std::array<int, 1> n {imgSize};

  std::array<unsigned int, 256> histOut {};

  // create a queue (a queue of commands that the GPU will execute)
  cl::CommandQueue queue(gpuHandle.context, gpuHandle.device);

  // create buffers on device (allocate space on GPU)
  auto bufferImg {
    BufferWrapper::writeBuffer(
      queue, gpuHandle, CL_MEM_READ_ONLY, img, imgSize
      )
  };

  auto bufferN {
    BufferWrapper::writeBuffer(
      queue, gpuHandle, CL_MEM_READ_ONLY, n
    )
  };

  auto bufferHistOut {
    BufferWrapper::fromArr(gpuHandle, CL_MEM_READ_WRITE, histOut)
  };

  // RUN ZE KERNEL
  //cl::KernelFunctor simple_add(cl::Kernel(program, "simple_add"), queue, cl::NullRange, cl::NDRange(10), cl::NullRange);
  //simple_add(buffer_A, buffer_B, buffer_C, buffer_N);

  cl::Kernel kernel(program, "histogram");
  setArgs(kernel, bufferImg, bufferN, bufferHistOut);
  queue.enqueueNDRangeKernel(
    kernel, cl::NullRange, cl::NDRange(8), cl::NullRange);

  bufferHistOut.enqueueRead(queue, histOut);

  queue.finish();
  return histOut;
}*/


}
