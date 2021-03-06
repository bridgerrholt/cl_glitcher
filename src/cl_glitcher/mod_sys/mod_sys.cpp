//
// Created by bridg on 2/12/2021.
//

#include <mod_sys/mod_sys.h>

namespace clglitch
{

void ModSys::reserveModLibs(std::size_t count)
{
  modLibArray.reserve(count);
}



void ModSys::addStaticMod(
  std::string && name, StaticModData modData)
{
  staticModMap.emplace(name, modData);
}



void ModSys::addDynamicMod(
  std::string && name, DynamicModData modData, dynalo::library && lib)
{
  dynamicModMap.emplace(name, modData);
  modLibArray.emplace_back(std::forward<dynalo::library>(lib));
}

}