//
// Created by bridg on 3/5/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_PROGRAMS_HISTOGRAM_PROGRAM_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_PROGRAMS_HISTOGRAM_PROGRAM_H

#include <gpu_util/gpu_handle.h>
#include <gpu_util/buffer_wrapper.h>

#include "histogram_array.h"

namespace clglitch::gpu_programs {

class HistogramProgram
{
  public:
    explicit HistogramProgram(gpu_util::GpuHandle const & gpuHandle);

    HistogramArray execute(
      gpu_util::GpuHandle const & gpuHandle,
      unsigned char const * img,
      int imgSize) const;

    gpu_util::BufferWrapper execute(
      cl::CommandQueue & queue,
      gpu_util::GpuHandle const & gpuHandle,
      unsigned char const * img,
      int imgSize) const;

    gpu_util::BufferWrapper execute(
      cl::CommandQueue & queue,
      gpu_util::GpuHandle const & gpuHandle,
      gpu_util::BufferWrapper const & img,
      int imgSize) const;

    void execute(
      cl::CommandQueue & queue,
      gpu_util::GpuHandle const & gpuHandle,
      unsigned char const * img,
      int imgSize,
      gpu_util::BufferWrapper & resBuffer) const;

    void execute(
      cl::CommandQueue & queue,
      gpu_util::GpuHandle const & gpuHandle,
      gpu_util::BufferWrapper const & img,
      int imgSize,
      gpu_util::BufferWrapper & resBuffer) const;

  private:
    cl::Program program;
};

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_IMAGE_UTIL_HISTOGRAM_PROGRAM_H
