//
// Created by bridg on 8/12/2021.
//

#ifndef CL_GLITCHER_INCLUDE_JSON_UTIL_JSON_TO_STRING_H
#define CL_GLITCHER_INCLUDE_JSON_UTIL_JSON_TO_STRING_H

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


namespace json_util
{

template <class T>
std::string jsonToString(T const & json)
{
  using namespace rapidjson;
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  json.Accept(writer);
  return buffer.GetString();
}

}

#endif //CL_GLITCHER_INCLUDE_JSON_UTIL_JSON_TO_STRING_H
