//
// Created by bridg on 1/18/2021.
//

#ifndef CL_GLITCHER_INCLUDE_JSON_PROPERTY_JSON_PROPERTY_H
#define CL_GLITCHER_INCLUDE_JSON_PROPERTY_JSON_PROPERTY_H

namespace json_util
{

template <class Owner, class T>
class JsonProperty
{
  public:
    using Type = T;

    T Owner::*member;
    char const * name;

    constexpr JsonProperty(T Owner::*member, char const * name) :
      member{member},
      name{name} {}
};

}

#endif //CL_GLITCHER_INCLUDE_JSON_PROPERTY_JSON_PROPERTY_H
