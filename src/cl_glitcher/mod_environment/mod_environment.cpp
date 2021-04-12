//
// Created by bridg on 3/11/2021.
//

#include <mod_environment/mod_environment.h>
#include <mod_environment/environment_defaults.h>

namespace clglitch
{


CmdEnvironment::CmdEnvironment() :
  CmdEnvironment(
    JsonDocType{rapidjson::kObjectType},
    JsonDocType{rapidjson::kObjectType},
    JsonObjType{rapidjson::kObjectType})
{

}


CmdEnvironment::CmdEnvironment(
  JsonDocType globalEnv,
  JsonDocType localEnv,
  JsonObjType inlineEnv) :
  globalEnv_{std::move(globalEnv)},
  localEnv_{std::move(localEnv)},
  inlineEnv_{std::move(inlineEnv)}
{
  insertGlobalDefaults(globalEnv_);
}


CmdEnvironment CmdEnvironment::fromLocalAndInline(
  JsonDocType localEnv, JsonObjType inlineEnv)
{
  return {
    JsonDocType{rapidjson::kObjectType},
    std::move(localEnv),
    std::move(inlineEnv)
  };
}


CmdEnvironment defaultLocal(
  JsonDocType globalEnv, JsonObjType inlineEnv)
{
  return {
    std::move(globalEnv),
    JsonDocType{rapidjson::kObjectType},
    std::move(inlineEnv)
  };
}


JsonObjType const * CmdEnvironment::getVar(std::string const & name) const
{
  auto const * inlinePtr = getInlineVar(name);
  if (inlinePtr == nullptr)
  {
    auto const * localPtr = getLocalVar(name);
    if (localPtr == nullptr)
    {
      return getGlobalVar(name);
    }
    else
    {
      return localPtr;
    }
  }
  else
  {
    return inlinePtr;
  }
}


JsonObjType const * CmdEnvironment::getGlobalVar(
  std::string const & name) const
{
  return getVar(globalEnv_, name);
}


JsonObjType const * CmdEnvironment::getLocalVar(
  std::string const & name) const
{
  return getVar(localEnv_, name);
}


JsonObjType const * CmdEnvironment::getInlineVar(
  std::string const & name) const
{
  return getVar(inlineEnv_, name);
}


JsonObjType const * CmdEnvironment::getVar(
  JsonObjType const & env,
  std::string const & name)
{
  auto it = env.FindMember(name.c_str());
  if (it != env.MemberEnd())
  {
    return &it->value;
  }

  return nullptr;
}



void CmdEnvironment::setLocalEnv(JsonDocType globalEnv)
{
  globalEnv_ = std::move(globalEnv);
}



bool CmdEnvironment::operator==(CmdEnvironment const & other) const
{
  return globalEnv_ == other.globalEnv_ && localEnv_ == other.localEnv_;
}



void CmdEnvironment::insertDefault(
  JsonDocType & env, JsonObjType && name, JsonObjType && value)
{
  auto it = env.FindMember(name);
  if (it == env.MemberEnd()) {
    env.AddMember(name, value, env.GetAllocator());
  }
}



void CmdEnvironment::insertGlobalDefaults(JsonDocType & globalEnv)
{
  using namespace defaults;

  insertDefault(
    globalEnv,
    JsonObjType {"searchForLocalVar"},
    JsonObjType {searchForLocalVar});
  insertDefault(
    globalEnv,
    JsonObjType {"envDirRelativeToInput"},
    JsonObjType {envDirRelativeToInput});
  insertDefault(
    globalEnv,
    JsonObjType {"envFilename"},
    JsonObjType {envFilename});
}



JsonDocType CmdEnvironment::defaultGlobalEnv()
{
  JsonDocType globalEnv;
  insertGlobalDefaults(globalEnv);
  return globalEnv;
}



}
