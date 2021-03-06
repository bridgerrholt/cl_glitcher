//
// Created by bridg on 2/12/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_DEFS_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_DEFS_H

#include <rapidjson/document.h>

namespace clglitch {

using JsonObjType = rapidjson::Document::ValueType;

/// json: JSON-parsed contents of the config file.
/// directory: Directory the config file is located in.
using JsonObjExecuteFuncType =
  void(
    JsonObjType const & json,
    char const * directory);

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_DEFS_H
