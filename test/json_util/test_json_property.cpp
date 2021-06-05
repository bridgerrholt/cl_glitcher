#include <property.h>

#include <gtest/gtest.h>

using namespace json_util;
using namespace rapidjson;

class Obj
{
  public:
    int objIntTest {0};
    float objFloatTest {0};
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

/// Given an array of the following form [int, float, string],
/// multiply int and float by 10, add "0" to string.
template <class Owner>
static void deserializeCustomObj(
  Owner & owner, Obj & obj, rapidjson::Value const & json)
{
  obj = {
    json[0].GetInt() * 10,
    json[1].GetFloat() * 10.0f,
    std::string(json[2].GetString()) + "0"
  };
}

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
    std::vector<int> arrayTest;
    std::vector<Obj> arrayOfObjTest;
    Obj objTest;
    Obj customObjTest;

    static constexpr auto jsonProps = std::make_tuple(
      JSON_UTIL_MAKE_PROP(Owner, boolTestT),
      JSON_UTIL_MAKE_PROP(Owner, boolTestF),
      JSON_UTIL_MAKE_PROP(Owner, intTest),
      JSON_UTIL_MAKE_PROP(Owner, uintTest),
      JSON_UTIL_MAKE_PROP(Owner, int64Test),
      JSON_UTIL_MAKE_PROP(Owner, uint64Test),
      JSON_UTIL_MAKE_PROP(Owner, floatTest),
      JSON_UTIL_MAKE_PROP(Owner, doubleTest),
      JSON_UTIL_MAKE_PROP(Owner, stringTest),
      JSON_UTIL_MAKE_PROP(Owner, arrayTest),
      JSON_UTIL_MAKE_PROP(Owner, arrayOfObjTest),
      JSON_UTIL_MAKE_PROP(Owner, objTest),
      JSON_UTIL_MAKE_CUSTOM_PROP(Owner, customObjTest, deserializeCustomObj<Owner>)
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
        arrayTest == other.arrayTest &&
        arrayOfObjTest == other.arrayOfObjTest &&
        objTest == other.objTest &&
        customObjTest == other.customObjTest;
    }
};



class OwnerAllOptional
{
  public:
    bool boolTestT {true};
    bool boolTestF {false};
    int intTest {-1};
    unsigned uintTest {1};
    int64_t int64Test {-2};
    uint64_t uint64Test {2};
    float floatTest {1.5};
    double doubleTest {10.25};
    std::string stringTest {"default"};
    Obj objTest;
    Obj customObjTest;

    static constexpr auto jsonProps = propList(
      JSON_UTIL_MAKE_OPTIONAL_PROP(OwnerAllOptional, boolTestT),
      JSON_UTIL_MAKE_OPTIONAL_PROP(OwnerAllOptional, boolTestF),
      JSON_UTIL_MAKE_OPTIONAL_PROP(OwnerAllOptional, intTest),
      JSON_UTIL_MAKE_OPTIONAL_PROP(OwnerAllOptional, uintTest),
      JSON_UTIL_MAKE_OPTIONAL_PROP(OwnerAllOptional, int64Test),
      JSON_UTIL_MAKE_OPTIONAL_PROP(OwnerAllOptional, uint64Test),
      JSON_UTIL_MAKE_OPTIONAL_PROP(OwnerAllOptional, floatTest),
      JSON_UTIL_MAKE_OPTIONAL_PROP(OwnerAllOptional, doubleTest),
      JSON_UTIL_MAKE_OPTIONAL_PROP(OwnerAllOptional, stringTest),
      JSON_UTIL_MAKE_OPTIONAL_PROP(OwnerAllOptional, objTest),
      JSON_UTIL_MAKE_CUSTOM_OPTIONAL_PROP(
        OwnerAllOptional,
        customObjTest,
        deserializeCustomObj<OwnerAllOptional>)
    );

    bool operator==(OwnerAllOptional const & other) const
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
          objTest == other.objTest &&
          customObjTest == other.customObjTest;
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
    "arrayTest": [10, 20],
    "arrayOfObjTest": [
      {
        "objIntTest": 1,
        "objFloatTest": 1.5,
        "objStringTest": "test1"
      }, {
        "objIntTest": 2,
        "objFloatTest": 2.5,
        "objStringTest": "test2"
      }],
    "objTest": {
      "objIntTest": 100,
      "objFloatTest": 10.5,
      "objStringTest": "test"
    },
    "customObjTest": [100, 10.5, "test"]
  })";

  Document d;
  d.Parse(json);

  return d;
}



Document emptyDoc()
{
  const char * json = "{}";

  Document d;
  d.Parse(json);

  return d;
}



TEST(TestJsonUtil, DeserializeAllNoOptional)
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
    { 10, 20 },
    {
      Obj { 1, 1.5f, "test1"},
      Obj { 2, 2.5f, "test2"}
    },
    {
      100, 10.5f, "test"
    },
    {
      1000, 105.0f, "test0"
    }
  };

  ASSERT_EQ(o, expected);
}


TEST(TestJsonUtil, DeserializeAllOptional)
{
  auto d = fullDoc();

  OwnerAllOptional o;
  deserialize(d, o);

  OwnerAllOptional expected {
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


TEST(TestJsonUtil, DeserializeAllIndividual)
{
  auto d = fullDoc();

  Owner o;
  deserialize(d["boolTestT"], o.boolTestT);
  deserialize(d["boolTestF"], o.boolTestF);
  deserialize(d["intTest"], o.intTest);
  deserialize(d["uintTest"], o.uintTest);
  deserialize(d["int64Test"], o.int64Test);
  deserialize(d["uint64Test"], o.uint64Test);
  deserialize(d["floatTest"], o.floatTest);
  deserialize(d["doubleTest"], o.doubleTest);
  deserialize(d["stringTest"], o.stringTest);
  deserialize(d["arrayTest"], o.arrayTest);
  deserialize(d["arrayOfObjTest"], o.arrayOfObjTest);
  deserialize(d["objTest"], o.objTest);

  Owner expected {
    true, false,
    -200, 200,
    -300, 300,
    10.5, 100.25,
    "test string",
    { 10, 20 },
    {
      Obj { 1, 1.5, "test1"},
      Obj { 2, 2.5, "test2"}
    },
    {
      100, 10.5, "test"
    }
  };

  ASSERT_EQ(o, expected);
}


TEST(TestJsonUtil, DeserializeAllOptionalEmptyJson)
{
  auto d = emptyDoc();

  OwnerAllOptional o;
  deserialize(d, o);

  OwnerAllOptional expected {};

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


TEST(TestJsonUtil, DeserializeNestedObj)
{
  Document d;
  d.Parse(R"({"obj": {"name": "bob"}})");

  Parent parent;
  deserialize(d, parent);

  ASSERT_EQ(parent.obj.name, "bob");
}