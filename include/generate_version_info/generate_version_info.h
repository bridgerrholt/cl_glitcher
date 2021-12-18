//
// Created by bridg on 12/17/2021.
//

#ifndef CL_GLITCHER_GENERATE_VERSION_INFO_H
#define CL_GLITCHER_GENERATE_VERSION_INFO_H

#include <string>

template <class OStream>
void generateVersionInfoStreamed(
		char const * varNamespace,
		char const * versionVarName, char const * gitCommitVarName,
		OStream & oStream,
		char const * version, std::string const & gitCommit)
{
	oStream << "namespace " << varNamespace << "{\n";
	oStream << "constexpr char const * " << versionVarName << " {\"" << version << "\"};\n";
	oStream << "constexpr char const * " << gitCommitVarName << " {\"" << gitCommit << "\"};\n";
	oStream << "}\n";
}

void generateVersionInfo(int argc, char * argv[]);

#endif //CL_GLITCHER_GENERATE_VERSION_INFO_H
