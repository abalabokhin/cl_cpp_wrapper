#ifndef CLKERNELWRAPPER_H
#define CLKERNELWRAPPER_H

#include "KernelRunningSettings.h"

#include <CL/cl.hpp>

class clKernelWrapper : public cl::Kernel
{
public:
    clKernelWrapper(const cl::Program &program, const char *name)
        :   cl::Kernel(program, name)
    {}

    clKernelWrapper()
    {}

    template<typename... Values> void RunKernel(cl::CommandQueue commandQueue, KernelRunningSettings const & runningSettings, Values... values) {
        SetAllArgs(values...);
        commandQueue.enqueueNDRangeKernel(*this, runningSettings.GetOffsetClNDRange(), runningSettings.GetGlobalClNDRange(), runningSettings.GetLocalClNDRange());
    }

    template<typename... Values> void SetAllArgs(Values... values) {
        iArg = 0;
        AddArgs(values...);
    }

private:
    void AddArgs() {
        setArg(iArg++, 0);
    }

    template<typename T, typename... Tail> void AddArgs(T head, Tail... tail) {
        setArg(iArg++, head);
        AddArgs(tail...);
    }

    int iArg = 0;
};

#endif // CLKERNELWRAPPER_H
