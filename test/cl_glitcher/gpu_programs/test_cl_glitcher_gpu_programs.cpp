#include <gpu_programs/histogram_program.h>
#include <gpu_programs/sort_histogram.h>

#include <gtest/gtest.h>

#include <array>

#include <gpu_util/init.h>

using namespace clglitch;
using namespace gpu_util;

TEST(TestClGlitcherGpuPrograms, Histogram)
{
  using namespace gpu_programs;
  using namespace gpu_util;

  GpuHandle handle {init()};
  HistogramProgram program {handle};

  std::array<unsigned char, 1024> img {};
  for (std::size_t i {0}; i < 1024; i++)
  {
    img[i] = i % 256;
  }

  auto res { program.execute(handle, img.data(), img.size()) };

  std::array<unsigned int, 256> expected {};
  std::fill(expected.begin(), expected.end(), 4);

  ASSERT_EQ(res, expected);
}

TEST(TestClGlitcherGpuPrograms, HistogramSorted)
{
  using namespace gpu_programs;
  using namespace gpu_util;

  GpuHandle handle {init()};
  HistogramProgram program {handle};

  constexpr std::size_t s {5 * 4 * 3 * 2};
  std::array<unsigned char, s> img {};
  std::size_t index {0};
  for (unsigned char i {1}; i < 6; i++)
  {
    for (std::size_t j {0}; j < i; j++) {
      img[index] = i;
      index += 1;
    }
  }

  cl::CommandQueue queue(handle.context, handle.device);
  auto histBuffer { program.execute(queue, handle, img.data(), img.size()) };
  auto indices { sortHistogram(queue, handle, histBuffer) };

  ASSERT_EQ(indices[0], 0);
  ASSERT_EQ(indices[1], 5);
  ASSERT_EQ(indices[2], 4);
  ASSERT_EQ(indices[3], 3);
  ASSERT_EQ(indices[4], 2);
  ASSERT_EQ(indices[5], 1);
}