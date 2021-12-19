//
// Created by bridg on 8/8/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_MANDELBROT_SHIFT_MANDELBROT_SHIFT_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_MANDELBROT_SHIFT_MANDELBROT_SHIFT_H

#include <rapidjson/document.h>

#include <json_defs/line_series.h>
#include <json_util/property.h>
#include <mod_sys/static_mod_data.h>

namespace clglitch::mandelbrot_shift
{

class MandelbrotShiftData
{
  private:

  public:
    LineSeries<float> incFactor;

    JSON_UTIL_DECLARE_PROP_LIST(
      JSON_UTIL_MAKE_PROP(MandelbrotShiftData, incFactor)
    )

		MandelbrotShiftData() = default;
		explicit MandelbrotShiftData(LineSeries<float> incFactor) :
			incFactor {std::move(incFactor)} {}

    bool operator==(MandelbrotShiftData const & other) const
    {
      return incFactor == other.incFactor;
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



#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_MANDELBROT_MANDELBROT_H
