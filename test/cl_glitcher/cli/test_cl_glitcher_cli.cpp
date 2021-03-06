#include <cli/cli.h>

#include <gtest/gtest.h>

using namespace clglitch;

TEST(TestClGlitcherCli, RunJson)
{
  char const * strArr[] {"cl_glitch", "--run-json", "filename.json"};
  auto [res, code] = cli(3, strArr);

  CliResult resExpected;
  resExpected.jsonInstanceFilename = "filename.json";

  ASSERT_EQ(res, resExpected);
  ASSERT_EQ(0, code);
}



TEST(TestClGlitcherCli, J)
{
  char const * strArr[] {"cl_glitch", "-J", "filename.json"};
  auto [res, code] = cli(3, strArr);

  CliResult resExpected;
  resExpected.jsonInstanceFilename = "filename.json";

  ASSERT_EQ(res, resExpected);
  ASSERT_EQ(0, code);
}



TEST(TestClGlitcherCli, ModFile)
{
  char const * strArr[] {"cl_glitch", "--mod-file", "filename.json"};
  auto [res, code] = cli(3, strArr);

  CliResult resExpected;
  resExpected.jsonModFilename = "filename.json";

  ASSERT_EQ(res, resExpected);
  ASSERT_EQ(0, code);
}



TEST(TestClGlitcherCli, M)
{
  char const * strArr[] {"cl_glitch", "-M", "filename.json"};
  auto [res, code] = cli(3, strArr);

  CliResult resExpected;
  resExpected.jsonModFilename = "filename.json";

  ASSERT_EQ(res, resExpected);
  ASSERT_EQ(0, code);
}