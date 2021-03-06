//
// Created by bridg on 3/5/2021.
//

#ifndef CL_GLITCHER_INCLUDE_STRINGIFY_TO_HEADER_STRINGIFY_TO_HEADER_H
#define CL_GLITCHER_INCLUDE_STRINGIFY_TO_HEADER_STRINGIFY_TO_HEADER_H

#include <string>
#include <fstream>

template <class IStream, class OStream>
void stringifyToHeaderStreamed(
  std::string const & varNamespace, std::string const & varName,
  IStream & iStream, OStream & oStream)
{
  oStream << "namespace " << varNamespace << "{\n";
  oStream << "std::string const " << varName << " {\n";

  std::string line;
  while (std::getline(iStream, line))
  {
    std::string oLine {'"'};
    for (auto c : line)
    {
      if (c == '\\')
        oLine += "\\\\";
      else if (c == '"')
        oLine += "\\\"";
      else
        oLine += c;
    }
    oLine += "\\n\"\n";
    oStream.write(oLine.c_str(), oLine.size());
  }

  oStream << "};\n}\n";
}



void stringifyToHeader(
  std::string const & varNamespace, std::string const & varName,
  std::string const & inputFilename, std::string const & outputFilename);

#endif //CL_GLITCHER_INCLUDE_STRINGIFY_TO_HEADER_STRINGIFY_TO_HEADER_H
