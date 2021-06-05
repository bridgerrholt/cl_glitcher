//
// Created by bridg on 2/15/2021.
//

#include <string>
#include <cassert>
#include <numeric>

#include <opencv2/opencv.hpp>

#include <histogram_shift.h>
#include <histogram_shift_program.h>
#include <file_util/append_number.h>
#include <gpu_programs/histogram_program.h>
#include <gpu_programs/sort_histogram.h>


namespace clglitch::histogram_shift
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



unsigned verifyNumber(rapidjson::Value const & value)
{
  std::cout << value.GetUint() << '\n';
  return value.GetUint();
}



float verifyTime(rapidjson::Value const & value)
{
  return value.GetFloat();
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

std::vector<unsigned> lineSegmentToValueArray(
  LineSegment const & line,
  unsigned imageCount)
{
  std::vector<unsigned> res;
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
    unsigned lastValue {line.initial};

    for (auto const & v : line.frames) {
      while (t < currentTotalT + v.time && i < imageCount) {
        float timeFactor = (t - currentTotalT) / v.time;
        float valueFactor = (float)v.value - (float)lastValue;
        float rawValue = (float)lastValue + timeFactor * valueFactor;

        res[i] = (unsigned)std::max(0.0f, rawValue);

        i += 1;
        t += tStep;
      }

      currentTotalT += v.time;
      lastValue = v.value;
    }
  }

  return res;
}

}


void LineSegment::deserializeFrames(
  LineSegment & owner,
  std::vector<ValueTimePair> & frames,
  rapidjson::Value const & value)
{
  auto const & arr = value.GetArray();

  if (!arr.Empty()) {
    if (arr[0].IsNumber()) {
      deserializeFramesFromValueArr(frames, arr.begin(), arr.Size());
    }
    else if (arr[0].IsArray()) {
      deserializeFramesFromFrameArr(frames, arr);
    }
    else {
      throw std::runtime_error("Invalid element data type of NumTimeArray");
    }
  }
  else {
    throw std::runtime_error("NumTimeArray must not be empty");
  }
}



void LineSegment::deserializeFramesFromValueArr(
  std::vector<ValueTimePair> & frames,
  rapidjson::Value::ConstArray::ValueIterator arrayBegin,
  rapidjson::SizeType arraySize)
{
  if (arraySize > 0) {
    frames.reserve(arraySize);
    float t {1.0f / (float)arraySize};
    for (std::size_t i {0}; i < arraySize; i++) {
      auto const & v = arrayBegin[i];
      if (v.IsUint()) {
        frames.emplace_back(v.GetUint(), t);
      }
      else {
        throw std::runtime_error(
          "All elements of LineSegment frame arrays must be the same type.");
      }
    }
  }
}


void LineSegment::deserializeFramesFromFrameArr(
  std::vector<ValueTimePair> & frames,
  rapidjson::Value::ConstArray const & jsonArray)
{
  for (auto const & v : jsonArray) {
    if (v.IsArray()) {
      if (v.Size() == 2) {
        frames.emplace_back(verifyNumber(v[0]), verifyTime(v[1]));
      }
      else {
        throw std::runtime_error("Elements of frame arrays must have a size of 2.");
      }
    }
    else {
      throw std::runtime_error(
        "All elements of LineSegment frame arrays must be the same type.");
    }
  }
}




LineSegment LineSegment::multiFormatDeserialize(
  rapidjson::Value const & value)
{
  if (value.IsNumber()) {
    return {verifyNumber(value), {}};
  }
  else if (value.IsArray()) {
    LineSegment line;
    line.deserializeFromValueArr(value.GetArray());
    return line;

    /*auto const & arr = value.GetArray();

    if (!arr.Empty()) {
      if (arr[0].IsNumber()) {
        return deserializeArrayOfNums(arr);
      }
      else if (arr[0].IsArray()) {
        return deserializeArrayOfNumTimes(arr);
      }
      else {
        throw std::runtime_error("Invalid element data type of NumTimeArray");
      }
    }
    else {
      throw std::runtime_error("NumTimeArray must not be empty");
    }*/
  }
  else if (value.IsObject()) {
    return json_util::deserialize<LineSegment>(value);
  }
  else {
    throw std::runtime_error("Invalid data type for NumTimeArray");
  }
}



void LineSegment::deserializeFromValueArr(
  rapidjson::Value::ConstArray const & jsonArray)
{
  auto s = jsonArray.Size();

  if (s > 0) {
    initial = verifyNumber(jsonArray[0]);
    deserializeFramesFromValueArr(frames, jsonArray.begin() + 1, s - 1);
  }
  else {
    throw std::runtime_error(
      "Value array used to initialize LineSegment must not be empty.");
  }
}



void HistogramShiftData::deserializeLine(
  HistogramShiftData & owner,
  LineSegment & line,
  rapidjson::Value const & value)
{
  line = LineSegment::multiFormatDeserialize(value);
}


void jsonObjExecute(JsonObjExecuteParams const & params)
{
  using namespace gpu_programs;

  HistogramShiftData data;
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

  HistogramProgram histProgram {params.gpuHandle};
  // TODO: Use the resBuffer overload (instead of allocating a new buffer each iteration)
  auto hist = histProgram.execute(
    params.commandQueue,
    params.gpuHandle,
    params.currentImage, // TODO: Change name to imgIn
    params.imgSizeBytes);

  /*HistogramArray res;
  hist.enqueueRead(params.commandQueue, res);
  params.commandQueue.finish();*/

  auto histIndices =
    sortHistogram(params.commandQueue, params.gpuHandle, hist);
  auto histIndicesBuffer = gpu_util::BufferWrapper::writeBuffer(
    params.commandQueue,
    params.gpuHandle,
    CL_MEM_READ_WRITE, // TODO: Change to READ_ONLY?
    histIndices);

  auto const & path = params.systemEnv.cmdFilePath();

  auto incMinArr = lineSegmentToValueArray(data.incMin, imageCountField->GetUint());
  auto incMaxArr = lineSegmentToValueArray(data.incMax, imageCountField->GetUint());

  unsigned i {0};
  imageNameLoop(
    path,
    ext,
    imageCountField->GetUint(),
    [&](std::string const & outputFilename) {
      std::cout << incMinArr[i] << " " << incMaxArr[i] << "\n";

      HistogramShiftProgram program {params.gpuHandle};
      program.execute(
        params.commandQueue,
        params.gpuHandle,
        params.currentImage,
        imgCurrent,
        params.imgSizeBytes,
        histIndicesBuffer,
        incMinArr[i],
        incMaxArr[i],
        data.incFactor);



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