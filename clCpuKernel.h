#ifndef CLCPUKERNEL_H
#define CLCPUKERNEL_H

#include "KernelRunningSettings.h"
#include <functional>

template <class Fn> class clCpuKernel
{
public:
    clCpuKernel()
    {}

    clCpuKernel(Fn * fn)
        : function(fn)
    {}

    template<typename... Values> void RunKernel(KernelRunningSettings const & runningSettings, Values... values) {
        std::function<void(KernelRunningSettings)> newFn = AddArgs(std::function<Fn>(function), values...);
        //auto globalRange = runningSettings.get_global_id();
        if (runningSettings.getGlobalId(2) != 0) {
            for (size_t i1 = 0; i1 < runningSettings.getGlobalId(0); ++i1) {
                for (size_t i2 = 0; i2 < runningSettings.getGlobalId(1); ++i2) {
                    for (size_t i3 = 0; i3 < runningSettings.getGlobalId(2); ++i3) {
                        newFn(KernelRunningSettings(
                            {i1, i2, i3},
                            {i1 / runningSettings.getLocalId(0), i2 / runningSettings.getLocalId(1), i3 / runningSettings.getLocalId(2)}));
                        //function(values..., CpuRange({i1, i2, i3}));
                    }
                }
            }
            return;
        }
        if (runningSettings.getGlobalId(1) != 0) {
            for (size_t i1 = 0; i1 < runningSettings.getGlobalId(0); ++i1) {
                for (size_t i2 = 0; i2 < runningSettings.getGlobalId(1); ++i2) {
                    newFn(KernelRunningSettings(
                        {i1, i2},
                        {i1 / runningSettings.getLocalId(0), i2 / runningSettings.getLocalId(1)}));
                    //function(values..., CpuRange({i1, i2, 0}));
                }
            }
            return;
        }

        for (size_t i1 = 0; i1 < runningSettings.getGlobalId(0); ++i1) {
            newFn(KernelRunningSettings(
                {i1},
                {i1 / runningSettings.getLocalId(0)}));
            //function(values..., CpuRange({i1, 0, 0}));
        }
    }

private:
    std::function<void(KernelRunningSettings)> AddArgs(std::function<void(KernelRunningSettings)> fn) {
        return fn;
    }

    template<typename T, typename... Tail> std::function<void(Tail... tail, KernelRunningSettings)> AddArgs(std::function<void(T, Tail... tail, KernelRunningSettings)> fn, T head, Tail... tail) {
        return AddArgs(SetArg(fn, head), tail...);
    }

    template <typename T, typename... Tail> std::function<void(Tail... tail, KernelRunningSettings)> SetArg(std::function<void(T, Tail... tail, KernelRunningSettings)> fn, T value) {
        return std::bind(fn, std::placeholders::_1, value);
    }
private:
    Fn * function;
};

#endif // CLCPUKERNEL_H
