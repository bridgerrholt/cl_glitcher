//
// Created by bridg on 1/18/2021.
//

#ifndef CL_GLITCHER_INCLUDE_JSON_UTIL_PROPERTY_H
#define CL_GLITCHER_INCLUDE_JSON_UTIL_PROPERTY_H

#include <tuple>

#include <rapidjson/document.h>
#include <vector>

#include "json_option.h"

namespace json_util
{

/// Used for storing JSON metadata
/// \tparam Owner The owner of the variable in question
/// \tparam T The type of variable in question
template <class Owner, class T, JsonOption Options = JsonOption::None>
class JsonProperty
{
  public:
    using Type = T;

    /// Pointer to the variable
    T Owner::*member;

    /// Name of the variable for JSON serialization and deserialization
    char const * name;

    constexpr JsonProperty(T Owner::*member, char const * name) :
      member {member},
      name {name} {}
};



/// Used for storing JSON metadata
/// \tparam Owner The owner of the variable in question
/// \tparam T The type of variable in question
template <
  class Owner, class T, class Func, JsonOption Options = JsonOption::None>
class JsonPropertyCustom
{
  public:
    using Type = T;

    /// Pointer to the variable
    T Owner::*member;

    /// Name of the variable for JSON serialization and deserialization
    char const * name;

    Func f;

    constexpr JsonPropertyCustom(T Owner::*member, char const * name, Func f) :
      member {member},
      name {name},
      f {f} {}

    void execute(Owner & obj, rapidjson::Value const & value) const {
      f(obj, obj.*(member), value);
    }

    /*void execute(Owner & obj, rapidjson::Value const & value) {
      execute(f, obj, value);
    }

  private:
    template <class F>
    void execute(F const & func, Owner & obj, rapidjson::Value const & value)
    {
      func(obj, obj.*(member), value);
    }

    template <class F>
    void execute(F Owner::* const & func, Owner & obj, rapidjson::Value const & value)
    {
      obj.*func(obj.*member, value);
    }*/
};


/// Alternate syntax constructor for JsonProperty.
/// Only for non-optional properties. See makeOptionalProp below.
template <class Owner, class T>
constexpr JsonProperty<Owner, T, JsonOption::None>
makeProp(T Owner::*member, char const * name)
{
  return {member, name};
}



/// Alternate syntax constructor for JsonProperty.
/// Only for optional properties. See makeProp above.
template <class Owner, class T>
constexpr JsonProperty<Owner, T, JsonOption::Optional>
makeOptionalProp(T Owner::*member, char const * name)
{
  return {member, name};
}


/// Alternate syntax constructor for JsonProperty.
/// Only for non-optional properties. See makeOptionalProp below.
template <class Owner, class T, class Func>
constexpr JsonPropertyCustom<Owner, T, Func, JsonOption::None>
makeCustomProp(T Owner::*member, char const * name, Func f)
{
  return {member, name, f};
}



/// Alternate syntax constructor for JsonProperty.
/// Only for optional properties. See makeProp above.
template <class Owner, class T, class Func>
constexpr JsonPropertyCustom<Owner, T, Func, JsonOption::Optional>
makeCustomOptionalProp(T Owner::*member, char const * name, Func f)
{
  return {member, name, f};
}


/*/// Alternate syntax constructor for JsonProperty.
/// Only for non-optional properties. See makeOptionalProp below.
template <class Owner, class T, class Func Owner::*>
constexpr JsonPropertyCustom<Owner, T, Func Owner::*, JsonOption::None>
makeCustomProp(T Owner::*member, char const * name, Func Owner::*f)
{
  return {member, name, f};
}



/// Alternate syntax constructor for JsonProperty.
/// Only for optional properties. See makeProp above.
template <class Owner, class T, class Func>
constexpr JsonPropertyCustom<Owner, T, Func Owner::*, JsonOption::Optional>
makeCustomOptionalProp(T Owner::*member, char const * name, Func Owner::*f)
{
  return {member, name, f};
}*/



#define JSON_UTIL_DECLARE_PROP_LIST(...) \
  static constexpr auto jsonProps = std::make_tuple( \
    __VA_ARGS__ \
  );


/// Convenient macro for when the member variable has the same name as the JSON
/// property.
#define JSON_UTIL_MAKE_PROP(owner, name) \
  (json_util::makeProp(&owner::name, #name))



#define JSON_UTIL_MAKE_OPTIONAL_PROP(owner, name) \
  (json_util::makeOptionalProp(&owner::name, #name))


#define JSON_UTIL_MAKE_CUSTOM_PROP(owner, name, func) \
  (json_util::makeCustomProp(&owner::name, #name, func))

#define JSON_UTIL_MAKE_CUSTOM_OPTIONAL_PROP(owner, name, func) \
  (json_util::makeCustomOptionalProp(&owner::name, #name, func))


// --- verifyPropList ---

/// Used for ensuring an arg list contains only JsonProperty objects.
template <class Owner, class T, JsonOption Options>
constexpr void
verifyPropList(JsonProperty<Owner, T, Options> const & first)
{

}



template <class Owner, class T, JsonOption Options, class ... ArgPack>
constexpr void
verifyPropList(
  JsonProperty<Owner, T, Options> const & first, ArgPack && ... args)
{
  verifyPropList(std::forward<ArgPack>(args)...);
}



// --- propList ---

/// Convenient function for creating correct JsonProperty tuples.
/// All arguments must be JsonProperty objects.
/// @return A tuple of the JsonProperty objects
template <class Owner, class T, JsonOption Options, class ... ArgPack>
constexpr std::tuple<JsonProperty<Owner, T, Options>, ArgPack...>
propList(JsonProperty<Owner, T, Options> && first, ArgPack && ... args)
{
  //verifyPropList(first, std::forward<ArgPack>(args)...);
  return {first, std::forward<ArgPack>(args)...};
}



/// Used for template deduction
template <class GenericJson, class Owner>
void deserialize2(
  GenericJson const & json,
  Owner & obj);



#define __JSON_UTIL_DESERIALIZE_GENERIC(json, obj, prop, getFunc)\
  (obj).*((prop).member) = (json)[(prop).name].getFunc();

#define __JSON_UTIL_DESERIALIZE_GENERIC_OPTIONAL(json, obj, prop, getFunc)\
  {\
  auto it = (json).FindMember((prop).name);\
  if (it != (json).MemberEnd())\
    (obj).*((prop).member) = it->value.getFunc();\
  }

#define __JSON_UTIL_PROP_MEMBER(obj, prop)\
  ((obj).*((prop).member))



/// Deserialization
template <class GenericJson, class Owner, class T, JsonOption options>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, T, options> const & prop);


/// Deserialize using custom func
template <class GenericJson, class Owner, class T, class Func>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonPropertyCustom<Owner, T, Func> const & prop)
{
  prop.execute(obj, json[prop.name]);
  //prop.f(obj, obj.*(prop.member), json[prop.name]);
}



template <class GenericJson, class Owner, class T, class Func>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonPropertyCustom<Owner, T, Func, JsonOption::Optional> const & prop)
{
  auto it = json.FindMember(prop.name);
  if (it != json.MemberEnd())
  {
    prop.execute(obj, it->value);
    //prop.f(obj, obj.*(prop.member), it->value);
  }
}




/// Deserialize into JSON object (recurse)
template <class GenericJson, class Owner, class T>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, T> const & prop)
{
  deserialize2(json[prop.name].GetObject(), obj.*(prop.member));
}

template <class GenericJson, class Owner, class T>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, T, JsonOption::Optional> const & prop)
{
  auto it = json.FindMember(prop.name);
  if (it != json.MemberEnd())
  {
    deserialize2(it->value.GetObject(), obj.*(prop.member));
  }
}


// bool
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, bool> const & prop)
{
  //obj.*(prop.member) = json[prop.name].GetBool();
  __JSON_UTIL_DESERIALIZE_GENERIC(json, obj, prop, GetBool);
}

template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, bool, JsonOption::Optional> const & prop)
{
  //obj.*(prop.member) = json[prop.name].GetBool();
  __JSON_UTIL_DESERIALIZE_GENERIC_OPTIONAL(json, obj, prop, GetBool);
}

template <class JsonBool>
void deserialize(
  JsonBool const & jsonBool,
  bool & outBool)
{
  outBool = jsonBool.GetBool();
}


// int
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, int> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC(json, obj, prop, GetInt);
}

template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, int, JsonOption::Optional> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC_OPTIONAL(json, obj, prop, GetInt);
}

