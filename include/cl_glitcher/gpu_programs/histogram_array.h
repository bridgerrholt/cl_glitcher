//
// Created by bridg on 6/3/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_PROGRAMS_HISTOGRAM_ARRAY_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_PROGRAMS_HISTOGRAM_ARRAY_H


#include <array>

namespace clglitch::gpu_programs {

using HistogramArray = std::array<unsigned int, 256>;
using HistogramIndexArray = std::array<unsigned char, 256>;



constexpr std::size_t histogramArraySizeBytes()
{
  return
    std::tuple_size<HistogramArray>::value *
    sizeof(HistogramArray::value_type);
}



constexpr std::size_t histogramIndexArraySize()
{
  return std::tuple_size<HistogramIndexArray>::value;
}

}


#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_GPU_PROGRAMS_HISTOGRAM_ARRAY_H
