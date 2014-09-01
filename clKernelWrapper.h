#ifndef CLKERNELWRAPPER_H
#define CLKERNELWRAPPER_H

#include "KernelRunningSettings.h"
#include "CpuGpuBuffer.h"
#include <CL/cl.hpp>

class clKernelWrapper : public cl::Kernel
{
public:
    clKernelWrapper(const cl::Program &program, const cl::CommandQueue &cq, const char *name)
        :   cl::Kernel(program, name), defaultCq(&cq)
    {}

    clKernelWrapper()
    {}

    template<typename... Values> void RunKernel(KernelRunningSettings const & runningSettings, Values... values) {
        SetAllArgs(values...);
        defaultCq->enqueueNDRangeKernel(*this, runningSettings.GetOffsetClNDRange(), runningSettings.GetGlobalClNDRange(), runningSettings.GetLocalClNDRange());
        defaultCq->finish();
    }

    template<typename... Values> void SetAllArgs(Values... values) {
        iArg = 0;
        AddArgs(values...);
    }

private:
    void AddArgs() {
        SetArg(0);
    }

    template<typename T, typename... Tail> void AddArgs(T head, Tail... tail) {
        SetArg(head);
        AddArgs(tail...);
    }

    template <typename T> void SetArg(T value) {
        setArg(iArg++, value);
    }

    template <typename T> void SetArg(CpuGpuBuffer<T> * value) {
        setArg(iArg++, value->getGpuBuffer());
    }

    int iArg = 0;
    const cl::CommandQueue * defaultCq;
};

#endif // CLKERNELWRAPPER_H
