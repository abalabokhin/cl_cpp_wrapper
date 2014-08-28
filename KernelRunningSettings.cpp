#include "KernelRunningSettings.h"

KernelRunningSettings::KernelRunningSettings(std::array<int, 3> const & global, std::array<int, 3> const & local, std::array<int, 3> const & offset)
    : global(global), local(local), offset(offset)
{}

cl::NDRange KernelRunningSettings::GetLocalClNDRange() const
{
    if (local[2] != 0)
        return cl::NDRange(local[0], local[1], local[2]);
    if (local[1] != 0)
        return cl::NDRange(local[0], local[1]);
    return cl::NDRange(local[0]);
}

cl::NDRange KernelRunningSettings::GetGlobalClNDRange() const
{
    if (local[2] != 0) {
        return cl::NDRange(
                (global[0] + local[0] - 1) / local[0] * local[0],
                (global[1] + local[1] - 1) / local[1] * local[1],
                (global[2] + local[2] - 1) / local[2] * local[2]);
    }
    if (local[1] != 0) {
        return cl::NDRange(
                (global[0] + local[0] - 1) / local[0] * local[0],
                (global[1] + local[1] - 1) / local[1] * local[1]);
    }

    return cl::NDRange(
            (global[0] + local[0] - 1) / local[0] * local[0]);
}

cl::NDRange KernelRunningSettings::GetOffsetClNDRange() const
{
    return cl::NDRange(offset[0], offset[1], offset[2]);
}
