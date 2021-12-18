//
// Created by bridg on 4/7/2021.
//

#include <mandelbrot_shift_program.h>

#include <gpu_util/build_program.h>
#include <gpu_util/buffer_wrapper.h>
#include <gpu_util/set_args.h>

#include <compute_kernels/static_mods/mandelbrot_shift.h>
#include <gpu_util/init.h>

namespace clglitch::mandelbrot_shift
{

MandelbrotShiftProgram::MandelbrotShiftProgram(
  gpu_util::GpuHandle const & gpuHandle) :
  program {
    gpu_util::buildProgram(
      gpuHandle, {{
        mandelbrot_shift_program::mandelbrotShiftStr.c_str(),
        mandelbrot_shift_program::mandelbrotShiftStr.size()
      }}
    )
  } {}



void MandelbrotShiftProgram::execute(
  cl::CommandQueue & queue,
  gpu_util::GpuHandle const & gpuHandle,
  gpu_util::BufferWrapper & imgCurrent,
  int imgSize,
  float incFactor) const
{
  using namespace gpu_util;

  auto bwImgSize {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, imgSize
    )
  };

  auto bwIncFactor {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, incFactor
    )
  };

  cl::Kernel mandelbrotShift(program, "mandelbrotShift");
  setArgs(
    mandelbrotShift, imgCurrent, bwImgSize, bwIncFactor);
  queue.enqueueNDRangeKernel(
    mandelbrotShift, cl::NullRange, cl::NDRange(16), cl::NullRange);
}

}
