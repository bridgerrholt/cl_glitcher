//
// Created by bridg on 3/7/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_IMAGE_UTIL_LOAD_IMAGE_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_IMAGE_UTIL_LOAD_IMAGE_H

#include <opencv2/opencv.hpp>
#include <string>

namespace clglitch::image_util {

cv::Mat loadImage(std::string const & filename);

cv::Mat loadImage(std::string const & filename, cv::ImreadModes mode);

}


#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_IMAGE_UTIL_LOAD_IMAGE_H
