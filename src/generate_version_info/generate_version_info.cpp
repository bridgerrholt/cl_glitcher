//
// Created by bridg on 12/17/2021.
//

#include <generate_version_info.h>

#include <exception>
#include <fstream>
#include <array>
#include <memory>

std::string exec(char const * cmd)
{
	std::array<char, 128> buffer {};
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

	if (!pipe)
	{
		throw std::runtime_error("popen() failed");
	}

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
		result += buffer.data();
	}

	return result;
}

// <namespace> <version_var_name> <git_commit_var_name> <output_file> <version> [git_commit]
void generateVersionInfo(int argc, char * argv[])
{
	if (argc != 5 && argc != 6)
		throw std::runtime_error("Invalid number of arguments");

	std::string git_commit;
	if (argc == 5)
	{
		git_commit = exec("git rev-parse --verify HEAD");
		if (git_commit.back() == '\n')
			git_commit.pop_back();
	}
	else
	{
		git_commit = argv[5];
	}

	std::ofstream f {argv[3]};
	generateVersionInfoStreamed(argv[0], argv[1], argv[2], f, argv[4], git_commit);
}
