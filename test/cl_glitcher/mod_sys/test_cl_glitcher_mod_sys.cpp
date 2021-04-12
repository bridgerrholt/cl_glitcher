#include <mod_sys/load_dynamic_mods.h>

#include <gtest/gtest.h>

using namespace clglitch;

namespace {

constexpr char const * directory {CL_GLITCHER_TEST_DIRECTORY_MOD_SYS};
std::string const modFile {std::string{directory} + "/test_dynamic_mod_0.json"};

}

TEST(TestClGlitcherModSys, LoadDynamicMod)
{
  ModSys modMap;
  loadDynamicMods(modMap, modFile.c_str());

  ASSERT_TRUE(
    modMap.getDynamicMod(
      "test_cl_glitcher_mod_sys_dynamic_mod_lib_1"
      ) != nullptr);
}