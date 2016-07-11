#ifndef CLGPUKERNEL_H
#define CLGPUKERNEL_H

#include "KernelRunningSettings.h"
#include "CpuGpuBuffer.h"
#include <CL/cl2.hpp>

#define CREATE_GPU_KERNEL(variableName, kernelName, programVariableName) clGpuKernel variableName = \
    clGpuKernel(programVariableName.GetProgram(), OpenCLManager::GetInstance()->GetDefaultCommandQueue(), "kernelName");

class clGpuKernel : public cl::Kernel
{
public:
    clGpuKernel(const cl::Program &program, const cl::CommandQueue &cq, const char *name)
        :   cl::Kernel(program, name), defaultCq(&cq)
    {}

    clGpuKernel()
    {}

    template<typename... Values> void RunKernel(KernelRunningSettings const & runningSettings, Values... values) {
        SetAllArgs(values...);
        defaultCq->enqueueNDRangeKernel(*this, runningSettings.GetOffsetClNDRange(), runningSettings.GetGlobalClNDRange(), runningSettings.GetLocalClNDRange());
        defaultCq->finish();
    }

    template<typename... Values> void SetAllArgs(Values... values) {
        iArg = 0;
        SetArg(0);
        AddArgs(values...);
    }

private:
    void AddArgs() {}

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

#endif // CLGPUKERNEL_H
