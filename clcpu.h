#ifndef CLCPU_H
#define CLCPU_H

#include <array>
#include <CL/cl.hpp>
#include <cmath>
#include <KernelRunningSettings.h>

#define __global
#define __kernel
#define uint cl_uint
#define uint4 cl_uint4
#define uint2 cl_uint2
#define float4 cl_float4
#define int4 cl_int4

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
    float lenght = sqrt(pow(vector.s0, 2) + pow(vector.s1, 2) + pow(vector.s2, 2) + pow(vector.s3, 2));
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

inline float distance(const uint4 & point1, const uint4 & point2) {
    return sqrt(pow((int)point1.s0 - (int)point2.s0, 2) +
                pow((int)point1.s1 - (int)point2.s1, 2) +
                pow((int)point1.s2 - (int)point2.s2, 2) +
                pow((int)point1.s3 - (int)point2.s3, 2));
}

inline float distance(const int4 & point1, const uint4 & point2) {
    return sqrt(pow((int)point1.s0 - (int)point2.s0, 2) +
                pow((int)point1.s1 - (int)point2.s1, 2) +
                pow((int)point1.s2 - (int)point2.s2, 2) +
                pow((int)point1.s3 - (int)point2.s3, 2));
}

inline bool operator == (uint4 const & left, uint4 const & right) {
    return left.s0 == right.s0 && left.s1 == right.s1 && left.s2 == right.s2 && left.s3 == right.s3;
}

inline bool operator != (uint4 const & left, uint4 const & right) {
    return !(left == right);
}

inline int4 operator - (uint4 const & left, uint4 const & right) {
    return int4 {left.s0 - right.s0, left.s1 - right.s1, left.s2 - right.s2, left.s3 - right.s3};
}

inline int4 operator - (uint4 const & left, int4 const & right) {
    return int4 {left.s0 - right.s0, left.s1 - right.s1, left.s2 - right.s2, left.s3 - right.s3};
}

inline int4 operator - (int4 const & left, uint4 const & right) {
    return int4 {left.s0 - right.s0, left.s1 - right.s1, left.s2 - right.s2, left.s3 - right.s3};
}

inline int4 operator + (uint4 const & left, int4 const & right) {
    return int4 {left.s0 + right.s0, left.s1 + right.s1, left.s2 + right.s2, left.s3 + right.s3};
}

inline float4 normalize(int4 const & vector) {
    float lenght = sqrt(pow(vector.s0, 2) + pow(vector.s1, 2) + pow(vector.s2, 2) + pow(vector.s3, 2));
    if (lenght == 0)
        return float4 {vector.s0, vector.s1, vector.s2, vector.s3};
    return float4 {vector.s0 / lenght, vector.s1 / lenght, vector.s2 / lenght, vector.s3 / lenght};
}

template<typename _Tp>
inline const _Tp&
max(const _Tp& __a, const _Tp& __b)
{
    if (__a > __b)
        return __a;
    return __b;
}

template<typename _Tp>
inline const _Tp&
min(const _Tp& __a, const _Tp& __b)
{
    if (__b > __a)
        return __a;
    return __b;
}

#endif // CLCPU_H
