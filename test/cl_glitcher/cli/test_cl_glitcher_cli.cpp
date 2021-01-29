#include <cli/cli.h>

#include <gtest/gtest.h>

using namespace clgitch;

TEST(TestClGlitcherCli, RunJson)
{
  char const * strArr[] {"cl_glitch", "--run-json", "filename.json"};
  auto [res, code] = cli(3, strArr);

  CliResult resExpected;
  resExpected.filename = "filename.json";

  ASSERT_EQ(res, resExpected);
  ASSERT_EQ(0, code);
}



TEST(TestClGlitcherCli, J)
{
  char const * strArr[] {"cl_glitch", "-J", "filename.json"};
  auto [res, code] = cli(3, strArr);

  CliResult resExpected;
  resExpected.filename = "filename.json";

  ASSERT_EQ(res, resExpected);
  ASSERT_EQ(0, code);
}