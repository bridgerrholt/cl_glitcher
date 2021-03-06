//
// Created by bridg on 1/27/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_DYNAMIC_MOD_DATA_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_DYNAMIC_MOD_DATA_H

#include <string>
#include <functional>

#include <rapidjson/document.h>

#include "mod_defs.h"
#include "mod_data_interface.h"

namespace clglitch
{


/// json: The JSON contents of the config file.
/// directory: The directory the config file is located in.
using StringExecuteFuncType =
  void(
    char const * json,
    char const * directory);


class DynamicModData
{
  public:
    DynamicModData() :
      jsonObjExecute {nullptr},
      stringExecute {nullptr} {}

    JsonObjExecuteFuncType* jsonObjExecute;
    StringExecuteFuncType* stringExecute;
};

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_DYNAMIC_MOD_DATA_H
