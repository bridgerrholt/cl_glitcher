//
// Created by bridg on 3/12/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_EXECUTE_CMD_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_EXECUTE_CMD_H

#include <mod_sys/mod_sys.h>
#include <mod_environment/mod_environment.h>

namespace clglitch {

void executeCmd(
  ModSys const & modSys,
  CmdEnvironment const & cmdEnv,
  SystemEnvironment const & systemEnv,
  JsonObjType const & cmd);

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_EXECUTE_CMD_H
