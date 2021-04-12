#include <image_util/load_image.h>

#include <gtest/gtest.h>

#include <array>

#include "gtest_cv_mat_wrapper.h"


using namespace clglitch;
using namespace image_util;

constexpr char const * directory {CL_GLITCHER_TEST_DIRECTORY_IMAGE_UTIL};
std::string const vectorAdditionFile {std::string{directory} + "/test_cl_glitcher_image_1.png"};

TEST(TestClGlitcherImageUtil, LoadImage)
{
  auto m {loadImage(vectorAdditionFile)};

  //cv::Mat mExpected {3, 4, CV_8UC4, 0};
  cv::Mat mExpected {cv::Mat::zeros(cv::Size {4, 3}, CV_8UC3)};
  for (unsigned char i {0}; i < 4; i++) {
    unsigned char ratio {256 / 4};
    unsigned char value {(unsigned char)((i + 1) * ratio - 1)};
    mExpected.at<cv::Vec3b>(0, i)[0] = value;
    mExpected.at<cv::Vec3b>(1, i)[1] = value;
    mExpected.at<cv::Vec3b>(2, i)[2] = value;
  }

  //ASSERT_TRUE(std::equal(
  //  m.begin<cv::Vec4b>(), m.end<cv::Vec4b>(), mExpected.begin<cv::Vec4b>()
  //));

  using MatWrapper = GtestCvMatWrapper<GtestCvMatPrinterUVec3>;
  ASSERT_EQ(MatWrapper {m}, MatWrapper {mExpected});
}