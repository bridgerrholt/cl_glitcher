//
// Created by bridg on 1/18/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_CLI_CLI_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_CLI_CLI_H

#include <tuple>
#include <string>

namespace clgitch
{

class CliResult
{
  public:
    std::string filename;

    bool operator==(CliResult const & other) const;
};

std::pair<CliResult, int> cli(int argc, char const * argv[]);

}
#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_CLI_CLI_H
