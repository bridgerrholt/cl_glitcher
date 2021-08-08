//
// Created by bridg on 7/24/2021.
//
#include <load_json_file.h>

#include <gtest/gtest.h>

using namespace json_util;
using namespace rapidjson;

namespace {

constexpr char const * directory {CL_GLITCHER_TEST_DIRECTORY_JSON_UTIL};
std::string const directoryString {std::string(directory) + '/'};

}

TEST(TestJsonUtil, LoadJsonFileEmpty)
{
  auto doc = loadJsonFile(directoryString + "test_json_util_empty.json");
}
