#ifndef CLCPU_H
#define CLCPU_H

#include <CL/cl.hpp>
#include <math.h>

#define __global
#define __kernel
#define uint cl_uint
#define uint4 cl_uint4
#define uint2 cl_uint2
#define float4 cl_float4

class CpuRange {
public:
    explicit CpuRange(const cl::NDRange & global, const cl::NDRange & local);

    size_t get_global_id(uint dimindx) { return global_ids[dimindx]++; }
private:
    size_t global_ids[3] = {0, 0, 0};
};

#define get_global_id(dimindx) range.get_global_id(dimindx)

template <typename T>
inline T atomic_inc(T *t) {
    return (*t)++;
}

inline float4 operator - (float4 const & left, float4 const & right) {
    return float4 {left.s0 - right.s0, left.s1 - right.s1, left.s2 - right.s2, left.s3 - right.s3};
}

inline float4 operator + (float4 const & left, float4 const & right) {
    return float4 {left.s0 + right.s0, left.s1 + right.s1, left.s2 + right.s2, left.s3 + right.s3};
}

inline float4 operator * (float4 const & vector, float const & scale) {
    return float4 {vector.s0 * scale, vector.s1 * scale, vector.s2 * scale, vector.s3 * scale};
}

inline float4 normalize(float4 const & vector) {
    float lenght = pow(vector.s0, 2) + pow(vector.s1, 2) + pow(vector.s2, 2) + pow(vector.s3, 2);
    if (lenght == 0)
        return vector;
    return float4 {vector.s0 / lenght, vector.s1 / lenght, vector.s2 / lenght, vector.s3 / lenght};
}

inline float dot(float4 const & vector1, float4 const & vector2) {
    return vector1.s0 * vector2.s0 + vector1.s1 * vector2.s1 + vector1.s2 * vector2.s2 + vector1.s3 * vector2.s3;
}

inline float4 cross(float4 const & vector1, float4 const & vector2) {
    return float4 {
        vector1.s2 * vector2.s3 - vector1.s3 * vector2.s2,
        vector1.s3 * vector2.s1 - vector1.s1 * vector2.s3,
        vector1.s1 * vector2.s2 - vector1.s2 * vector2.s1,
        0
    };
}

#endif // CLCPU_H
