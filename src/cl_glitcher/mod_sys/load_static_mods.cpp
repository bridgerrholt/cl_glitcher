//
// Created by bridg on 3/5/2021.
//

#include <mod_sys/load_static_mods.h>

#include <static_mods/fractal_hist/fractal_hist.h>

namespace clglitch {

void loadStaticMods(ModSys & modSys)
{
  modSys.addStaticMod("Fractal Hist", fractal_hist::getModData());
}

}
