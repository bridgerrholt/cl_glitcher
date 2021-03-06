//
// Created by bridg on 3/5/2021.
//

#include <iostream>
#include <stringify_to_header.h>

int main(int argc, char * argv[])
{
  if (argc < 4)
  {
    std::cout <<
      "Example usage: stringify_to_header <var_namespace> <var_name> <input_file> <output_file>\n";
  }
  else
  {
    stringifyToHeader(argv[1], argv[2], argv[3], argv[4]);
  }
}