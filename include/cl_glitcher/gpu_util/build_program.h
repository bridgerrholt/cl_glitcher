//
// Created by bridg on 3/5/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_BUILD_PROGRAM_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_BUILD_PROGRAM_H

#include "gpu_handle.h"

namespace clglitch::gpu_util {

cl::Program buildProgram(
  GpuHandle const & gpuHandle, cl::Program::Sources const & sources);

cl::Program buildProgramFromFile(
  GpuHandle const & gpuHandle, std::string const & filename);

cl::Program buildProgramFromFiles(
  GpuHandle const & gpuHandle, std::vector<std::string> const & filenames);

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_BUILD_PROGRAM_H
