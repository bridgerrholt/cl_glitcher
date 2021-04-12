//
// Created by bridg on 3/27/2021.
//

#include <cmd_execution/system_environment.h>

namespace clglitch {


SystemEnvironment::SystemEnvironment(
  std::filesystem::path cmdFilePath)
:
  cmdFilePath_(std::move(cmdFilePath)) {}



std::filesystem::path const & SystemEnvironment::cmdFilePath() const
{
  return cmdFilePath_;
}



std::string SystemEnvironment::cmdFileDir() const
{
  return cmdFilePath_.parent_path().generic_string();
}



std::string SystemEnvironment::cmdFilename() const
{
  return cmdFilePath_.filename().generic_string();
}

}