#include <iostream>

#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

#include <cli/cli.h>

int main(int argc, char * argv[])
{
  using namespace clgitch;

  auto [res, code] = cli(argc, argv);

  if (code == 0)
  {
    std::cout << res.filename << '\n';
  }

  return code;
}
