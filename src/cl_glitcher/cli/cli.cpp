#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

#include <cli/cli.h>

namespace clglitch
{

bool CliResult::operator==(CliResult const & other) const
{
  return
    jsonInstanceFilename == other.jsonInstanceFilename &&
    jsonModFilename == other.jsonModFilename;
}



std::pair<CliResult, int> cli(int argc, char const * argv[])
{
  CliResult res;
  CLI::App app{"Image glitcher using OpenCL GPU computing."};

  //res.jsonInstanceFilename = "default";
  app.add_option(
    "--run-json,-J", res.jsonInstanceFilename,
    "Run a JSON specification file");
  app.add_option(
    "--mod-file,-M", res.jsonModFilename,
    "Load mods from a JSON mod specification file");

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