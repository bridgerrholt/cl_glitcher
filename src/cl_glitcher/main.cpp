#include <iostream>

#include <cli/cli.h>
#include <mod_sys/mod_sys.h>
#include <mod_sys/load_dynamic_mods.h>
#include <mod_sys/load_static_mods.h>

namespace {

using namespace clglitch;

ModSys loadMods(std::string const & dynamicModFilename)
{
  ModSys modSys;

  loadStaticMods(modSys);

  if (!dynamicModFilename.empty())
    loadDynamicMods(modSys, dynamicModFilename.c_str());

  return modSys;
}

}



int main(int argc, char * argv[])
{
  using namespace clglitch;

  auto [res, code] = cli(argc, const_cast<char const **>(argv));

  if (code == 0)
  {
    ModSys modSys {::loadMods(res.jsonModFilename)};

  }

  return code;
}
