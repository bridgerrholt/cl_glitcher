//
// Created by bridg on 2/15/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_HISTOGRAM_SHIFT_HISTOGRAM_SHIFT_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_HISTOGRAM_SHIFT_HISTOGRAM_SHIFT_H

#include <rapidjson/document.h>

#include <json_defs/line_series.h>
#include <json_util/property.h>
#include <mod_sys/static_mod_data.h>

namespace clglitch::histogram_shift
{

class IncMinIncMaxPair
{
  public:
    LineSeries<unsigned> incMin;
    LineSeries<unsigned> incMax;
};



class HistogramShiftData
{
  private:
    static void deserializeLine(
      HistogramShiftData & owner,
      LineSeries<unsigned> & line,
      rapidjson::Value const & value);


  public:
    LineSeries<unsigned> incMin;
    LineSeries<unsigned> incMax;
    LineSeries<float> incFactor;

    JSON_UTIL_DECLARE_PROP_LIST(
      JSON_UTIL_MAKE_PROP(HistogramShiftData, incFactor),
      JSON_UTIL_MAKE_CUSTOM_PROP(HistogramShiftData, incMin, deserializeLine),
      JSON_UTIL_MAKE_CUSTOM_PROP(HistogramShiftData, incMax, deserializeLine)
    );

		HistogramShiftData() = default;

		HistogramShiftData(
			LineSeries<unsigned> incMin,
			LineSeries<unsigned> incMax,
			LineSeries<float> incFactor) :
			incMin {std::move(incMin)},
			incMax {std::move(incMax)},
			incFactor {std::move(incFactor)} {}

    bool operator==(HistogramShiftData const & other) const
    {
      return
        incMin == other.incMin &&
        incMax == other.incMax &&
        incFactor == other.incFactor;
    }

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

  private:
    bool channelsDefined {false};
};



void jsonObjExecute(JsonObjExecuteParams const & params);



constexpr StaticModData getModData()
{
  return StaticModData {jsonObjExecute};
}



}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_HISTOGRAM_SHIFT_HISTOGRAM_SHIFT_H
