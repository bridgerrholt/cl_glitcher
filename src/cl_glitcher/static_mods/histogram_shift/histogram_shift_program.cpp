//
// Created by bridg on 4/7/2021.
//

#include <histogram_shift_program.h>

#include <gpu_util/build_program.h>
#include <gpu_util/buffer_wrapper.h>
#include <gpu_util/set_args.h>

#include <compute_kernels/static_mods/histogram_shift.h>
#include <gpu_util/init.h>

namespace clglitch::histogram_shift
{

HistogramShiftProgram::HistogramShiftProgram(
  gpu_util::GpuHandle const & gpuHandle) :
  program {
    gpu_util::buildProgram(
      gpuHandle, {{
        histogram_shift_program::histogramShiftStr.c_str(),
        histogram_shift_program::histogramShiftStr.size()
      }}
    )
  } {}



void HistogramShiftProgram::execute(
  cl::CommandQueue & queue,
  gpu_util::GpuHandle const & gpuHandle,
  gpu_util::BufferWrapper & imgIn,
  gpu_util::BufferWrapper & imgCurrent,
  int imgSize,
  gpu_util::BufferWrapper const & histIndices,
  unsigned incMin,
  unsigned incMax,
  float incFactor) const
{
  using namespace gpu_util;

  auto bwImgSize {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, imgSize
    )
  };

  auto bwIncMin {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, incMin
    )
  };

  auto bwIncMax {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, incMax
    )
  };

  auto bwIncFactor {
    BufferWrapper::writeBufferValue(
      queue, gpuHandle, CL_MEM_READ_ONLY, incFactor
    )
  };

  cl::Kernel histogramShift(program, "histogramShift");
  setArgs(
    histogramShift, imgIn, imgCurrent, bwImgSize, histIndices, bwIncMin, bwIncMax, bwIncFactor);
  queue.enqueueNDRangeKernel(
    histogramShift, cl::NullRange, cl::NDRange(16), cl::NullRange);
}

}
