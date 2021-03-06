//
// Created by bridg on 1/27/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_LOAD_DYNAMIC_MODS_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_LOAD_DYNAMIC_MODS_H

#include <vector>
#include <unordered_map>

#include "mod_sys.h"

namespace clglitch
{

/// Loads mods from a mod config file.
/// Config file consists of one parameter per line. Empty lines are ignored.
/// White space is trimmed from font and end of lines.
/// A single mod is represented by three lines:
///   Library dir:       The directory the shared library (.dll, .so, .dylib,
///                      etc.) is contained in.
///   Library name:      The name of the library. This is NOT the file name.
///                      For example, if you have a library file `libtest.so`,
///                      only put `test` (without tick marks).
///   ModData func name: The name of the global-scope function within the
///                      library which returns a ModData object for that mod.
///                      Must be of the signature ModData().
/// \param configFileName The location of the file containing the mod config
///                       data.
/// \return A list of ModData objects, one for each mod.
/// \throws std::exception when the file can't be loaded, a library can't be
///         loaded, a library's ModData func can't be loaded and executed,
///         or the file doesn't contain sets of 3 lines.
void loadDynamicMods(
  ModSys & modSys,
  char const * configFileName);

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_LOAD_DYNAMIC_MODS_H
