//
// Created by bridg on 1/18/2021.
//

#ifndef CL_GLITCHER_INCLUDE_JSON_UTIL_PROPERTY_H
#define CL_GLITCHER_INCLUDE_JSON_UTIL_PROPERTY_H

#include <tuple>

#include <rapidjson/document.h>
#include <vector>


namespace json_util
{

enum class JsonOption
{
    None = 0,
    Optional = 1
};

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



/// Convenient wrapper for template deduction
template <class Owner, class T>
constexpr JsonProperty<Owner, T, JsonOption::None>
makeProp(T Owner::*member, char const * name)
{
  return {member, name};
}

template <class Owner, class T>
constexpr JsonProperty<Owner, T, JsonOption::Optional>
makeOptionalProp(T Owner::*member, char const * name)
{
  return {member, name};
}


/// Convenient macro for when the member variable has the same name as the JSON
/// property.
#define JSON_UTIL_MAKE_PROP(owner, name) \
  (json_util::makeProp(&owner::name, #name))
#define JSON_UTIL_MAKE_OPTIONAL_PROP(owner, name) \
  (json_util::makeOptionalProp(&owner::name, #name))



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



/// Convenient function for creating correct JsonProperty tuples.
template <class Owner, class T, JsonOption Options, class ... ArgPack>
constexpr std::tuple<JsonProperty<Owner, T, Options>, ArgPack...>
propList(JsonProperty<Owner, T, Options> && first, ArgPack && ... args)
{
  verifyPropList(first, std::forward<ArgPack>(args)...);
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

// object
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
