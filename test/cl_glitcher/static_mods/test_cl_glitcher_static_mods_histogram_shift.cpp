#include <json_util/property.h>
#include <static_mods/histogram_shift/histogram_shift.h>
#include <gtest/gtest.h>

using namespace json_util;
using namespace rapidjson;
using namespace clglitch::histogram_shift;


TEST(TestHistogramShift, HistogramShiftDataSingleNumber)
{
  const char* json = R"({
    "incMin": 10,
    "incMax": 20,
    "incFactor": 10.0
  })";

  Document d;
  d.Parse(json);

  HistogramShiftData o;
  deserialize(d, o);

  HistogramShiftData expected {
    {{10, 1}},
    {{20, 1}},
    10.0f
  };

  ASSERT_EQ(o, expected);
}


TEST(TestHistogramShift, HistogramShiftDataSingleNumberInArr)
{
  const char* json = R"({
    "incMin": [10],
    "incMax": [20],
    "incFactor": 10.0
  })";

  Document d;
  d.Parse(json);

  HistogramShiftData o;
  deserialize(d, o);

  HistogramShiftData expected {
    {{10, 1}},
    {{20, 1}},
    10.0f
  };

  ASSERT_EQ(o, expected);
}


TEST(TestHistogramShift, HistogramShiftDataMultipleNumbers)
{
  const char* json = R"({
    "incMin": [10, 30, 50],
    "incMax": [20, 40, 60],
    "incFactor": 10.0
  })";

  Document d;
  d.Parse(json);

  HistogramShiftData o;
  deserialize(d, o);

  HistogramShiftData expected {
    {{10, 1}, {30, 1}, {50, 1}},
    {{20, 1}, {40, 1}, {60, 1}},
    10.0f
  };

  ASSERT_EQ(o, expected);
}


TEST(TestHistogramShift, HistogramShiftDataMultipleNumbersWithTimes)
{
  const char* json = R"({
    "incMin": [[10, 1], [30, 2], [50, 3]],
    "incMax": [[20, 4], [40, 5], [60, 6]],
    "incFactor": 10.0
  })";

  Document d;
  d.Parse(json);

  HistogramShiftData o;
  deserialize(d, o);

  HistogramShiftData expected {
    {{10, 1}, {30, 2}, {50, 3}},
    {{20, 4}, {40, 5}, {60, 6}},
    10.0f
  };

  ASSERT_EQ(o, expected);
}

