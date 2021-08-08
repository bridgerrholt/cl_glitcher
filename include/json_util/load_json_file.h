//
// Created by bridg on 1/19/2021.
//

#ifndef CL_GLITCHER_INCLUDE_JSON_UTIL_LOAD_JSON_FILE_H
#define CL_GLITCHER_INCLUDE_JSON_UTIL_LOAD_JSON_FILE_H

#include <string>

#include <rapidjson/document.h>

#include <file_read_stream.h>

namespace json_util
{

struct DocumentStreamPair
{
  rapidjson::Document document;
  FileReadStream stream;
};

rapidjson::Document loadJsonFile(std::string const & filename);

}




#endif //CL_GLITCHER_INCLUDE_JSON_UTIL_LOAD_JSON_FILE_H
