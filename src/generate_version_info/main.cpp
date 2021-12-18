//
// Created by bridg on 12/17/2021.
//

#include <iostream>
#include <fstream>
#include <array>
#include <memory>

#include <generate_version_info.h>

int main(int argc, char * argv[])
{
	for (int i = 0; i < argc; i++)
		std::cout << argv[i] << '\n';
	std::cout <<
	          "Usage: generate_version_info <namespace> <version_var_name> <git_commit_var_name> <output_file> <version> [git_commit]\n";
	if (argc != 6 && argc != 7)
	{
		std::cout <<
			"Usage: generate_version_info <namespace> <version_var_name> <git_commit_var_name> <output_file> <version> [git_commit]\n";
	}
	else
	{
		generateVersionInfo(argc - 1, argv + 1);
	}
}
