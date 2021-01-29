#include <property.h>

#include <gtest/gtest.h>

using namespace json_util;
using namespace rapidjson;

class Obj
{
  public:
    int objIntTest;
    float objFloatTest;
    std::string objStringTest;

    static constexpr auto jsonProps = propList(
      JSON_UTIL_MAKE_PROP(Obj, objIntTest),
      JSON_UTIL_MAKE_PROP(Obj, objFloatTest),
      JSON_UTIL_MAKE_PROP(Obj, objStringTest)
    );

    bool operator==(Obj const & other) const
    {
      return
        objIntTest == other.objIntTest &&
        objFloatTest == other.objFloatTest &&
        objStringTest == other.objStringTest;
    }
};

class Owner
{
  public:
    bool boolTestT;
    bool boolTestF;
    int intTest;
    unsigned uintTest;
    int64_t int64Test;
    uint64_t uint64Test;
    float floatTest;
    double doubleTest;
    std::string stringTest;
    Obj objTest;

    static constexpr auto jsonProps = propList(
      JSON_UTIL_MAKE_PROP(Owner, boolTestT),
      JSON_UTIL_MAKE_PROP(Owner, boolTestF),
      JSON_UTIL_MAKE_PROP(Owner, intTest),
      JSON_UTIL_MAKE_PROP(Owner, uintTest),
      JSON_UTIL_MAKE_PROP(Owner, int64Test),
      JSON_UTIL_MAKE_PROP(Owner, uint64Test),
      JSON_UTIL_MAKE_PROP(Owner, floatTest),
      JSON_UTIL_MAKE_PROP(Owner, doubleTest),
      JSON_UTIL_MAKE_PROP(Owner, stringTest),
      JSON_UTIL_MAKE_PROP(Owner, objTest)
    );

    bool operator==(Owner const & other) const
    {
      return
        boolTestT == other.boolTestT &&
        boolTestF == other.boolTestF &&
        intTest == other.intTest &&
        uintTest == other.uintTest &&
        int64Test == other.int64Test &&
        uint64Test == other.uint64Test &&
        floatTest == other.floatTest &&
        doubleTest == other.doubleTest &&
        stringTest == other.stringTest &&
        objTest == other.objTest;
    }
};

Document fullDoc()
{
  const char* json = R"({
    "boolTestT": true,
    "boolTestF": false,
    "intTest": -200,
    "uintTest": 200,
    "int64Test": -300,
    "uint64Test": 300,
    "floatTest": 10.5,
    "doubleTest": 100.25,
    "stringTest": "test string",
    "objTest": {
      "objIntTest": 100,
      "objFloatTest": 10.5,
      "objStringTest": "test"
    }
  })";

  Document d;
  d.Parse(json);

  return d;
}

TEST(TestClGlitcherCli, DeserializeAll)
{
  auto d = fullDoc();

  Owner o;
  deserialize(d, o);

  Owner expected {
    true, false,
    -200, 200,
    -300, 300,
    10.5, 100.25,
    "test string",
    {
      100, 10.5, "test"
    }
  };

  ASSERT_EQ(o, expected);
}

struct Child
{
  std::string name;

  static constexpr auto jsonProps = propList(
    JSON_UTIL_MAKE_PROP(Child, name)
  );
};

struct Parent
{
  Child obj;

  static constexpr auto jsonProps = propList(
    JSON_UTIL_MAKE_PROP(Parent, obj)
  );
};


TEST(TestClGlitcherCli, DeserializeNestedObj)
{
  Document d;
  d.Parse(R"({"obj": {"name": "bob"}})");

  Parent parent;
  deserialize(d, parent);

  ASSERT_EQ(parent.obj.name, "bob");
}