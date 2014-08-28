#ifndef KERNELRUNNINGSETTINGS_H
#define KERNELRUNNINGSETTINGS_H

#include <CL/cl.hpp>
#include <array>

class KernelRunningSettings
{
public:
    KernelRunningSettings(std::array<int, 3> const & global, std::array<int, 3> const & local, std::array<int, 3> const & offset = {0, 0, 0});
    cl::NDRange GetLocalClNDRange() const;
    cl::NDRange GetGlobalClNDRange() const;
    cl::NDRange GetOffsetClNDRange() const;
private:
    std::array<int, 3> global;
    std::array<int, 3> local;
    std::array<int, 3> offset;
};

#endif // KERNELRUNNINGSETTINGS_H
