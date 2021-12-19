//
// Created by bridg on 8/8/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_MANDELBROT_MANDELBROT_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_MANDELBROT_MANDELBROT_H

#include <rapidjson/document.h>

#include <json_defs/line_series.h>
#include <json_util/property.h>
#include <mod_sys/static_mod_data.h>

namespace clglitch::mandelbrot
{

class MandelbrotData
{
  private:

  public:
    LineSeries<float> steps;
    LineSeries<float> n;
    LineSeries<float> radius;
    LineSeries<float> sphereOffsetX {0};
    LineSeries<float> sphereOffsetY {0};
    LineSeries<float> sphereOffsetZ {0};
    bool imageFeedback {true};

    JSON_UTIL_DECLARE_PROP_LIST(
      JSON_UTIL_MAKE_PROP(MandelbrotData, steps),
      JSON_UTIL_MAKE_PROP(MandelbrotData, n),
      JSON_UTIL_MAKE_PROP(MandelbrotData, radius),
      JSON_UTIL_MAKE_OPTIONAL_PROP(MandelbrotData, sphereOffsetX),
      JSON_UTIL_MAKE_OPTIONAL_PROP(MandelbrotData, sphereOffsetY),
      JSON_UTIL_MAKE_OPTIONAL_PROP(MandelbrotData, sphereOffsetZ),
      JSON_UTIL_MAKE_OPTIONAL_PROP(MandelbrotData, imageFeedback)
    );

    bool operator==(MandelbrotData const & other) const
    {
      return steps == other.steps && n == other.n && radius == other.radius;
    }

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
