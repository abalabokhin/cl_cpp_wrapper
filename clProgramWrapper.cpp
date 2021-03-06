#include "clManager.h"
#include "clProgramWrapper.h"
#include <fstream>
#include <iostream>

clProgramWrapper::clProgramWrapper(const cl::Context & context, const std::vector<cl::Device> & devices, std::string const & filename, std::vector<std::string> const & includePaths, std::vector<std::string> const & defines)
{
    /// read all from the file into string
    std::ifstream in(filename);
    std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    std::string commandLineString;
    /// collect all the includePaths
    for (auto & i : includePaths) {
        commandLineString += " -I ";
        commandLineString += i;
    }
    /// collect all the defines
    for (auto & i : defines) {
        commandLineString += " -D ";
        commandLineString += i;
    }
    /// add GPU_OPENCL define
    commandLineString += " -D GPU_OPENCL";

    cl::Program::Sources source{src};
    program = cl::Program(context, source, nullptr);
    try {
        program.build(devices, commandLineString.c_str());
    } catch (...)
    {}
    /// throw a normal exception here if there are any build errors.
    std::string str = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(OpenCLManager::GetInstance()->GetDefaultDevices()[0]);
    std::cout << "Build log:" << str.c_str() << "\n";
}