template <class JsonInt>
void deserialize(
  JsonInt const & jsonInt,
  int & outInt)
{
  outInt = jsonInt.GetInt();
}


// unsigned
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, unsigned> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC(json, obj, prop, GetUint);
}

template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, unsigned, JsonOption::Optional> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC_OPTIONAL(json, obj, prop, GetUint);
}

template <class JsonUInt>
void deserialize(
  JsonUInt const & jsonUInt,
  unsigned & outUInt)
{
  outUInt = jsonUInt.GetUint();
}


// int64_t
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, int64_t> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC(json, obj, prop, GetInt64);
}

template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, int64_t, JsonOption::Optional> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC_OPTIONAL(json, obj, prop, GetInt64);
}

template <class JsonInt64>
void deserialize(
  JsonInt64 const & jsonInt64,
  int64_t & outInt64)
{
  outInt64 = jsonInt64.GetInt64();
}


// uint64_t
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, uint64_t> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC(json, obj, prop, GetUint64);
}

template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, uint64_t, JsonOption::Optional> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC_OPTIONAL(json, obj, prop, GetUint64);
}

template <class JsonUInt64>
void deserialize(
  JsonUInt64 const & jsonUInt64,
  uint64_t & outUInt64)
{
  outUInt64 = jsonUInt64.GetUint64();
}


// float
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, float> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC(json, obj, prop, GetFloat);
}

template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, float, JsonOption::Optional> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC_OPTIONAL(json, obj, prop, GetFloat);
}

template <class JsonFloat>
void deserialize(
  JsonFloat const & jsonFloat,
  float & outFloat)
{
  outFloat = jsonFloat.GetFloat();
}


