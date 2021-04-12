#include <file_util/append_number.h>

#include <gtest/gtest.h>

using namespace file_util;

TEST(TestFileUtil, CalcDigits0)
{
  ASSERT_EQ(calcDigits(0), 1);
}

TEST(TestFileUtil, CalcDigits1)
{
  ASSERT_EQ(calcDigits(1), 1);
}

TEST(TestFileUtil, CalcDigits10)
{
  ASSERT_EQ(calcDigits(10), 2);
}

TEST(TestFileUtil, CalcDigits100)
{
  ASSERT_EQ(calcDigits(100), 3);
}


TEST(TestFileUtil, AppendNumber1)
{
  std::string s;
  appendNumber(s, 2, 1);
  ASSERT_EQ("01", s);
}


void testNumber(int maxDigits, int digitsDiff, int i)
{
  std::string s;
  appendNumber(s, maxDigits, i);

  std::string sExpected (digitsDiff, '0');
  sExpected += std::to_string(i);

  ASSERT_EQ(s, sExpected);
}


TEST(TestFileUtil, AppendNumberLoop)
{
  int maxDigits {4};
  int i {1};

  for (; i < 10; i++)
  {
    testNumber(maxDigits, maxDigits - 1, i);
  }

  for (; i < 100; i++)
  {
    testNumber(maxDigits, maxDigits - 2, i);
  }

  for (; i < 1000; i++)
  {
    testNumber(maxDigits, maxDigits - 3, i);
  }

  for (; i < 10000; i++)
  {
    testNumber(maxDigits, maxDigits - 4, i);
  }
}