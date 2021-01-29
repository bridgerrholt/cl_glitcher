//
// Created by bridg on 1/19/2021.
//

#ifndef CL_GLITCHER_INCLUDE_JSON_UTIL_LOAD_JSON_FILE_H
#define CL_GLITCHER_INCLUDE_JSON_UTIL_LOAD_JSON_FILE_H

#include <string>

#include <FastNoise.h>
#include <rapidjson/document.h>

#include "../noise_mode.h"

namespace json_util
{

rapidjson::Document loadJsonFile(std::string const & filename);

}




#endif //CL_GLITCHER_INCLUDE_JSON_UTIL_LOAD_JSON_FILE_H
