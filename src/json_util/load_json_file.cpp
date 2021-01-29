//
// Created by bridg on 1/19/2021.
//

#include <load_json_file.h>

#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>

namespace json_util
{

rapidjson::Document loadJsonFile(std::string const & filename)
{
  using namespace rapidjson;

  FILE * fp = fopen(filename.c_str(), "r"); // non-Windows use "r"

  char readBuffer[65536];
  FileReadStream is(fp, readBuffer, sizeof(readBuffer));

  Document document;
  document.ParseStream(is);

  fclose(fp);

  return document;
}

}
