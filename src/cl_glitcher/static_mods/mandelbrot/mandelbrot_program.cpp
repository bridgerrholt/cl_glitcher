//
// Created by bridg on 4/7/2021.
//

#include <mandelbrot_program.h>

#include <gpu_util/build_program.h>
#include <gpu_util/buffer_wrapper.h>
#include <gpu_util/set_args.h>

#include <compute_kernels/static_mods/mandelbrot.h>
#include <gpu_util/init.h>
#include <iostream>

namespace clglitch::mandelbrot
{

MandelbrotProgram::MandelbrotProgram(
  gpu_util::GpuHandle const & gpuHandle) :
  program {
    gpu_util::buildProgram(
      gpuHandle, {{
        mandelbrot_program::mandelbrotStr.c_str(),
        mandelbrot_program::mandelbrotStr.size()
      }}
    )
  } {}



void MandelbrotProgram::execute(
  cl::CommandQueue & queue,
  gpu_util::GpuHandle const & gpuHandle,
  gpu_util::BufferWrapper & imgIn,
  gpu_util::BufferWrapper & imgCurrent,
  int imgSize,
  float steps,
  float n,
  float radius,
  bool imageFeedback,
  cl_float3 sphereOffset) const
{
  using namespace gpu_util;

  auto bwImgSize {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, imgSize
    )
  };

  auto bwSteps {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, steps
    )
  };

  auto bwN {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, n
    )
  };

  auto bwRadius {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, radius
    )
  };

  auto bwImageFeedback {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, imageFeedback
    )
  };

  auto bwSphereOffset {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, sphereOffset
    )
  };

  cl_int err = 0;
  cl::Kernel mandelbrot(program, "mandelbrot", &err);
  if (err != 0)
  {
    std::cout << "Failed to load mandelbrot\n";
  }
  setArgs(
    mandelbrot, imgIn, imgCurrent, bwImgSize, bwSteps, bwN, bwRadius, bwImageFeedback, bwSphereOffset);
  queue.enqueueNDRangeKernel(
    mandelbrot, cl::NullRange, cl::NDRange(16), cl::NullRange);
}

}
