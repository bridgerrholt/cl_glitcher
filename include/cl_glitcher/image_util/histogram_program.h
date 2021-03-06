//
// Created by bridg on 3/5/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_IMAGE_UTIL_HISTOGRAM_PROGRAM_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_IMAGE_UTIL_HISTOGRAM_PROGRAM_H

#include <array>

#include <gpu_util/gpu_handle.h>

namespace clglitch::image_util {

class HistogramProgram
{
  public:
    explicit HistogramProgram(gpu_util::GpuHandle const & gpuHandle);

    std::array<unsigned int, 256> execute(
      gpu_util::GpuHandle const & gpuHandle,
      unsigned char const * img,
      int imgSize);

  private:
    cl::Program program;
};

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_IMAGE_UTIL_HISTOGRAM_PROGRAM_H
