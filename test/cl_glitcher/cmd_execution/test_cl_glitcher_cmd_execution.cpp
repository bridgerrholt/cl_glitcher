#include <cmd_execution/cmd_execution.h>

#include <gtest/gtest.h>

using namespace clglitch;

std::string const directory {CL_GLITCHER_TEST_DIRECTORY_CMD_EXECUTION};
std::string const cmd1File {directory + "/cmd1/cmd1.json"};

TEST(TestClGlitcherCmdExecution, DefaultEmpty)
{
  CmdExecution exec {{}};

  CmdData const & execData {exec.getCmdData()};

}


TEST(TestClGlitcherCmdExecution, RunCmd1)
{
  CmdExecutionParams params {
    cmd1File
  };

  CmdExecution exec {params};
}
