//
// Created by bridg on 3/5/2021.
//


#include <gpu_util/build_program.h>
#include <file_util/load_file_to_string.h>

#include <sstream>

namespace clglitch::gpu_util {

cl::Program buildProgram(
  GpuHandle const & gpuHandle,
  cl::Program::Sources const & sources)
{
  cl::Program program {gpuHandle.context, sources};

  if (program.build({gpuHandle.device}) != CL_SUCCESS)
  {
    std::stringstream ss;
    ss <<
      "Error building: " <<
      program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(gpuHandle.device);
    throw std::runtime_error(ss.str());
  }

  return program;
}


std::string pushFile(cl::Program::Sources & sources, std::string const & filename)
{
  std::string str {file_util::loadFileToString(filename)};
  sources.emplace_back(str.c_str(), str.size());
  return str;
}


cl::Program buildProgramFromFile(
  GpuHandle const & gpuHandle, std::string const & filename)
{
  cl::Program::Sources sources;
  std::string s {pushFile(sources, filename)};
  return buildProgram(gpuHandle, sources);
}



cl::Program buildProgramFromFiles(
  GpuHandle const & gpuHandle, std::vector<std::string> const & filenames)
{
  cl::Program::Sources sources;
  std::vector<std::string> strings;
  strings.reserve(filenames.size());
  for (auto const & filename : filenames)
    strings.push_back(pushFile(sources, filename));
  return buildProgram(gpuHandle, sources);
}

}