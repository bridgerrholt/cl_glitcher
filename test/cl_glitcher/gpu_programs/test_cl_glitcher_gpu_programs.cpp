#include <gpu_programs/histogram_program.h>

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