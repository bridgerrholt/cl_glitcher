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

class ValueTimePair
{
  public:
    unsigned value;
    float time;

    static constexpr auto jsonProps = std::make_tuple(
      JSON_UTIL_MAKE_PROP(ValueTimePair, value),
      JSON_UTIL_MAKE_PROP(ValueTimePair, time)
    );

    constexpr ValueTimePair(unsigned num, float time) :
      value {num}, time {time} {}

    constexpr bool operator==(ValueTimePair const & other) const
    {
      return value == other.value && time == other.time;
    }
};



class LineSegment
{
  private:
    static void deserializeFrames(
      LineSegment & owner,
      std::vector<ValueTimePair> & frames,
      rapidjson::Value const & value);

    static void deserializeFramesFromValueArr(
      std::vector<ValueTimePair> & frames,
      rapidjson::Value::ConstArray::ValueIterator arrayBegin,
      rapidjson::SizeType arraySize);

    static void deserializeFramesFromFrameArr(
      std::vector<ValueTimePair> & frames,
      rapidjson::Value::ConstArray const & jsonArray);

    void deserializeFromValueArr(
      rapidjson::Value::ConstArray const & jsonArray);

  public:
    unsigned initial;
    std::vector<ValueTimePair> frames;

    static constexpr auto jsonProps = std::make_tuple(
      JSON_UTIL_MAKE_PROP(LineSegment, initial),
      JSON_UTIL_MAKE_CUSTOM_PROP(LineSegment, frames, deserializeFrames)
    );

    constexpr bool operator==(LineSegment const & other) const
    {
      return initial == other.initial && frames == other.frames;
    }

    /// Serialize from multiple possible JSON types ("formats" of the object).
    static LineSegment multiFormatDeserialize(rapidjson::Value const & value);

    /*static LineSegment deserializeFromValueArr(
      rapidjson::Value::ConstArray const & jsonArray);*/
};



class IncMinIncMaxPair
{
  public:
    LineSegment incMin;
    LineSegment incMax;
};



class HistogramShiftData
{
  private:
    static void deserializeLine(
      HistogramShiftData & owner,
      LineSegment & line,
      rapidjson::Value const & value);


  public:
    LineSegment incMin;
    LineSegment incMax;
    float incFactor;

    static constexpr auto jsonProps = std::make_tuple(
      JSON_UTIL_MAKE_PROP(HistogramShiftData, incFactor),
      JSON_UTIL_MAKE_CUSTOM_PROP(HistogramShiftData, incMin, deserializeLine),
      JSON_UTIL_MAKE_CUSTOM_PROP(HistogramShiftData, incMax, deserializeLine)
    );

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
    bool channelsDefined {0};
};



void jsonObjExecute(JsonObjExecuteParams const & params);



constexpr StaticModData getModData()
{
  return StaticModData {jsonObjExecute};
}



}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_STATIC_MODS_HISTOGRAM_SHIFT_HISTOGRAM_SHIFT_H
