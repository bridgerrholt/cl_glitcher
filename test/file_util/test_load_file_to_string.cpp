#include <file_util/load_file_to_string.h>

#include <gtest/gtest.h>

using namespace file_util;

constexpr char const * directory {CL_GLITCHER_TEST_DIRECTORY_FILE_UTIL};
std::string const testFile {std::string{directory} + "/test_load_file_to_string_1.txt"};

TEST(TestFileUtil, LoadFileToString)
{
  std::string expected {
    "This is an example file\n"
    "named test_load_file_to_string_1.txt\n"
  };

  std::string res {loadFileToString(testFile)};

  ASSERT_EQ(expected, res);
}