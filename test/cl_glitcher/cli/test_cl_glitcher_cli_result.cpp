#include <cli/cli.h>

#include <gtest/gtest.h>

using namespace clglitch;

TEST(TestClGlitcherCliResult, RunCmd1)
{
  char const * strArr[] {"cl_glitch", "--cmd", "filename.json"};
  auto [res, code] = cli(3, strArr);

  CmdExecutionParams resExpected;
  resExpected.jsonInstanceFilename = "filename.json";

  ASSERT_EQ(res, resExpected);
  ASSERT_EQ(0, code);
}
