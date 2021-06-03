//
// Created by bridg on 3/19/2021.
//

#include <cmd_execution/cmd_execution.h>

#include <filesystem>

#include <mod_sys/load_static_mods.h>
#include <mod_sys/load_dynamic_mods.h>
#include <mod_environment/load_mod_environment.h>
#include <json_util/load_json_file.h>
#include <cmd_execution/execute_cmd.h>

namespace clglitch
{


CmdExecution::CmdExecution(CmdExecutionParams params) :
  params {std::move(params)}
{

}



CmdExecution CmdExecution::loadAndExecute(CmdExecutionParams params)
{
  CmdExecution res {std::move(params)};

  res.loadStaticMods();
  res.loadDynamicMods();
  res.loadCmd();
  res.loadCmdEnv();
  res.loadSystemEnv();
  res.execute();

  return res;
}



void CmdExecution::loadStaticMods()
{
  clglitch::loadStaticMods(cmdData.modSys);
}



void CmdExecution::loadDynamicMods()
{
  if (!params.jsonModFilename.empty()) {
    clglitch::loadDynamicMods(
      cmdData.modSys, params.jsonModFilename.c_str());
  }
}



void CmdExecution::loadCmd()
{
  cmdData.cmd = json_util::loadJsonFile(params.jsonInstanceFilename);
}



void CmdExecution::loadCmdEnv()
{
  // TODO: Test .generic_string() does not end in /
  std::filesystem::path cmdFilePath {params.jsonInstanceFilename};
  std::string cmdPath {cmdFilePath.parent_path().generic_string()};

  auto inlineEnv = getInlineEnv();

  if (params.globalEnvironmentFilename.empty()) {
    cmdData.cmdEnv = loadModEnvironmentDefaultGlobal(
      std::move(cmdPath),
      std::move(inlineEnv));
  }
  else {
    cmdData.cmdEnv = loadModEnvironment(
      params.globalEnvironmentFilename,
      std::move(cmdPath),
      std::move(inlineEnv));
  }
}



void CmdExecution::loadSystemEnv()
{
  cmdData.systemEnv = SystemEnvironment {
    params.jsonInstanceFilename
  };
}



void CmdExecution::execute() const
{
  executeCmd(
    cmdData.modSys,
    cmdData.cmdEnv,
    cmdData.systemEnv,
    params.jsonInstanceFilename,
    cmdData.cmd);
}



CmdData const & CmdExecution::getCmdData() const
{
  return cmdData;
}



JsonObjType CmdExecution::getInlineEnv()
{
  auto it = cmdData.cmd.FindMember("env");
  if (it != cmdData.cmd.MemberEnd()) {
    return JsonObjType(std::move(it->value));
  }
  else {
    return JsonObjType(rapidjson::kObjectType);
  }
}



}