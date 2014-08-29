#ifndef CLPROGRAMWRAPPER_H
#define CLPROGRAMWRAPPER_H

#include <CL/cl.hpp>
#include <vector>

class clProgramWrapper
{
public:
    clProgramWrapper(const cl::Context & context, std::string const & filename, std::vector<std::string> const & includePaths, std::vector<std::string> const & defines);
    clProgramWrapper() {}
    cl::Program const & GetProgram() { return program; }
private:
    cl::Program program;
};

#endif // CLPROGRAMWRAPPER_H
