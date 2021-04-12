//
// Created by bridg on 3/12/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_LOAD_MOD_ENVIRONMENT_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_LOAD_MOD_ENVIRONMENT_H

#include "mod_environment.h"

namespace clglitch {

// TODO: Implement local mod filename specifier.
CmdEnvironment loadModEnvironment(
  std::string const & globalEnvFilename,
  std::string commandFileDirectory,
  JsonObjType inlineEnv);

CmdEnvironment loadModEnvironmentDefaultGlobal(
  std::string commandFileDirectory,
  JsonObjType inlineEnv);

}


#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_LOAD_MOD_ENVIRONMENT_H
