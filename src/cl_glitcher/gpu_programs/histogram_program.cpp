//
// Created by bridg on 3/5/2021.
//

#include <gpu_programs/histogram_program.h>

#include <gpu_util/build_program.h>
#include <gpu_util/buffer_wrapper.h>
#include <gpu_util/set_args.h>

#include <compute_kernels/gpu_programs/histogram.h>
#include <gpu_util/init.h>

namespace clglitch::gpu_programs {

HistogramProgram::HistogramProgram(gpu_util::GpuHandle const & gpuHandle) :
  program {
    gpu_util::buildProgram(
      gpuHandle, {{
        histogram_program::histogramStr.c_str(),
        histogram_program::histogramStr.size()
      }}
    )
  } {}



HistogramProgram::ResultArr HistogramProgram::execute(
  gpu_util::GpuHandle const & gpuHandle,
  unsigned char const * img,
  int imgSize) const
{
  using namespace gpu_util;

  ResultArr res {};

  cl::CommandQueue queue(gpuHandle.context, gpuHandle.device);

  /*auto bwA {
    BufferWrapper::writeBuffer(
      queue, gpuHandle, CL_MEM_READ_ONLY, img, imgSize
    )
  };

  auto bwN {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, imgSize
    )
  };*/

  // RUN ZE KERNEL
  /*cl::Kernel histogram(program, "histogram");
  setArgs(histogram, bwA, bwN, bwC);
  queue.enqueueNDRangeKernel(histogram,cl::NullRange,cl::NDRange(16),cl::NullRange);*/

  auto bwC {execute(queue, gpuHandle, img, imgSize)};

  // read result from GPU to here
  bwC.enqueueRead(queue, res);
  queue.finish();

  return res;
}



gpu_util::BufferWrapper HistogramProgram::execute(
  cl::CommandQueue & queue,
  gpu_util::GpuHandle const & gpuHandle,
  unsigned char const * img,
  int imgSize) const
{
  using namespace gpu_util;

  BufferWrapper bwRes {
    gpuHandle, CL_MEM_READ_WRITE, resultBytes()
  };

  execute(queue, gpuHandle, img, imgSize, bwRes);

  return bwRes;
}



gpu_util::BufferWrapper HistogramProgram::execute(
  cl::CommandQueue & queue,
  gpu_util::GpuHandle const & gpuHandle,
  gpu_util::BufferWrapper const & img,
  int imgSize) const
{
  using namespace gpu_util;

  BufferWrapper bwRes {
    gpuHandle, CL_MEM_READ_WRITE, resultBytes()
  };

  execute(queue, gpuHandle, img, imgSize, bwRes);

  return bwRes;
}



void HistogramProgram::execute(
  cl::CommandQueue & queue,
  gpu_util::GpuHandle const & gpuHandle,
  unsigned char const * img,
  int imgSize,
  gpu_util::BufferWrapper & resBuffer) const
{
  using namespace gpu_util;

  auto bwA {
    BufferWrapper::writeBuffer(
      queue, gpuHandle, CL_MEM_READ_ONLY, img, imgSize
    )
  };

  execute(queue, gpuHandle, bwA, imgSize, resBuffer);
}



void HistogramProgram::execute(
  cl::CommandQueue & queue,
  gpu_util::GpuHandle const & gpuHandle,
  gpu_util::BufferWrapper const & img,
  int imgSize,
  gpu_util::BufferWrapper & resBuffer) const
{
  using namespace gpu_util;

  auto bwN {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, imgSize
    )
  };

  cl::Kernel histogram(program, "histogram");
  setArgs(histogram, img, bwN, resBuffer);
  queue.enqueueNDRangeKernel(
    histogram, cl::NullRange, cl::NDRange(16), cl::NullRange);
}


}
