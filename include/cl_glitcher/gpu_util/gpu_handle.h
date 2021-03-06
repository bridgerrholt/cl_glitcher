//
// Created by bridg on 3/5/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_GPU_HANDLE_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_GPU_HANDLE_H

#include "gpu_headers.h"

namespace clglitch::gpu_util {

class GpuHandle
{
  public:
    explicit GpuHandle(cl::Device device);

    cl::Context context;
    cl::Device device;
};

}


#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_GPU_HANDLE_H
