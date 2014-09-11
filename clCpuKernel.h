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
        /*if (runningSettings.getGlobalId(2) != 0) {
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
        }*/
    }

private:
    std::function<void(KernelRunningSettings)> AddArgs(std::function<void(KernelRunningSettings)> fn) {
        return fn;
    }

    template<typename ArgsT, typename FuncArgsT, typename... ArgsTail, typename... FuncArgsTail>
    std::function<void(KernelRunningSettings)> AddArgs(std::function<void(KernelRunningSettings, FuncArgsT, FuncArgsTail... funcTail)> fn, ArgsT head, ArgsTail... tail) {
        return AddArgs(SetArg(fn, head), tail...);
    }

    /// General SetArg functions for different number of parameters of any types.
    template <typename ArgsT, typename FAT1>
    std::function<void(KernelRunningSettings)> SetArg(std::function<void(KernelRunningSettings, FAT1)> fn, ArgsT value) {
        return std::bind(fn, std::placeholders::_1, value);
    }

    template <typename ArgsT, typename FAT1, typename FAT2>
    std::function<void(KernelRunningSettings, FAT2)> SetArg(std::function<void(KernelRunningSettings, FAT1, FAT2)> fn, ArgsT value) {
        return std::bind(fn, std::placeholders::_1, value, std::placeholders::_2);
    }

    template <typename ArgsT, typename FAT1, typename FAT2, typename FAT3>
    std::function<void(KernelRunningSettings, FAT2, FAT3)> SetArg(std::function<void(KernelRunningSettings, FAT1, FAT2, FAT3)> fn, ArgsT value) {
        return std::bind(fn, std::placeholders::_1, value, std::placeholders::_2, std::placeholders::_3);
    }

    template <typename ArgsT, typename FAT1, typename FAT2, typename FAT3, typename FAT4>
    std::function<void(KernelRunningSettings, FAT2, FAT3, FAT4)> SetArg(std::function<void(KernelRunningSettings, FAT1, FAT2, FAT3, FAT4)> fn, ArgsT value) {
        return std::bind(fn, std::placeholders::_1, value, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    }

    template <typename ArgsT, typename FAT1, typename FAT2, typename FAT3, typename FAT4, typename FAT5>
    std::function<void(KernelRunningSettings, FAT2, FAT3, FAT4, FAT5)> SetArg(std::function<void(KernelRunningSettings, FAT1, FAT2, FAT3, FAT4, FAT5)> fn, ArgsT value) {
        return std::bind(fn, std::placeholders::_1, value, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
    }

    /*template <typename ArgsT, typename FuncArgsT, typename... Tail>
    std::function<void(Tail... tail, KernelRunningSettings)> SetArg(std::function<void(FuncArgsT, Tail... tail, KernelRunningSettings)> fn, ArgsT value) {
        return std::bind(fn, value, std::placeholders::_1);
    }*/
private:
    Fn * function;
};

#endif // CLCPUKERNEL_H
