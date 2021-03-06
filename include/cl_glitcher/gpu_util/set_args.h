//
// Created by bridg on 3/5/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_SET_ARGS_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_SET_ARGS_H

#include "buffer_wrapper.h"

namespace clglitch::gpu_util {

template <std::size_t index, class T>
void setArgsI(cl::Kernel kernel, T const & bwI)
{
  kernel.setArg(index, bwI.getBuffer());
}



template <std::size_t index, class T, class ... ArgPack>
void setArgsI(cl::Kernel kernel, T const & bwI, ArgPack && ... args)
{
  setArgsI<index>(kernel, bwI);
  setArgsI<index + 1>(kernel, std::forward<ArgPack>(args)...);
}



template <class T, class ... ArgPack>
void setArgs(cl::Kernel kernel, T const & bw)
{
  kernel.setArg(0, bw.getBuffer());
}



template <class T, class ... ArgPack>
void setArgs(cl::Kernel kernel, T const & bw0, ArgPack && ... args)
{
  setArgs(kernel, bw0);
  setArgsI<1>(kernel, std::forward<ArgPack>(args)...);
}

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_SET_ARGS_H
