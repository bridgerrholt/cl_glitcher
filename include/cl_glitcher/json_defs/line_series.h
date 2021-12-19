//
// Created by bridg on 6/7/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_JSON_DEFS_LINE_SERIES_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_JSON_DEFS_LINE_SERIES_H

#include <iostream>
#include <json_util/property.h>

namespace clglitch
{

namespace {

float verifyTime(rapidjson::Value const & value)
{
  return value.GetFloat();
}

}



template <class Value>
class ValueTimePair
{
  public:
    Value value;
    float time;

    JSON_UTIL_DECLARE_PROP_LIST(
      JSON_UTIL_MAKE_PROP(ValueTimePair, value),
      JSON_UTIL_MAKE_PROP(ValueTimePair, time)
    );

    constexpr ValueTimePair(Value num, float time) :
      value {num}, time {time} {}

    constexpr bool operator==(ValueTimePair const & other) const
    {
      return value == other.value && time == other.time;
    }
};



template <class Value>
class LineSeries
{
  private:
    using ValueTimeType = ValueTimePair<Value>;

    static void deserializeFrames(
      LineSeries & owner,
      std::vector<ValueTimeType> & frames,
      rapidjson::Value const & value)
    {
      auto const & arr = value.GetArray();

      if (!arr.Empty()) {
        if (arr[0].IsNumber()) {
          deserializeFramesFromValueArr(frames, arr.begin(), arr.Size());
        }
        else if (arr[0].IsArray()) {
          deserializeFramesFromFrameArr(frames, arr);
        }
        else {
          throw std::runtime_error("Invalid element data type of NumTimeArray");
        }
      }
      else {
        throw std::runtime_error("NumTimeArray must not be empty");
      }
    }



    static void deserializeFramesFromValueArr(
      std::vector<ValueTimeType> & frames,
      rapidjson::Value::ConstArray::ValueIterator arrayBegin,
      rapidjson::SizeType arraySize)
    {
      if (arraySize > 0) {
        frames.reserve(arraySize);
        float t {1.0f / (float)arraySize};
        for (std::size_t i {0}; i < arraySize; i++) {
          auto const & v = arrayBegin[i];
          if (v.Is<Value>()) {
            frames.emplace_back(v.Get<Value>(), t);
          }
          else {
            throw std::runtime_error(
              "All elements of LineSegment frame arrays must be the same type.");
          }
        }
      }
    }



    static void deserializeFramesFromFrameArr(
      std::vector<ValueTimeType> & frames,
      rapidjson::Value::ConstArray const & jsonArray)
    {
      for (auto const & v : jsonArray) {
        if (v.IsArray()) {
          if (v.Size() == 2) {
            frames.emplace_back(verifyValue(v[0]), verifyTime(v[1]));
          }
          else {
            throw std::runtime_error("Elements of frame arrays must have a size of 2.");
          }
        }
        else {
          throw std::runtime_error(
            "All elements of LineSegment frame arrays must be the same type.");
        }
      }
    }



    void deserializeFromValueArr(
      rapidjson::Value::ConstArray const & jsonArray)
    {
      auto s = jsonArray.Size();

      if (s > 0) {
        initial = verifyValue(jsonArray[0]);
        deserializeFramesFromValueArr(frames, jsonArray.begin() + 1, s - 1);
      }
      else {
        throw std::runtime_error(
          "Value array used to initialize LineSegment must not be empty.");
      }
    }



  public:
    Value initial;
    std::vector<ValueTimeType> frames;

    JSON_UTIL_DECLARE_PROP_LIST(
      JSON_UTIL_MAKE_PROP(LineSeries, initial),
      JSON_UTIL_MAKE_CUSTOM_PROP(LineSeries, frames, deserializeFrames)
    );

		LineSeries() = default;

		LineSeries(Value initial, std::vector<ValueTimeType> frames={}) :
			initial {initial},
			frames {std::move(frames)} {}

    constexpr bool operator==(LineSeries const & other) const
    {
      return initial == other.initial && frames == other.frames;
    }



    /// Serialize from multiple possible JSON types ("formats" of the object).
    static LineSeries multiFormatDeserialize(rapidjson::Value const & value)
    {
      if (value.IsNumber()) {
        return {verifyValue(value), {}};
      }
      else if (value.IsArray()) {
        LineSeries line;
        line.deserializeFromValueArr(value.GetArray());
        return line;

        /*auto const & arr = value.GetArray();

        if (!arr.Empty()) {
          if (arr[0].IsNumber()) {
            return deserializeArrayOfNums(arr);
          }
          else if (arr[0].IsArray()) {
            return deserializeArrayOfNumTimes(arr);
          }
          else {
            throw std::runtime_error("Invalid element data type of NumTimeArray");
          }
        }
        else {
          throw std::runtime_error("NumTimeArray must not be empty");
        }*/
      }
      else if (value.IsObject()) {
        return json_util::deserialize<LineSeries>(value);
      }
      else {
        throw std::runtime_error("Invalid data type for NumTimeArray");
      }
    }

    /*static LineSegment deserializeFromValueArr(
      rapidjson::Value::ConstArray const & jsonArray);*/



  private:
    static Value verifyValue(rapidjson::Value const & value)
    {
      std::cout << value.Get<Value>() << '\n';
      return value.Get<Value>();
    }
};

}



// Specializations of json_util::deserialize for LineSeries.
namespace json_util
{

template <class GenericJson, class Owner, class Value>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<
    Owner, clglitch::LineSeries<Value>
  > const & prop)
{
  obj.*(prop.member) =
    clglitch::LineSeries<Value>::multiFormatDeserialize(json[prop.name]);
}



template <class GenericJson, class Owner, class Value>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<
    Owner, clglitch::LineSeries<Value>, JsonOption::Optional
  > const & prop)
{
  auto it = json.FindMember(prop.name);
  if (it != json.MemberEnd())
  {
    obj.*(prop.member) =
      clglitch::LineSeries<Value>::multiFormatDeserialize(it->value);
  }
}

}


#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_JSON_DEFS_LINE_SERIES_H
