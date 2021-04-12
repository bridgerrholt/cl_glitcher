//
// Created by bridg on 3/19/2021.
//

#include <cmd_execution/cmd_execution_params.h>

namespace clglitch
{

bool CmdExecutionParams::operator==(CmdExecutionParams const & other) const
{
  return
    jsonInstanceFilename == other.jsonInstanceFilename &&
      jsonModFilename == other.jsonModFilename &&
      globalEnvironmentFilename == other.globalEnvironmentFilename;
}

}
