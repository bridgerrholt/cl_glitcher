#include <mod_environment/load_mod_environment.h>

#include <gtest/gtest.h>

using namespace clglitch;

namespace {

class DirectorySystem
{
  public:
    std::string executeDirectory;
    std::string globalEnvFile;
};

std::string const directory {CL_GLITCHER_TEST_DIRECTORY_MOD_ENVIRONMENT};

std::string const test0Directory {directory + "/mod_environment_0"};
std::string const test0Glitch0Directory {test0Directory + "/glitch_0"};
std::string const test0GlobalEnvFile {test0Directory + "/test_mod_env_global_0.json"};

}

TEST(TestClGlitcherModSys, DefaultModEnvironment)
{
  CmdEnvironment env {};

  ASSERT_STREQ(env.getVar("envDirRelativeToInput")->GetString(), ".");
  ASSERT_STREQ(env.getVar("envFilename")->GetString(), "env.json");

  ASSERT_STREQ(env.getGlobalVar("envDirRelativeToInput")->GetString(), ".");
  ASSERT_STREQ(env.getGlobalVar("envFilename")->GetString(), "env.json");

  ASSERT_EQ(env.getLocalVar("envDirRelativeToInput"), nullptr);
  ASSERT_EQ(env.getLocalVar("envFilename"), nullptr);
};


TEST(TestClGlitcherModSys, ModEnvironment0)
{
  JsonObjType inlineEnv {rapidjson::kObjectType};
  auto env = loadModEnvironmentDefaultGlobal(test0Glitch0Directory, std::move(inlineEnv));

  ASSERT_STREQ(env.getVar("inputFilename")->GetString(), "glitch_0.png");
  ASSERT_STREQ(env.getLocalVar("inputFilename")->GetString(), "glitch_0.png");
  ASSERT_EQ(env.getGlobalVar("inputFilename"), nullptr);
}


/*TEST(TestClGlitcherModSys, LoadModEnvironment)
{
  auto env = loadModEnvironment(test0GlobalEnvFile, test0Directory);
}*/
