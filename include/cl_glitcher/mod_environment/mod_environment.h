//
// Created by bridg on 3/6/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_ENVIRONMENT_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_ENVIRONMENT_H

#include <string>

#include <json_defs/json_obj_type.h>

namespace clglitch {

///
class CmdEnvironment
{
  public:
    CmdEnvironment();

    CmdEnvironment(
      JsonDocType globalEnv,
      JsonDocType localEnv,
      JsonObjType inlineEnv);

    static CmdEnvironment fromLocalAndInline(
      JsonDocType localEnv, JsonObjType inlineEnv);

    static CmdEnvironment defaultLocal(
      JsonDocType globalEnv, JsonObjType inlineEnv);

    static CmdEnvironment fromInline(JsonObjType inlineEnv);

    /// Get the JSON field `name`.
    /// If it exists in the local env, return that.
    /// If it exists in the global env, return that.
    /// Otherwise, return null.
    JsonObjType const * getVar(std::string const & name) const;

    JsonObjType const * getGlobalVar(std::string const & name) const;
    JsonObjType const * getLocalVar(std::string const & name) const;
    JsonObjType const * getInlineVar(std::string const & name) const;

    void setLocalEnv(JsonDocType globalEnv);

    bool operator==(CmdEnvironment const & other) const;


  private:
    JsonDocType globalEnv_;
    JsonDocType localEnv_;
    JsonObjType inlineEnv_;

    static JsonObjType const * getVar(
      JsonObjType const & env,
      std::string const & name);

    static void insertDefault(
      JsonDocType & env, JsonObjType && name, JsonObjType && value);
    static void insertGlobalDefaults(JsonDocType & globalEnv);

    static JsonDocType defaultGlobalEnv();
};


}


#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_ENVIRONMENT_H
