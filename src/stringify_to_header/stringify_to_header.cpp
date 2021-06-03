//
// Created by bridg on 3/5/2021.
//

#include <filesystem>

#include <stringify_to_header.h>

#include <file_util/load_file_to_string.h>

void stringifyToHeader(
  std::string const & varNamespace, std::string const & varName,
  std::string const & inputFilename, std::string const & outputFilename)
{
  using namespace std::filesystem;

  std::ifstream inputFile {inputFilename};

  create_directory(path{outputFilename}.parent_path());
  std::ofstream outputFile {outputFilename};

  stringifyToHeaderStreamed(varNamespace, varName, inputFile, outputFile);
}