//
// Created by bridg on 3/20/2021.
//

#ifndef CL_GLITCHER_INCLUDE_FILE_UTIL_APPEND_NUMBER_H
#define CL_GLITCHER_INCLUDE_FILE_UTIL_APPEND_NUMBER_H

#include <string>

namespace file_util {

template <typename Number>
Number calcDigits(Number number)
{
  Number count {0};

  do {
    number /= 10;
    count += 1;
  }
  while (number != 0);

  return count;
}



template <typename Number>
void appendNumber(std::string & str, Number digits, Number number)
{
  std::string numberStr = std::to_string(number);

  for (Number i {0}; i < digits - numberStr.size(); i++) {
    str += '0';
  }

  str += numberStr;
}

}

#endif //CL_GLITCHER_INCLUDE_FILE_UTIL_APPEND_NUMBER_H
