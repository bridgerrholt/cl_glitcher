#include <mod_sys/load_dynamic_mods.h>

#include <fstream>
#include <string>
#include <algorithm>

#include <dynalo/dynalo.hpp>
#include <load_json_file.h>
#include <property.h>

namespace
{

/// Json object for
class ModDataLoader
{
  public:
    /// The directory containing the library file.
    /// If libPath is defined, libDir must not be, otherwise libDir must be.
    std::string libDir;

    /// The generic name (i.e. without .dll, .so, etc.) of the library.
    /// Only used if libPath is specified, and must be specified if so.
    std::string libName;

    /// The full path to the library file.
    /// If libDir is defined, libPath must not be, otherwise libPath must be.
    std::string libPath;

    /// A custom name applied to the mod. If not specified, libName is used.
    /// Must be specified if libDir is specified.
    std::string modName;

    /// The name of the function which takes rapidjson::Document::ValueType const &.
    /// jsonObjExecuteFuncName or (exclusive) stringExecuteFuncName must be defined.
    std::string jsonObjExecuteFuncName;

    /// The name of the function which takes char const *.
    /// jsonObjExecuteFuncName or (exclusive) stringExecuteFuncName must be defined.
    std::string stringExecuteFuncName;

    JSON_UTIL_DECLARE_PROP_LIST(
      JSON_UTIL_MAKE_OPTIONAL_PROP(ModDataLoader, libDir),
      JSON_UTIL_MAKE_OPTIONAL_PROP(ModDataLoader, libName),
      JSON_UTIL_MAKE_OPTIONAL_PROP(ModDataLoader, libPath),
      JSON_UTIL_MAKE_OPTIONAL_PROP(ModDataLoader, modName),
      JSON_UTIL_MAKE_OPTIONAL_PROP(ModDataLoader, jsonObjExecuteFuncName),
      JSON_UTIL_MAKE_OPTIONAL_PROP(ModDataLoader, stringExecuteFuncName)
    );

    void load(clglitch::ModSys & modSys)
    {
      std::string path;

      std::string name {getName()};

      if (!libDir.empty())
      {
        if (!libPath.empty())
          throw libPathDirError();

        if (libDir.back() != '/' && libDir.back() != '\\')
          libDir.push_back('/');

        if (!libName.empty())
          path = libDir + dynalo::to_native_name(libName);
        else
          path = libDir + dynalo::to_native_name(modName);
      }
      else
        path = libPath;

      dynalo::library lib {path};
      clglitch::DynamicModData modData;

      if (!jsonObjExecuteFuncName.empty()) {
        if (!stringExecuteFuncName.empty())
          throw bothExecuteFuncNamesError();

        modData.jsonObjExecute =
          lib.get_function<clglitch::JsonObjExecuteFuncType>(
            jsonObjExecuteFuncName);
      }
      else if (!stringExecuteFuncName.empty()) {
        modData.stringExecute =
          lib.get_function<clglitch::StringExecuteFuncType>(
            stringExecuteFuncName);
      }
      else {
        modData.jsonObjExecute =
          lib.try_get_function<clglitch::JsonObjExecuteFuncType>(
            "jsonObjExecute");

        modData.stringExecute =
          lib.try_get_function<clglitch::StringExecuteFuncType>(
            "stringExecute");

        if (
          modData.jsonObjExecute == nullptr &&
          modData.stringExecute == nullptr) {
          throw noFuncsFoundError();
        }
        else if (
          modData.jsonObjExecute != nullptr &&
          modData.stringExecute != nullptr) {
          throw bothFuncsFoundError();
        }
      }


      modSys.addDynamicMod(std::move(name), modData, std::move(lib));
    }

  private:
    static std::string const jsonObjExecuteDefaultName;
    static std::string const stringExecuteDefaultName;

    std::string getName() const
    {
      if (!modName.empty())
        return modName;
      else if (!libName.empty())
        return libName;
      else
        throw noLibOrModNameError();
    }

    std::runtime_error libPathDirError() const
    {
      return std::runtime_error(
        "libPath (" + libPath +
        ") and libDir (" + libDir +
        ") must not both be defined.");
    }

    static std::runtime_error noLibOrModNameError()
    {
      return std::runtime_error(
        "libName or modName must be specified.");
    }

    std::runtime_error bothExecuteFuncNamesError() const
    {
      return std::runtime_error {
        "jsonObjExecuteFuncName (" + jsonObjExecuteFuncName +
        ") and stringExecuteFuncName (" + stringExecuteFuncName +
        ") must not both be defined."
      };
    }

    static std::runtime_error noFuncsFoundError()
    {
      return std::runtime_error {
        "No execution functions found. Either define a function named " +
        jsonObjExecuteDefaultName + " or " +
        stringExecuteDefaultName +
        ", or specify in the JSON mod file a field named " +
        "jsonObjExecuteFuncName or stringExecuteFuncName"
      };
    }

    static std::runtime_error bothFuncsFoundError()
    {
      return std::runtime_error {
        "Both execution functions named " +
        jsonObjExecuteDefaultName + " and " +
        stringExecuteDefaultName +
        " found. Either remove one definition or specify in the JSON mod " +
        "file a field named jsonObjExecuteFuncName or stringExecuteFuncName"
      };
    }
};

std::string const ModDataLoader::jsonObjExecuteDefaultName {"jsonObjExecute"};
std::string const ModDataLoader::stringExecuteDefaultName {"jsonObjExecute"};


/*class ModDataLoaderInfoFullName
{
  public:
    std::string fullLibName;
    std::string modDataFuncName {"getModData"};
};*/


// trim from start (in place)
/*std::string & ltrim(std::string & s) {
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
}*/

}

namespace clglitch
{



void loadDynamicMod(ModSys & modSys, rapidjson::Document::ValueType const & json)
{
  std::string fullFileName;

  ModDataLoader loader;
  json_util::deserialize(json, loader);

  loader.load(modSys);
}



void loadDynamicMods(
  ModSys & modSys,
  char const * configFileName)
{
  rapidjson::Document doc {json_util::loadJsonFile(configFileName)};

  if (doc.IsArray()) {
    for (auto const & mod : doc.GetArray()) {
      loadDynamicMod(modSys, mod);
    }
  }
  else {
    loadDynamicMod(modSys, doc);
  }
}


/*std::vector<ModData> loadDynamicMods(char const * configFileName)
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
}*/

}
