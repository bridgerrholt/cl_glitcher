//
// Created by bridg on 3/9/2021.
//

#ifndef CL_GLITCHER_TEST_CL_GLITCHER_IMAGE_UTIL_GTEST_CV_MAT_WRAPPER_H
#define CL_GLITCHER_TEST_CL_GLITCHER_IMAGE_UTIL_GTEST_CV_MAT_WRAPPER_H

#include <opencv2/opencv.hpp>

class GtestCvMatPrinterUVec3
{
  public:
    using VType = cv::Vec3b;

    template <class OStream>
    static void print(OStream & os, cv::Mat const & mat)
    {
      for (int j {0}; j < mat.rows; j++)
      {
        for (int i {0}; i < mat.cols; i++)
        {
          auto v = mat.at<cv::Vec3b>(j, i);
          os << '(';

          for (int c {0}; c < 2; c++)
          {
            os << (unsigned int) v[c] << ' ';
          }

          os << (unsigned int) v[2] << ") ";
        }

        os << '\n';
      }
    }
};



template <class Printer>
class GtestCvMatWrapper
{
  public:
    cv::Mat mat;

    bool operator==(GtestCvMatWrapper const & other) const
    {
      return std::equal(
        mat.begin<typename Printer::VType>(),
        mat.end<typename Printer::VType>(),
        other.mat.template begin<typename Printer::VType>()
      );
    }

    friend std::ostream & operator<<(
      std::ostream & os,
      GtestCvMatWrapper const & m)
    {
      Printer::print(os, m.mat);
      return os;
    }
};

#endif //CL_GLITCHER_TEST_CL_GLITCHER_IMAGE_UTIL_GTEST_CV_MAT_WRAPPER_H
