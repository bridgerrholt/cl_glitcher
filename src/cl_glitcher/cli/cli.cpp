#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

#include <cli/cli.h>

namespace clglitch
{

namespace {

constexpr char const * GLOBAL_ENVIRONMENT_DESCRIPTION {
  "The global environment JSON file for usage with --cmd.\n"
  "The following JSON properties are currently supported:\n"
  " envDirRelativeToInput: string\n"
  "  The directory containing the local environment JSON file. Is relative to\n"
  "  the directory of the --cmd input file.\n"
  "  Default: \".\"\n"
  "\n"
  " envFilename: string\n"
  "  The name of the local environment JSON file. Is relative to\n"
  "  envDirRelativeToInput (which is relative to the directory of the --cmd"
  " input file).\n"
  "  Default: \"env.json\"\n"
  "\n"
  " searchForLocalEnv: boolean\n"
  "  Whether or not to search for the local environment using the"
  " envDirRelativeToInput and envFilename properties.\n"
  "  Default: true"
};

constexpr char const * LOCAL_ENVIRONMENT_DESCRIPTION {
  "The local environment JSON file for usage with --cmd.\n"
  "The following JSON properties are currently supported:\n"
  " inputFilename: string\n"
  "  The input file used for image manipulation commands. Can be overridden in\n"
  "  command files.\n"
  "\n"
  " outputExtension: string\n"
  "  The file extension for the output images."
};

}

std::pair<CmdExecutionParams, int> cli(int argc, char const * argv[])
{
  CmdExecutionParams res;
  CLI::App app{"Image glitcher using OpenCL GPU computing."};

  //res.jsonInstanceFilename = "default";
  auto * cmdOption = app.add_option(
    "--cmd,-C", res.jsonInstanceFilename,
    "Run a JSON command file");
  app.add_option(
    "--mod-file,-M", res.jsonModFilename,
    "Load mods from a JSON mod specification file");

  app.add_option(
      "--env,-E", res.globalEnvironmentFilename,
      GLOBAL_ENVIRONMENT_DESCRIPTION)
    ->needs(cmdOption);
  /*app.add_option(
      "--local-env,-e", res.localEnvironmentFilename,
      "The local environment file for usage with --cmd")
    ->needs(cmdOption);*/

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