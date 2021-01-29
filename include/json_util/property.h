//
// Created by bridg on 1/18/2021.
//

#ifndef CL_GLITCHER_INCLUDE_JSON_UTIL_PROPERTY_H
#define CL_GLITCHER_INCLUDE_JSON_UTIL_PROPERTY_H

#include <tuple>

#include <rapidjson/document.h>


namespace json_util
{

/// Used for storing JSON metadata
/// \tparam Owner The owner of the variable in question
/// \tparam T The type of variable in question
template <class Owner, class T>
class JsonProperty
{
  public:
    using Type = T;

    /// Pointer to the variable
    T Owner::*member;

    /// Name of the variable for JSON serialization and deserialization
    char const * name;

    constexpr JsonProperty(T Owner::*member, char const * name) :
      member{member},
      name{name} {}
};



/// Convenient wrapper for template deduction
template <class Owner, class T>
constexpr JsonProperty<Owner, T>
makeProp(T Owner::*member, char const * name)
{
  return {member, name};
}


/// Convenient macro for when the member variable has the same name as the JSON
/// property.
#define JSON_UTIL_MAKE_PROP(owner, name) (makeProp(&owner::name, #name))



/// Used for ensuring an arg list contains only JsonProperty objects.
template <class Owner, class T>
constexpr void
verifyPropList(JsonProperty<Owner, T> const & first)
{

}

template <class Owner, class T, class ... ArgPack>
constexpr void
verifyPropList(JsonProperty<Owner, T> const & first, ArgPack && ... args)
{
  verifyPropList(std::forward<ArgPack>(args)...);
}



/// Convenient function for creating correct JsonProperty tuples.
template <class Owner, class T, class ... ArgPack>
constexpr std::tuple<JsonProperty<Owner, T>, ArgPack...>
propList(JsonProperty<Owner, T> && first, ArgPack && ... args)
{
  verifyPropList(first, std::forward<ArgPack>(args)...);
  return {first, std::forward<ArgPack>(args)...};
}



/// Used for template deduction
template <class GenericJson, class Owner>
void deserialize2(
  GenericJson const & json,
  Owner & obj);



/// Deserialization
// object
template <class GenericJson, class Owner, class T>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, T> const & prop)
{
  deserialize2(json[prop.name].GetObject(), obj.*(prop.member));
}


// bool
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, bool> const & prop)
{
  obj.*(prop.member) = json[prop.name].GetBool();
}


// int
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, int> const & prop)
{
  obj.*(prop.member) = json[prop.name].GetInt();
}


// unsigned
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, unsigned> const & prop)
{
  obj.*(prop.member) = json[prop.name].GetUint();
}


// int64_t
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, int64_t> const & prop)
{
  obj.*(prop.member) = json[prop.name].GetInt64();
}


// uint64_t
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, uint64_t> const & prop)
{
  obj.*(prop.member) = json[prop.name].GetUint64();
}


// float
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, float> const & prop)
{
  obj.*(prop.member) = json[prop.name].GetFloat();
}


// double
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, double> const & prop)
{
  obj.*(prop.member) = json[prop.name].GetDouble();
}


// std::string
template <class GenericJson, class Owner>
void deserialize(
  GenericJson const & json,
  Owner & obj,
  JsonProperty<Owner, std::string> const & prop)
{
  obj.*(prop.member) = json[prop.name].GetString();
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
