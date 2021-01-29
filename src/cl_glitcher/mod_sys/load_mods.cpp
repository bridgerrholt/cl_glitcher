#include <mod_sys/load_mods.h>

#include <fstream>
#include <string>
#include <algorithm>

#include <dynalo/dynalo.hpp>

namespace
{

// trim from start (in place)
std::string & ltrim(std::string & s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
    return !std::isspace(ch);
  }));
  return s;
}

// trim from end (in place)
std::string & rtrim(std::string & s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
    return !std::isspace(ch);
  }).base(), s.end());
  return s;
}

}

namespace clglitch
{

std::vector<ModData> loadMods(char const * configFileName)
{
  std::ifstream file {configFileName};

  std::string line;
  enum LineType { LIB_DIR, LIB_NAME, MOD_DATA_FUNC_NAME };
  LineType lineType {LIB_DIR};

  std::string libDir;
  std::string libName;
  std::string modDataFuncName;

  std::vector<ModData> modDataList;

  while (std::getline(file, line))
  {
    ltrim(rtrim(line));
    if (!line.empty())
    {
      switch (lineType)
      {
        case LIB_DIR:
          libDir = std::move(line);
          if (libDir.back() != '/' && libDir.back() != '\\')
            libDir.push_back('/');

          lineType = LIB_NAME;
          break;

        case LIB_NAME:
          libName = dynalo::to_native_name(line);

          lineType = MOD_DATA_FUNC_NAME;
          break;

        case MOD_DATA_FUNC_NAME:
          modDataFuncName = std::move(line);

          std::string libFileName = libDir + libName;

          dynalo::library lib {libFileName};
          
          auto getModData = lib.get_function<GetModDataFuncType>(modDataFuncName);

          modDataList.push_back(getModData());

          lineType = LIB_DIR;
          break;
      }
    }
  }

  if (lineType != LIB_DIR)
  {
    std::string error {"Mod config file \""};
    error += configFileName;
    error += "\" ends prematurely.";
    throw std::runtime_error(error);
  }

  return modDataList;
}

}
