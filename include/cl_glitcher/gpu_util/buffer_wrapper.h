//
// Created by bridg on 3/5/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_BUFFER_WRAPPER_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_BUFFER_WRAPPER_H

#include "gpu_handle.h"

namespace clglitch::gpu_util {

class BufferWrapper
{
  public:

    BufferWrapper(
      GpuHandle const & gpuHandle,
      cl_mem_flags flags,
      std::size_t arrSize) :
      buffer { gpuHandle.context, flags, arrSize }
    {

    }

    template <class Arr>
    static BufferWrapper fromArr(
      GpuHandle const & gpuHandle,
      cl_mem_flags flags,
      Arr const & arr)
    {
      return { gpuHandle, flags, calcSize(arr) };
    }

    template <class Arr>
    static BufferWrapper writeBuffer(
      cl::CommandQueue & queue,
      GpuHandle const & gpuHandle,
      cl_mem_flags flags,
      Arr const & arr)
    {
      auto bw { BufferWrapper::fromArr(gpuHandle, flags, arr) };
      bw.enqueueWrite(queue, arr);
      return bw;
    }

    template <class Arr>
    static BufferWrapper writeBuffer(
      cl::CommandQueue & queue,
      GpuHandle const & gpuHandle,
      cl_mem_flags flags,
      Arr const & arr,
      std::size_t arrSize)
    {
      BufferWrapper bw { gpuHandle, flags, arrSize };
      bw.enqueueWrite(queue, arr, arrSize);
      return bw;
    }

    template <class Arr>
    void enqueueWrite(cl::CommandQueue & queue, Arr const & arr)
    {
      std::size_t s {calcSize(arr)};
      queue.enqueueWriteBuffer(buffer, CL_TRUE, 0, s, arr.data());
    }

    template <class Type>
    void enqueueWrite(cl::CommandQueue & queue, Type const * arr, std::size_t arrSize)
    {
      std::size_t s {sizeof(Type) * arrSize};
      queue.enqueueWriteBuffer(buffer, CL_TRUE, 0, s, arr);
    }

    template <class Arr>
    void enqueueRead(cl::CommandQueue & queue, Arr & arr)
    {
      std::size_t s {calcSize(arr)};
      queue.enqueueReadBuffer(buffer, CL_TRUE, 0, s, arr.data());
    }

    template <class Type>
    void enqueueRead(cl::CommandQueue & queue, Type * arr, std::size_t arrSize)
    {
      queue.enqueueReadBuffer(buffer, CL_TRUE, 0, sizeof(Type) * arrSize, arr);
    }

    cl::Buffer const & getBuffer() const;
    cl::Buffer & getBuffer();



  private:
    template <class Arr>
    static std::size_t calcSize(Arr const & arr)
    {
      return sizeof(typename Arr::value_type) * arr.size();
    }

    cl::Buffer buffer;
};

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_UTIL_BUFFER_WRAPPER_H
