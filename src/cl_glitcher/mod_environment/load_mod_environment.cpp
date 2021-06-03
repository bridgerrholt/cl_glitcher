//
// Created by bridg on 3/12/2021.
//

#include <mod_environment/load_mod_environment.h>
#include <mod_environment/environment_defaults.h>

#include <load_json_file.h>

namespace clglitch {

namespace {


void appendEnvDir(std::string & str, JsonObjType const & globalEnv)
{
  auto it = globalEnv.FindMember("envDirRelativeToInput");

  if (it != globalEnv.MemberEnd()) {
    str += "/";

    if (it->value.IsString()) {
      str += it->value.GetString();
    }
    else {
      throw std::runtime_error(
        "envDirRelativeToInput in global environment file is not a string");
    }
  }
}



void appendEnvFilename(std::string & str, JsonObjType const & globalEnv)
{
  auto it = globalEnv.FindMember("envFilename");

  if (it != globalEnv.MemberEnd()) {
    str += "/";

    if (it->value.IsString()) {
      str += it->value.GetString();
    }
    else {
      throw std::runtime_error(
        "envFilename in global environment file is not a string");
    }
  }
  else {
    str += "/env.json";
  }
}

void maybeLoadLocalEnv(
  CmdEnvironment & env,
  std::string & commandFileDirectory)
{
  if (env.getVar("searchForLocalEnv")->GetBool()) {
    auto const & envDirRelativeToInput =
      env.getVar("envDirRelativeToInput");

    if (
      envDirRelativeToInput->GetString()[0] == '.' &&
      envDirRelativeToInput->GetStringLength() == 0)
    {
      commandFileDirectory += "/";
      commandFileDirectory += env.getVar("envDirRelativeToInput")->GetString();
    }

    commandFileDirectory += "/";
    commandFileDirectory += env.getVar("envFilename")->GetString();

    auto localEnv = json_util::loadJsonFile(commandFileDirectory);
    env.setLocalEnv(std::move(localEnv));
  }
}

}

CmdEnvironment loadModEnvironment(
  std::string const & globalEnvFilename,
  std::string commandFileDirectory,
  JsonObjType inlineEnv)
{
  using namespace json_util;

  auto globalEnv = loadJsonFile(globalEnvFilename);

  auto env = CmdEnvironment::defaultLocal(
    std::move(globalEnv), std::move(inlineEnv));

  maybeLoadLocalEnv(env, commandFileDirectory);

  return env;
}



CmdEnvironment loadModEnvironmentDefaultGlobal(
  std::string commandFileDirectory,
  JsonObjType inlineEnv)
{
  using namespace json_util;

  auto env = CmdEnvironment::fromInline(
    std::move(inlineEnv));

  maybeLoadLocalEnv(env, commandFileDirectory);

  return env;
}

}
