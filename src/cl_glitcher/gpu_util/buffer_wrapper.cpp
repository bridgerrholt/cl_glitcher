//
// Created by bridg on 3/5/2021.
//

#include <gpu_util/buffer_wrapper.h>

namespace clglitch::gpu_util {

cl::Buffer const & BufferWrapper::getBuffer() const
{
  return buffer;
}

cl::Buffer & BufferWrapper::getBuffer()
{
  return buffer;
}

}