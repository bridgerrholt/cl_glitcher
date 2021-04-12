//
// Created by bridg on 3/19/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_CMD_EXECUTION_CMD_EXECUTION_PARAMS_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_CMD_EXECUTION_CMD_EXECUTION_PARAMS_H

#include <string>

namespace clglitch
{

class CmdExecutionParams
{
  public:
    std::string jsonInstanceFilename;
    std::string jsonModFilename;
    std::string globalEnvironmentFilename;
    std::string localEnvironmentFilename;

    bool operator==(CmdExecutionParams const & other) const;
};

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_CMD_EXECUTION_CMD_EXECUTION_PARAMS_H
