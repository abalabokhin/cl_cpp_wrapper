#ifndef KERNELRUNNINGSETTINGS_H
#define KERNELRUNNINGSETTINGS_H

#include <CL/cl.hpp>
#include <array>

class KernelRunningSettings
{
public:
    KernelRunningSettings(const std::array<size_t, 3> & global, const std::array<size_t, 3> & local, const std::array<size_t, 3> & offset = {0, 0, 0})
        : global(global), local(local), offset(offset)
    {}

    cl::NDRange GetLocalClNDRange() const
    {
        if (local[2] != 0)
            return cl::NDRange(local[0], local[1], local[2]);
        if (local[1] != 0)
            return cl::NDRange(local[0], local[1]);
        return cl::NDRange(local[0]);
    }

    cl::NDRange GetGlobalClNDRange() const
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

    cl::NDRange GetOffsetClNDRange() const
    {
        return cl::NDRange(offset[0], offset[1], offset[2]);
    }


    size_t getLocalId(uint dimindx) const { return local[dimindx]; }
    size_t getGlobalId(uint dimindx) const { return global[dimindx]; }
    std::array<size_t, 3> const & GetOffsetRange() const { return offset; }
private:
    std::array<size_t, 3> global;
    std::array<size_t, 3> local;
    std::array<size_t, 3> offset;
};

#define get_global_id(dimindx) range.getGlobalId(dimindx)

#define get_local_id(dimindx) range.getLocalId(dimindx)

#endif // KERNELRUNNINGSETTINGS_H
