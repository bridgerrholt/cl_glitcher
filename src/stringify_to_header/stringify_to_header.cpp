//
// Created by bridg on 3/5/2021.
//

#include <stringify_to_header.h>

#include <file_util/load_file_to_string.h>

void stringifyToHeader(
  std::string const & varNamespace, std::string const & varName,
  std::string const & inputFilename, std::string const & outputFilename)
{
  std::ifstream inputFile {inputFilename};
  std::ofstream outputFile {outputFilename};
  stringifyToHeaderStreamed(varNamespace, varName, inputFile, outputFile);
}