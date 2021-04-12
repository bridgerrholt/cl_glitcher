//
// Created by bridg on 3/27/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_CMD_EXECUTION_SYSTEM_ENVIRONMENT_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_CMD_EXECUTION_SYSTEM_ENVIRONMENT_H

#include <string>
#include <filesystem>

#include <gpu_util/buffer_wrapper.h>

namespace clglitch {

class SystemEnvironment
{
  public:
    SystemEnvironment() = default;
    explicit SystemEnvironment(std::filesystem::path cmdFilePath);

    std::filesystem::path const & cmdFilePath() const;
    std::string cmdFileDir() const;
    std::string cmdFilename() const;

  private:
    std::filesystem::path cmdFilePath_;
};

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_CMD_EXECUTION_SYSTEM_ENVIRONMENT_H
