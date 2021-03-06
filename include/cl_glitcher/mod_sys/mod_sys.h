//
// Created by bridg on 2/12/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_SYS_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_SYS_H

#include <dynalo/dynalo.hpp>

#include "dynamic_mod_data.h"
#include "static_mod_data.h"

namespace clglitch
{

using DynamicModDataMap = std::unordered_map<std::string, DynamicModData>;
using StaticModDataMap = std::unordered_map<std::string, StaticModData>;
using ModLibArray = std::vector<dynalo::library>;

// TODO: Implement testing
class ModSys
{
  public:
    void reserveModLibs(std::size_t count);

    void addStaticMod(
      std::string && name, StaticModData modData);

    void addDynamicMod(
      std::string && name, DynamicModData modData, dynalo::library && lib);

  private:
    DynamicModDataMap dynamicModMap;
    StaticModDataMap staticModMap;
    ModLibArray modLibArray;
};

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_SYS_H
