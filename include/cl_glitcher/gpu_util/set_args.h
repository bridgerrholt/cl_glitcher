//
// Created by bridg on 3/5/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_SET_ARGS_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_SET_ARGS_H

#include "buffer_wrapper.h"

namespace clglitch::gpu_util {

template <std::size_t index, class T>
void setArgsI(cl::Kernel kernel, T & arg)
{
  kernel.setArg(index, arg.getBuffer());
}



template <std::size_t index, class T, class ... ArgPack>
void setArgsI(cl::Kernel kernel, T & arg, ArgPack && ... args)
{
  kernel.setArg(index, arg.getBuffer());
  setArgsI<index + 1>(kernel, std::forward<ArgPack>(args)...);
}

template <class T, class ... ArgPack>
void setArgs(cl::Kernel kernel, T & arg, ArgPack && ... args)
{
  kernel.setArg(0, arg.getBuffer());
  setArgsI<1>(kernel, std::forward<ArgPack>(args)...);
}

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_SET_ARGS_H
