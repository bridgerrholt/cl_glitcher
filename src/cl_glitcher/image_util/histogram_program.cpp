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

HistogramProgram::HistogramProgram(gpu_util::GpuHandle const & gpuHandle) :
  program {
    gpu_util::buildProgram(
      gpuHandle, {{
        histogram_program::histogramStr.c_str(),
        histogram_program::histogramStr.size()
      }}
    )
  } {}



std::array<unsigned int, 256> HistogramProgram::execute(
  gpu_util::GpuHandle const & gpuHandle,
  unsigned char const * img,
  int imgSize)
{
  using namespace gpu_util;

  std::array<unsigned int, 256> res {};

  cl::CommandQueue queue(gpuHandle.context, gpuHandle.device);

  /*auto bwA {
    BufferWrapper::fromArr(gpuHandle, CL_MEM_READ_ONLY, img, imgSize)
  };*/
  auto bwA {
    BufferWrapper::writeBuffer(
      queue, gpuHandle, CL_MEM_READ_ONLY, img, imgSize
    )
  };
  /*auto bwN {
    BufferWrapper::fromValue(gpuHandle, CL_MEM_READ_WRITE, imgSize)
  };*/
  auto bwN {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, imgSize
    )
  };
  auto bwC {
    BufferWrapper::fromArr(gpuHandle, CL_MEM_READ_WRITE, res)
  };

  // create buffers on device (allocate space on GPU)
  //cl::Buffer buffer_A(gpuHandle.context, CL_MEM_READ_ONLY, sizeof(char) * imgSize);
  //cl::Buffer buffer_C(gpuHandle.context, CL_MEM_READ_WRITE, sizeof(int) * 256);
  //cl::Buffer buffer_N(gpuHandle.context, CL_MEM_READ_ONLY,  sizeof(int));
  // create a queue (a queue of commands that the GPU will execute)

  // push write commands to queue
  //queue.enqueueWriteBuffer(bwA.getBuffer(), CL_TRUE, 0, sizeof(char)*imgSize, img);
  //queue.enqueueWriteBuffer(bwN.getBuffer(), CL_TRUE, 0, sizeof(int), &imgSize);

  // RUN ZE KERNEL
  //cl::KernelFunctor simple_add(cl::Kernel(program, "simple_add"), queue, cl::NullRange, cl::NDRange(10), cl::NullRange);
  //simple_add(buffer_A, buffer_B, buffer_C, buffer_N);

  cl::Kernel simple_add(program, "histogram");
  simple_add.setArg(0, bwA.getBuffer());
  simple_add.setArg(1, bwN.getBuffer());
  simple_add.setArg(2, bwC.getBuffer());
  queue.enqueueNDRangeKernel(simple_add,cl::NullRange,cl::NDRange(16),cl::NullRange);

  // read result from GPU to here
  //queue.enqueueReadBuffer(bwC.getBuffer(), CL_TRUE, 0, sizeof(int)*256, C.data());
  bwC.enqueueRead(queue, res);
  queue.finish();

  return res;
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
