#include <gpu_util/init.h>
#include <gpu_util/build_program.h>

#include <gtest/gtest.h>

#include <array>

#include "test_cl_glitcher_vector_addition.h"

using namespace clglitch;
using namespace gpu_util;

constexpr char const * directory {CL_GLITCHER_TEST_DIRECTORY_GPU_UTIL};
std::string const vectorAdditionFile {std::string{directory} + "/test_cl_glitcher_vector_addition.cl"};

template <int n>
std::array<int, n> runVectorAddition(GpuHandle const & gpuHandle, cl::Program const & program)
{
  // apparently OpenCL only likes arrays ...
  // N holds the number of elements in the vectors we want to add
  constexpr int N[1] = {n};

  // create buffers on device (allocate space on GPU)
  cl::Buffer buffer_A(gpuHandle.context, CL_MEM_READ_WRITE, sizeof(int) * n);
  cl::Buffer buffer_B(gpuHandle.context, CL_MEM_READ_WRITE, sizeof(int) * n);
  cl::Buffer buffer_C(gpuHandle.context, CL_MEM_READ_WRITE, sizeof(int) * n);
  cl::Buffer buffer_N(gpuHandle.context, CL_MEM_READ_ONLY,  sizeof(int));

  // create things on here (CPU)
  int A[n], B[n];
  for (int i = 0; i < n; i++) {
    A[i] = i;
    B[i] = n - i - 1;
  }
  // create a queue (a queue of commands that the GPU will execute)
  cl::CommandQueue queue(gpuHandle.context, gpuHandle.device);

  // push write commands to queue
  queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int)*n, A);
  queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int)*n, B);
  queue.enqueueWriteBuffer(buffer_N, CL_TRUE, 0, sizeof(int),   N);

  // RUN ZE KERNEL
  //cl::KernelFunctor simple_add(cl::Kernel(program, "simple_add"), queue, cl::NullRange, cl::NDRange(10), cl::NullRange);
  //simple_add(buffer_A, buffer_B, buffer_C, buffer_N);

  cl::Kernel simple_add(program, "simple_add");
  simple_add.setArg(0, buffer_A);
  simple_add.setArg(1, buffer_B);
  simple_add.setArg(2, buffer_C);
  simple_add.setArg(3, buffer_N);
  queue.enqueueNDRangeKernel(simple_add,cl::NullRange,cl::NDRange(10),cl::NullRange);
  queue.finish();

  std::array<int, n> C {};
  // read result from GPU to here
  queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int)*n, C.data());

  return C;
}


TEST(TestClGlitcherGpuUtil, Init)
{
  GpuHandle gpu {init()};
}



TEST(TestClGlitcherGpuUtil, VectorAdditionFromSources)
{
  GpuHandle data {init()};

  // create the program that we want to execute on the device
  cl::Program::Sources sources;

  // calculates for each element; C = A + B
  std::string kernel_code =
    "   void kernel simple_add(global const int* A, global const int* B, global int* C, "
    "                          global const int* N) {"
    "       int ID, Nthreads, n, ratio, start, stop;"
    ""
    "       ID = get_global_id(0);"
    "       Nthreads = get_global_size(0);"
    "       n = N[0];"
    ""
    "       ratio = (n / Nthreads);"  // number of elements for each thread
    "       start = ratio * ID;"
    "       stop  = ratio * (ID + 1);"
    ""
    "       for (int i=start; i<stop; i++)"
    "           C[i] = A[i] + B[i];"
    "   }";
  sources.push_back({kernel_code.c_str(), kernel_code.size()});

  cl::Program program {buildProgram(data, sources)};

  constexpr int n = 100;

  std::array<int, n> C {runVectorAddition<n>(data, program)};

  std::array<int, n> cDesired {};
  std::fill(cDesired.begin(), cDesired.end(), n - 1);

  ASSERT_EQ(C, cDesired);
}



TEST(TestClGlitcherGpuUtil, VectorAdditionFromFile)
{
  GpuHandle data {init()};

  cl::Program program {buildProgramFromFile(data, vectorAdditionFile)};

  constexpr int n = 100;

  std::array<int, n> C {runVectorAddition<n>(data, program)};

  std::array<int, n> cDesired {};
  std::fill(cDesired.begin(), cDesired.end(), n - 1);

  ASSERT_EQ(C, cDesired);
}



TEST(TestClGlitcherGpuUtil, VectorAdditionFromHeader)
{
  GpuHandle data {init()};

  cl::Program program {buildProgram(data, {{test::vectorAdditionStr.c_str(), test::vectorAdditionStr.size()}})};

  constexpr int n = 100;

  std::array<int, n> C {runVectorAddition<n>(data, program)};

  std::array<int, n> cDesired {};
  std::fill(cDesired.begin(), cDesired.end(), n - 1);

  ASSERT_EQ(C, cDesired);
}