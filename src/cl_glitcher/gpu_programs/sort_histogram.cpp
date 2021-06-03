//
// Created by bridg on 6/3/2021.
//

#include <gpu_programs/sort_histogram.h>
#include <array>
#include <algorithm>

namespace clglitch::gpu_programs {

HistogramIndexArray sortHistogram(
  cl::CommandQueue & queue,
  gpu_util::GpuHandle const & gpuHandle,
  gpu_util::BufferWrapper const & histBuffer)
{
  // Image size limited to 37837x37837 technically.
  // This is sqrt((2**32)/3)
  HistogramArray histArr {};

  histBuffer.enqueueRead(queue, histArr);
  queue.finish();

  class IndexedValue
  {
    public:
      unsigned int value;
      unsigned char index;
  };
  std::array<IndexedValue, 256> indexedHistArr {};

  {
    unsigned char i {0};
    std::generate(
      indexedHistArr.begin(),
      indexedHistArr.end(),
      [&]() {
        IndexedValue v {histArr[i], i};
        i += 1;
        return v;
      });
  }

  std::sort(
    indexedHistArr.begin(),
    indexedHistArr.end(),
    [](auto a, auto b) {
      return a.value > b.value;
    });

  HistogramIndexArray histIndices {};
  for (std::size_t i {0}; i < histogramIndexArraySize(); i++) {
    histIndices[indexedHistArr[i].index] = (unsigned char) i;
  }

  return histIndices;
}

}