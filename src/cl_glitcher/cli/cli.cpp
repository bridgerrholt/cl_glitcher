#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

#include <cli/cli.h>

namespace clgitch
{

bool CliResult::operator==(CliResult const & other) const
{
  return
    filename == other.filename;
}



std::pair<CliResult, int> cli(int argc, char const * argv[])
{
  CliResult res;
  CLI::App app{"Image glitcher using OpenCL GPU computing."};

  res.filename = "default";
  app.add_option(
    "--run-json,-J", res.filename, "Run a JSON specification file");

  try
  {
    app.parse(argc, argv);
  }
  catch (const CLI::ParseError &e)
  {
    return {res, app.exit(e)};
  }

  return {res, 0};
}

}