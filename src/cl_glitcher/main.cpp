#include <iostream>

#include <cli/cli.h>
#include <cmd_execution/cmd_execution.h>

int main(int argc, char * argv[])
{
  using namespace clglitch;

  // TODO: Remove const_cast
  auto [res, code] = cli(argc, const_cast<char const **>(argv));

  if (code == 0)
  {
    CmdExecution::loadAndExecute(res);
  }

  return code;
}
