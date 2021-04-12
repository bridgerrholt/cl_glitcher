//
// Created by bridg on 3/7/2021.
//

#include <image_util/load_image.h>

namespace clglitch::image_util {

cv::Mat loadImage(std::string const & filename)
{
  return cv::imread(filename);
}

cv::Mat loadImage(std::string const & filename, cv::ImreadModes mode)
{
  return cv::imread(filename, mode);
}

}
