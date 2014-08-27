#ifndef CLKERNEL_H
#define CLKERNEL_H

#include <CL/cl.hpp>

class clKernel : public cl::Kernel
{
public:
    clKernel(const cl::Program &program, const char *name)
        :   cl::Kernel(program, name)
    {}

    template<typename... Values> void SetAllArgs(Values... values) {
        iArg = 0;
        AddArgs(values...);
    }

    void AddArgs() {}

    template<typename T, typename... Tail> void AddArgs(T head, Tail... tail) {
        setArg(iArg++, head);
        AddArgs(tail...);
    }
private:
    int iArg = 0;
};

#endif // CLKERNEL_H
