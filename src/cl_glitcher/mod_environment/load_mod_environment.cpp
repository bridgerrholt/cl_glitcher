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

void maybeLoadLocalEnv(CmdEnvironment & env)
{
  auto const * searchForLocalVarPtr = env.getVar("searchForLocalVar");
  if (searchForLocalVarPtr != nullptr) {
    auto localEnv = loadJsonFile(localEnvFilename);
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

  std::string & localEnvFilename {commandFileDirectory};
  appendEnvDir(localEnvFilename, globalEnv);
  appendEnvFilename(localEnvFilename, globalEnv);

  auto localEnv = loadJsonFile(localEnvFilename);

  return {std::move(globalEnv), std::move(localEnv), std::move(inlineEnv)};
}



CmdEnvironment loadModEnvironmentDefaultGlobal(
  std::string commandFileDirectory,
  JsonObjType inlineEnv)
{
  using namespace json_util;
  using namespace defaults;

  std::string & localEnvFilename {commandFileDirectory};
  localEnvFilename += "/";
  localEnvFilename += envDirRelativeToInput;
  localEnvFilename += "/";
  localEnvFilename += envFilename;

  // TODO: Exception handling
  auto localEnv = loadJsonFile(localEnvFilename);

  return CmdEnvironment::fromLocalAndInline(
    std::move(localEnv), std::move(inlineEnv));
}

}
