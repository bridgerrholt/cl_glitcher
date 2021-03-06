//
// Created by bridg on 2/15/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_FRACTAL_HIST_FRACTAL_HIST_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_FRACTAL_HIST_FRACTAL_HIST_H

#include <rapidjson/document.h>

#include <mod_sys/static_mod_data.h>

namespace clglitch::fractal_hist
{


void jsonObjExecute(
  JsonObjType const & json,
  char const * directory);

constexpr StaticModData getModData()
{
  return {jsonObjExecute};
}



}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_FRACTAL_HIST_FRACTAL_HIST_H
