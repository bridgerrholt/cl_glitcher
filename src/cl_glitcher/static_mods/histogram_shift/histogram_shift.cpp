//
// Created by bridg on 2/15/2021.
//

#include <string>
#include <cassert>

#include <opencv2/opencv.hpp>

#include <histogram_shift.h>
#include <histogram_shift_program.h>
#include <file_util/append_number.h>
#include <gpu_programs/histogram_program.h>


namespace clglitch::histogram_shift
{

namespace {

void iterExecute(
  std::string const & outputFile)
{
}



template <class Functor>
void imageNameLoop(
  std::string const & cmdFileDir,
  std::string const & ext,
  std::size_t imageCount,
  Functor && iterFunc)
{
  std::size_t digits {file_util::calcDigits(imageCount)};

  for (std::size_t i {0}; i < imageCount; i++) {
    std::string outputFile {cmdFileDir};
    file_util::appendNumber(outputFile, digits, i);
    outputFile += ext;

    iterFunc(outputFile);
  }
}



std::string getExt(CmdEnvironment const & cmdEnv)
{
  JsonObjType const * extObj = cmdEnv.getVar("outputExtension");
  if (extObj == nullptr) {
    throw std::runtime_error("ext environment variable must be defined");
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

}


void jsonObjExecute(JsonObjExecuteParams const & params)
{
  using namespace gpu_programs;

  HistogramShiftData data;
  json_util::deserialize(params.data, data);

  std::string ext {getExt(params.cmdEnv)};

  auto const * imageCountField = params.cmdEnv.getVar("imageCount");
  assert(imageCountField != nullptr);

  imageNameLoop(
    params.systemEnv.cmdFileDir(),
    ext,
    imageCountField->GetUint(),
    [&](std::string const & outputFilename) {
      HistogramProgram histProgram {params.gpuHandle};
      // TODO: Use the resBuffer overload (instead of allocating a new buffer each iteration)
      auto hist = histProgram.execute(
        params.commandQueue,
        params.gpuHandle,
        params.currentImage,
        params.imgSizeBytes);

      HistogramShiftProgram program {params.gpuHandle};
      program.execute(
        params.commandQueue,
        params.gpuHandle,
        params.currentImage,
        params.imgSizeBytes,
        hist,
        data.incMin,
        data.incMax,
        data.incFactor);



      //std::vector<unsigned int> res;
      //res.resize(params.imgSizeBytes);

      // read result from GPU to here
      params.currentImage.enqueueRead(
        params.commandQueue,
        params.currentImageMat.data,
        params.imgSizeBytes);
      params.commandQueue.finish();

      cv::imwrite(outputFilename, params.currentImageMat);
    }
  );
}

}