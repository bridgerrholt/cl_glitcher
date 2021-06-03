//
// Created by bridg on 6/2/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_PROGRAMS_SORT_HISTOGRAM_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_PROGRAMS_SORT_HISTOGRAM_H

#include <gpu_util/gpu_handle.h>
#include <gpu_util/buffer_wrapper.h>

#include "histogram_array.h"

namespace clglitch::gpu_programs {

HistogramIndexArray sortHistogram(
  cl::CommandQueue & queue,
  gpu_util::GpuHandle const & gpuHandle,
  gpu_util::BufferWrapper const & histBuffer);

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_PROGRAMS_SORT_HISTOGRAM_H