// double
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, double> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC(json, obj, prop, GetDouble);
}

template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, double, JsonOption::Optional> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC_OPTIONAL(json, obj, prop, GetDouble);
}

template <class JsonDouble>
void deserialize(
  JsonDouble const & jsonDouble,
  double & outDouble)
{
  outDouble = jsonDouble.GetDouble();
}


// std::string
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, std::string> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC(json, obj, prop, GetString);
}

template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, std::string, JsonOption::Optional> const & prop)
{
  __JSON_UTIL_DESERIALIZE_GENERIC_OPTIONAL(json, obj, prop, GetString);
}

template <class JsonString>
void deserialize(
  JsonString const & jsonString,
  std::string & outString)
{
  outString = jsonString.GetString();
}


// object declaration
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj);

// array
template <class GenericJson, class Owner, class T>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, std::vector<T>> const & prop)
{
  auto const & arr = json[prop.name].GetArray();
  std::vector<T> & vec = obj.*(prop.member);
  vec.reserve(arr.Size());
  for (auto const & el : arr) {
    T & t = vec.emplace_back();
    deserialize(el, t);
  }
}

template <class GenericJson, class Owner, class T>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, std::vector<T>, JsonOption::Optional> const & prop)
{
  auto it = json.FindMember(prop.name);
  if (it != json.MemberEnd()) {
    auto const & arr = it->value.GetArray();

    std::vector<T> & vec = obj.*(prop.member);
    vec.reserve(arr.Size());
    for (auto const & el : arr) {
      T & t = vec.emplace_back();
      deserialize(el, t);
    }
  }
}

template <class JsonArray, class T>
void deserialize(
  JsonArray const & jsonArray,
  std::vector<T> & outVector)
{
  auto const & arr = jsonArray.GetArray();

  outVector.reserve(arr.Size());

  for (auto const & el : arr) {
    T & t = outVector.emplace_back();
    deserialize(el, t);
  }
}


template <class Owner, class GenericJson>
Owner deserialize(
  GenericJson const & json)
{
  Owner o;
  deserialize(json, o);
  return o;
}


template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj)
{
  deserialize<0>(json, obj, obj.jsonProps);
}
template <class GenericJson, class Owner>
void deserialize2(
  GenericJson const & json,
  Owner & obj)
{
  deserialize<0>(json, obj, obj.jsonProps);
}



/// Deserialize all elements of the props tuple starting from the given index.
template <std::size_t index, class GenericJson, class Owner, class Tuple>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  Tuple const & props)
{
  if constexpr (index < std::tuple_size<Tuple>::value)
  {
    deserialize(json, obj, std::get<index>(props));
    deserialize<index + 1>(json, obj, props);
  }
}



// rapidjson-specific:
/*
// object
template <class Encoding, class Allocator, class Owner, class T>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj,
  JsonProperty<Owner, T> const & prop)
{
  deserialize2(value[prop.name].GetObject(), obj.*(prop.member));
}


// bool
template <class Encoding, class Allocator, class Owner>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj,
  JsonProperty<Owner, bool> const & prop)
{
  obj.*(prop.member) = value[prop.name].GetBool();
}


// int
template <class Encoding, class Allocator, class Owner>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj,
  JsonProperty<Owner, int> const & prop)
{
  obj.*(prop.member) = value[prop.name].GetInt();
}


// unsigned
template <class Encoding, class Allocator, class Owner>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj,
  JsonProperty<Owner, unsigned> const & prop)
{
  obj.*(prop.member) = value[prop.name].GetUint();
}


// int64_t
template <class Encoding, class Allocator, class Owner>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj,
  JsonProperty<Owner, int64_t> const & prop)
{
  obj.*(prop.member) = value[prop.name].GetInt64();
}


// uint64_t
template <class Encoding, class Allocator, class Owner>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj,
  JsonProperty<Owner, uint64_t> const & prop)
{
  obj.*(prop.member) = value[prop.name].GetUint64();
}


// float
template <class Encoding, class Allocator, class Owner>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj,
  JsonProperty<Owner, float> const & prop)
{
  obj.*(prop.member) = value[prop.name].GetUint64();
}


// double
template <class Encoding, class Allocator, class Owner>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj,
  JsonProperty<Owner, double> const & prop)
{
  obj.*(prop.member) = value[prop.name].GetUint64();
}


// std::string
template <class Encoding, class Allocator, class Owner>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj,
  JsonProperty<Owner, std::string> const & prop)
{
  obj.*(prop.member) = value[prop.name].GetString();
}

template <class Encoding, class Allocator, class Owner>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj)
{
  deserialize<0>(value, obj, obj.jsonProps);
}


template <std::size_t index, class Encoding, class Allocator, class Owner, class Tuple>
void deserialize(
  rapidjson::GenericValue<Encoding, Allocator> const & value,
  Owner & obj,
  Tuple const & props)
{
  if constexpr (index < std::tuple_size<Tuple>::value)
  {
    deserialize(value, obj, std::get<index>(props));
    deserialize<index + 1>(value, obj, props);
  }
}*/



}

#endif //CL_GLITCHER_INCLUDE_JSON_UTIL_PROPERTY_H
