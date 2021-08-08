//
// Created by bridg on 3/5/2021.
//

#include <mod_sys/load_static_mods.h>

#include <static_mods/histogram_shift/histogram_shift.h>
#include <static_mods/mandelbrot_shift/mandelbrot_shift.h>

namespace clglitch {

void loadStaticMods(ModSys & modSys)
{
  modSys.addStaticMod("Histogram Shift", histogram_shift::getModData());
  modSys.addStaticMod("Mandelbrot Shift", mandelbrot_shift::getModData());
}

}
