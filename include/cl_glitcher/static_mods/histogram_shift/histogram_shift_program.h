//
// Created by bridg on 4/7/2021.
//

#ifndef CL_GLITCHER_SRC_CL_GLITCHER_STATIC_MODS_HISTOGRAM_SHIFT_HISTOGRAM_SHIFT_PROGRAM_H
#define CL_GLITCHER_SRC_CL_GLITCHER_STATIC_MODS_HISTOGRAM_SHIFT_HISTOGRAM_SHIFT_PROGRAM_H

#include <array>

#include <gpu_util/gpu_handle.h>
#include <gpu_util/buffer_wrapper.h>

namespace clglitch::histogram_shift
{

class HistogramShiftProgram
{
  public:
    explicit HistogramShiftProgram(gpu_util::GpuHandle const & gpuHandle);

    void execute(
      cl::CommandQueue & queue,
      gpu_util::GpuHandle const & gpuHandle,
      gpu_util::BufferWrapper & imgIn,
      gpu_util::BufferWrapper & imgCurrent,
      int imgSize,
      gpu_util::BufferWrapper const & histIndices,
      unsigned incMin,
      unsigned incMax,
      float incFactor) const;


  private:
    cl::Program program;
};

}

#endif //CL_GLITCHER_SRC_CL_GLITCHER_STATIC_MODS_HISTOGRAM_SHIFT_HISTOGRAM_SHIFT_PROGRAM_H
