//
// Created by bridg on 2/15/2021.
//

#include <string>
#include <cassert>
#include <numeric>

#include <opencv2/opencv.hpp>

#include <mandelbrot_shift.h>
#include <mandelbrot_shift_program.h>
#include <file_util/append_number.h>


namespace clglitch::mandelbrot_shift
{

namespace {

void iterExecute(
  std::string const & outputFile)
{
}



template <class Functor>
void imageNameLoop(
  std::filesystem::path const & path,
  std::string const & ext,
  std::size_t imageCount,
  Functor && iterFunc)
{
  std::size_t digits {file_util::calcDigits(imageCount - 1)};

  auto outPath = path.parent_path();
  outPath /= path.stem();

  for (std::size_t i {0}; i < imageCount; i++) {
    std::string outputFile {outPath.generic_string() + "_"};
    file_util::appendNumber(outputFile, digits, i);
    outputFile += ext;

    iterFunc(outputFile);
  }
}



std::string getExt(CmdEnvironment const & cmdEnv)
{
  JsonObjType const * extObj = cmdEnv.getVar("outputExtension");
  if (extObj == nullptr) {
    throw std::runtime_error("outputExtension environment variable must be defined");
  }

  auto extLength = extObj->GetStringLength();
  char const * ext = extObj->GetString();

  if (extLength == 0) {
    return "";
  }

  if (ext[0] == '.') {
    return ext + 1;
  }
  else {
    return std::string(".") + ext;
  }
}





/*template <class JsonArray>
LineSegment deserializeArrayOfNumTimes(
  HistogramShiftData::NumTimeArray & numArr,
  JsonArray const & jsonArray)
{
  float t = 1.0f / jsonArray.Size();
  for (auto const & v : jsonArray) {
    if (v.IsArray()) {
      if (v.Size() == 2) {
        numArr.emplace_back(verifyNumber(v[0]), verifyTime(v[1]));
      }
      else {
        throw std::runtime_error("NumTimeArray elements must have size of 2");
      }
    }
    else {
      throw std::runtime_error("All elements of NumTimeArray must be same type");
    }
  }
}*/

template <class Value, class Func>
std::vector<Value> lineSegmentToValueArrayImpl(
  LineSeries<Value> const & line,
  unsigned imageCount,
  Func && valueTransform)
{
  std::vector<Value> res;
  res.resize(imageCount);

  /*float timeSum = std::accumulate(
    line.frames.begin(),
    line.frames.end(),
    0.0f,
    [](auto a, auto b) { return a + b.time; });*/


  if (line.frames.empty()) {
    std::fill(res.begin(), res.end(), line.initial);
  }
  else {
    std::size_t i {0};
    //float tStep = timeSum / (float)imageCount;
    float tStep = 1.0f / (float)(imageCount - 1);
    float t {0};
    float currentTotalT {0};
    Value lastValue {line.initial};

    for (auto const & v : line.frames) {
      while (t < currentTotalT + v.time && i < imageCount) {
        float timeFactor = (t - currentTotalT) / v.time;
        float valueFactor = (float)v.value - (float)lastValue;
        float rawValue = (float)lastValue + timeFactor * valueFactor;

        res[i] = valueTransform(rawValue);

        i += 1;
        t += tStep;
      }

      currentTotalT += v.time;
      lastValue = v.value;
    }
  }

  return res;
}



template <class Value>
std::vector<Value> lineSegmentToValueArray(
  LineSeries<Value> const & line,
  unsigned imageCount)
{
  return lineSegmentToValueArrayImpl(
    line, imageCount,
    [](float val) {
      return (Value)val;
    }
  );
}



template <>
std::vector<unsigned> lineSegmentToValueArray(
  LineSeries<unsigned> const & line,
  unsigned imageCount)
{
  return lineSegmentToValueArrayImpl(
    line, imageCount,
    [](float val) {
      return (unsigned)std::max(0.0f, val);
    }
  );
}

}



void jsonObjExecute(JsonObjExecuteParams const & params)
{
  MandelbrotShiftData data;
  json_util::deserialize(params.data, data);

  std::string ext {getExt(params.cmdEnv)};

  auto const * imageCountField = params.cmdEnv.getVar("imageCount");
  assert(imageCountField != nullptr);

  auto imgCurrent = gpu_util::BufferWrapper::writeBuffer(
    params.commandQueue,
    params.gpuHandle,
    CL_MEM_READ_WRITE,
    params.currentImageMat.data,
    params.imgSizeBytes
  );

  /*HistogramArray res;
  hist.enqueueRead(params.commandQueue, res);
  params.commandQueue.finish();*/

  auto const & path = params.systemEnv.cmdFilePath();

  unsigned imageCount {imageCountField->GetUint()};
  auto incFactorArr = lineSegmentToValueArray(data.incFactor, imageCount);

  unsigned i {0};
  imageNameLoop(
    path,
    ext,
    imageCountField->GetUint(),
    [&](std::string const & outputFilename) {
      std::cout << incFactorArr[i] << "\n";

      MandelbrotShiftProgram program {params.gpuHandle};
      program.execute(
        params.commandQueue,
        params.gpuHandle,
        imgCurrent,
        params.imgSizeBytes,
        incFactorArr[i]);



      //std::vector<unsigned int> res;
      //res.resize(params.imgSizeBytes);

      // read result from GPU to here
      imgCurrent.enqueueRead(
        params.commandQueue,
        params.currentImageMat.data,
        params.imgSizeBytes);
      params.commandQueue.finish();

      cv::imwrite(outputFilename, params.currentImageMat);

      i += 1;
    }
  );
}

}