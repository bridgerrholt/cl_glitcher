//
// Created by bridg on 3/12/2021.
//

#include <filesystem>
#include <gpu_util/build_program.h>
#include <cmd_execution/execute_cmd.h>
#include <image_util/load_image.h>
#include <gpu_util/init.h>
#include <gpu_util/buffer_wrapper.h>

namespace clglitch {

namespace {

JsonObjType const & tryGetCmd(
  JsonObjType const & cmd)
{
  auto cmdIt = cmd.FindMember("cmd");
  if (cmdIt != cmd.MemberEnd()) {
    if (cmdIt->value.IsString()) {
      return cmdIt->value;
    }
    else {
      throw std::runtime_error(
        "Object in command file has non-string cmd field");
    }
  }
  else {
    throw std::runtime_error("Object in command file has no cmd field");
  }
}



JsonObjType const & tryGetData(
  JsonObjType const & data)
{
  auto dataIt = data.FindMember("data");
  if (dataIt != data.MemberEnd()) {
    return dataIt->value;
  }
  else {
    // TODO: Make this not throw (data may not always be required).
    throw std::runtime_error("Object in command file has no data field");
  }
}



// TODO: Make work with dynamic mods.
StaticModData const & tryGetMod(
  ModSys const & modSys,
  std::string const & cmdName)
{
  auto const * mod = modSys.getStaticMod(cmdName);
  if (mod != nullptr) {
    return *mod;
  }
  else {
    throw std::runtime_error("No such mod/cmd exists: " + cmdName);
  }
}



std::string tryGetInputImage(CmdEnvironment const & cmdEnv)
{
  auto const * it = cmdEnv.getVar("inputImage");
  if (it != nullptr) {
    return it->GetString();
  }
  else {
    throw std::runtime_error("No inputImage specified");
  }
}

}


void executeCmd(
  ModSys const & modSys,
  CmdEnvironment const & cmdEnv,
  SystemEnvironment const & systemEnv,
  std::string const & cmdPath,
  JsonObjType const & cmd)
{
  auto const & cmdField = tryGetCmd(cmd);
  auto const & dataField = tryGetData(cmd);
  auto const & mod = tryGetMod(modSys, cmdField.GetString());

  std::string inputImageFilename = tryGetInputImage(cmdEnv);
  auto inputImagePath =
    std::filesystem::path(cmdPath).parent_path() / inputImageFilename;
  inputImageFilename = inputImagePath.generic_string();
  cv::Mat imageMat {image_util::loadImage(inputImageFilename)};
  if (imageMat.empty()) {
    throw std::runtime_error(
      "Failed to load inputImage file \"" + inputImageFilename + '"'
    );
  }

  gpu_util::GpuHandle gpuHandle {gpu_util::init()};
  cl::CommandQueue queue(gpuHandle.context, gpuHandle.device);

  auto imgSize = imageMat.step[0] * imageMat.rows;
  auto imgBuffer = gpu_util::BufferWrapper::writeBuffer(
    queue, gpuHandle, CL_MEM_READ_WRITE, imageMat.data, imgSize
  );

  (mod.jsonObjExecute)({
    dataField,
    cmdEnv,
    systemEnv,
    imgBuffer,
    imageMat,
    (int)imgSize,
    gpuHandle,
    queue
  });
}

}