//
// Created by bridg on 8/8/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_MANDELBROT_MANDELBROT_PROGRAM_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_MANDELBROT_MANDELBROT_PROGRAM_H

#include <gpu_util/gpu_handle.h>
#include <gpu_util/buffer_wrapper.h>

namespace clglitch::mandelbrot
{

class MandelbrotProgram
{
  public:
    explicit MandelbrotProgram(gpu_util::GpuHandle const & gpuHandle);

    void execute(
      cl::CommandQueue & queue,
      gpu_util::GpuHandle const & gpuHandle,
      gpu_util::BufferWrapper & imgIn,
      gpu_util::BufferWrapper & imgCurrent,
      int imgSize,
      float steps,
      float n,
      float radius,
      bool imageFeedback,
      cl_float3 sphereOffset) const;


  private:
    cl::Program program;
};

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_MANDELBROT_MANDELBROT_PROGRAM_H
