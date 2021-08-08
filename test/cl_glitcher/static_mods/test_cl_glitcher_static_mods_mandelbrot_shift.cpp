#include <json_util/property.h>
#include <static_mods/mandelbrot_shift/mandelbrot_shift.h>
#include <gtest/gtest.h>

using namespace json_util;
using namespace rapidjson;
using namespace clglitch::mandelbrot_shift;


TEST(TestMandelbrotShift, MandelbrotShiftDataSingleNumber)
{
  const char* json = R"({
    "incFactor": 10.0
  })";

  Document d;
  d.Parse(json);

  MandelbrotShiftData o;
  deserialize(d, o);

  MandelbrotShiftData expected {
    10.0f
  };

  ASSERT_EQ(o, expected);
}

