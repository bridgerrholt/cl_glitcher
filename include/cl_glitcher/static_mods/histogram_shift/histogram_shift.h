//
// Created by bridg on 2/15/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_HISTOGRAM_SHIFT_HISTOGRAM_SHIFT_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_HISTOGRAM_SHIFT_HISTOGRAM_SHIFT_H

#include <rapidjson/document.h>

#include <json_util/property.h>
#include <mod_sys/static_mod_data.h>

namespace clglitch::histogram_shift
{

class HistogramShiftData
{
  public:
    unsigned incMin;
    unsigned incMax;
    float incFactor;

    static constexpr auto jsonProps = propList(
      JSON_UTIL_MAKE_PROP(HistogramShiftData, incMin),
      JSON_UTIL_MAKE_PROP(HistogramShiftData, incMax),
      JSON_UTIL_MAKE_PROP(HistogramShiftData, incFactor)
    );

    /*unsigned int imageCount;
    float strength;
    std::vector<unsigned char> histRangeLow;
    std::vector<unsigned char> histRangeHigh;

    static constexpr auto jsonProps = propList(
      JSON_UTIL_MAKE_PROP(HistogramShiftData, imageCount),
      JSON_UTIL_MAKE_PROP(HistogramShiftData, strength),
      JSON_UTIL_MAKE_PROP(HistogramShiftData, histRangeLow),
      JSON_UTIL_MAKE_PROP(HistogramShiftData, histRangeHigh)
    );*/
};



void jsonObjExecute(JsonObjExecuteParams const & params);



constexpr StaticModData getModData()
{
  return StaticModData {jsonObjExecute};
}



}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_HISTOGRAM_SHIFT_HISTOGRAM_SHIFT_H
