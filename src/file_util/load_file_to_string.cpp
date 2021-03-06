//
// Created by bridg on 3/5/2021.
//

#include <file_util/load_file_to_string.h>

#include <fstream>
#include <sstream>

namespace file_util {

std::string loadFileToString(std::string const & filename)
{
  std::ifstream t(filename);
  std::stringstream buffer;

  buffer << t.rdbuf();

  return buffer.str();
}

}