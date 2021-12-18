#include <generate_version_info.h>

#include <gtest/gtest.h>

#include "test_generate_version_info_1.h"

TEST(StringifyToHeader, StringifyToHeader)
{
  ASSERT_EQ(test::version, "0.0.0.1");
	ASSERT_EQ(test::git_commit, )
}