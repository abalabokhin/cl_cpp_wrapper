#ifndef CLCPUKERNEL_H
#define CLCPUKERNEL_H

#include "KernelRunningSettings.h"
#include <functional>

class CpuRange;

template <class Fn> class clCpuKernel
{
public:
    clCpuKernel()
    {}

    clCpuKernel(Fn * fn)
        : function(fn)
    {}

    template<typename... Values> void RunKernel(KernelRunningSettings const & runningSettings, Values... values) {
        //auto newFn = SetAllArgs(values...);
        std::function<void(CpuRange)> newFn = AddArgs(std::function<void(Values... values, CpuRange)>(*function), values...);

        for (int i1 = 0; i1 < runningSettings.GetGlobalRange()[0]; ++i1)
            for (int i2 = 0; i2 < runningSettings.GetGlobalRange()[1]; ++i2)
                for (int i3 = 0; i3 < runningSettings.GetGlobalRange()[2]; ++i3)
                    newFn(CpuRange({i1, i2, i3}));
    }

    /*template<typename... Values> auto SetAllArgs(Values... values) {
        return AddArgs(function, values...);
    }*/
private:
    std::function<void(CpuRange)> AddArgs(std::function<void(CpuRange)> fn) {
        return fn;
    }

    template<typename T, typename... Tail> std::function<void(Tail... tail, CpuRange)> AddArgs(std::function<void(T, Tail... tail, CpuRange)> fn, T head, Tail... tail) {
        return AddArgs(SetArg(fn, head), tail...);
    }

    template <typename T, typename... Tail> std::function<void(Tail... tail, CpuRange)> SetArg(std::function<void(T, Tail... tail, CpuRange)> fn, T value) {
        return std::bind(fn, std::placeholders::_1, value);
    }
private:
    Fn * function;
};

#endif // CLCPUKERNEL_H
