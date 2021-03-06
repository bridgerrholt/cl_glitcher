#include <stringify_to_header.h>

#include <gtest/gtest.h>

#include "test_stringify_to_header_1.h"

TEST(StringifyToHeader, StringifyToHeader)
{
  std::string expected {
    "stringify_to_header test \"\\n\\\"\\\\\"\n"
    "\"\"\n"
    "''\n"};

  ASSERT_EQ(test::testString1, expected);
}