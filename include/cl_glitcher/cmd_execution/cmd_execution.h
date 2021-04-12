//
// Created by bridg on 3/19/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_CMD_EXECUTION_CMD_EXECUTION_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_CMD_EXECUTION_CMD_EXECUTION_H

#include <cmd_execution/cmd_execution_params.h>
#include <mod_environment/mod_environment.h>
#include <mod_sys/mod_sys.h>
#include <json_defs/json_obj_type.h>

namespace clglitch {

class CmdData
{
  public:
    ModSys modSys;
    CmdEnvironment cmdEnv;
    SystemEnvironment systemEnv;
    JsonDocType cmd;
};


/// Mostly used for testing purposes. Only loadAndExecute should be used outside of testing.
class CmdExecution
{
  public:
    explicit CmdExecution(CmdExecutionParams params);

    static CmdExecution loadAndExecute(CmdExecutionParams params);

    void loadStaticMods();
    void loadDynamicMods();
    void loadCmd();
    void loadCmdEnv();
    void loadSystemEnv();

    void execute() const;

    CmdData const & getCmdData() const;

  private:
    CmdExecutionParams params;
    CmdData cmdData;

    JsonObjType getInlineEnv();
};

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_CMD_EXECUTION_CMD_EXECUTION_H
