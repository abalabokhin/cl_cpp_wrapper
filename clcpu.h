#ifndef CLCPU_H
#define CLCPU_H

#include <array>
#include <CL/cl2.hpp>
#include <cmath>
#include <KernelRunningSettings.h>
#include <limits.h>

#define __global
#define __kernel
#define __constant
#define uint cl_uint
#define uint4 cl_uint4
#define uint2 cl_uint2
#define float4 cl_float4
#define float2 cl_float2
#define int4 cl_int4
#define int2 cl_int2

template <typename T>
inline T atomic_inc(T *t) {
    return (*t)++;
}

template <typename T>
inline T atomic_add(T *t, T addition) {
    auto oldValue = *t;
    (*t)+=addition;
    return oldValue;
}

inline float2 operator - (float2 const & left, float2 const & right) {
    return float2 {left.s0 - right.s0, left.s1 - right.s1};
}

inline float2 operator + (float2 const & left, float2 const & right) {
    return float2 {left.s0 + right.s0, left.s1 + right.s1};
}

inline float4 operator - (float4 const & left, float4 const & right) {
    return float4 {left.s0 - right.s0, left.s1 - right.s1, left.s2 - right.s2, left.s3 - right.s3};
}

inline float4 operator + (float4 const & left, float4 const & right) {
    return float4 {left.s0 + right.s0, left.s1 + right.s1, left.s2 + right.s2, left.s3 + right.s3};
}

inline float4 operator * (float4 const & vector, float scale) {
    return float4 {vector.s0 * scale, vector.s1 * scale, vector.s2 * scale, vector.s3 * scale};
}

inline float4 operator * (cl_int4 const & v, float k) {
    return float4{(float)v.s0, (float)v.s1, (float)v.s2, (float)v.s3} * k;
}

inline float4 normalize(float4 const & vector) {
    float lenght = sqrt(pow(vector.s0, 2) + pow(vector.s1, 2) + pow(vector.s2, 2) + pow(vector.s3, 2));
    if (lenght == 0)
        return vector;
    return float4 {vector.s0 / lenght, vector.s1 / lenght, vector.s2 / lenght, vector.s3 / lenght};
}

inline float2 normalize(float2 const & vector) {
    float lenght = sqrt(pow(vector.s0, 2) + pow(vector.s1, 2));
    if (lenght == 0)
        return vector;
    return float2 {vector.s0 / lenght, vector.s1 / lenght};
}

inline float dot(float4 const & vector1, float4 const & vector2) {
    return vector1.s0 * vector2.s0 + vector1.s1 * vector2.s1 + vector1.s2 * vector2.s2 + vector1.s3 * vector2.s3;
}

inline float dot(float2 const & vector1, float2 const & vector2) {
    return vector1.s0 * vector2.s0 + vector1.s1 * vector2.s1;
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
                pow((int)point1.s2 - (int)point2.s2, 2));
}

inline float distance(const int4 & point1, const uint4 & point2) {
    return sqrt(pow((int)point1.s0 - (int)point2.s0, 2) +
                pow((int)point1.s1 - (int)point2.s1, 2) +
                pow((int)point1.s2 - (int)point2.s2, 2));
}

inline float distance(const int4 & point1, const int4 & point2) {
    return sqrt(pow((int)point1.s0 - (int)point2.s0, 2) +
                pow((int)point1.s1 - (int)point2.s1, 2) +
                pow((int)point1.s2 - (int)point2.s2, 2));
}

inline float distance(const int2 & point1, const int2 & point2) {
    return sqrt(pow((int)point1.s0 - (int)point2.s0, 2) +
                pow((int)point1.s1 - (int)point2.s1, 2));
}

inline float length(const int2 & point1) {
    return sqrt(pow(point1.s0, 2) + pow(point1.s1, 2));
}

inline float length(const float2 & point1) {
    return sqrt(pow(point1.s0, 2) + pow(point1.s1, 2));
}

inline bool operator == (uint4 const & left, uint4 const & right) {
    return left.s0 == right.s0 && left.s1 == right.s1 && left.s2 == right.s2 && left.s3 == right.s3;
}

inline bool operator == (int4 const & left, int4 const & right) {
    return left.s0 == right.s0 && left.s1 == right.s1 && left.s2 == right.s2 && left.s3 == right.s3;
}

inline bool operator == (int2 const & left, int2 const & right) {
    return left.s0 == right.s0 && left.s1 == right.s1;
}

inline bool operator != (uint4 const & left, uint4 const & right) {
    return !(left == right);
}

inline bool operator != (int4 const & left, int4 const & right) {
    return !(left == right);
}

inline bool operator != (int2 const & left, int2 const & right) {
    return !(left == right);
}

inline int4 operator - (int4 const & left, int4 const & right) {
    return int4 {left.s0 - right.s0, left.s1 - right.s1, left.s2 - right.s2, left.s3 - right.s3};
}

inline int4 operator + (int4 const & left, int4 const & right) {
    return int4 {left.s0 + right.s0, left.s1 + right.s1, left.s2 + right.s2, left.s3 + right.s3};
}

inline float4 normalize(int4 const & vector) {
    float lenght = sqrt(pow(vector.s0, 2) + pow(vector.s1, 2) + pow(vector.s2, 2) + pow(vector.s3, 2));
    if (lenght == 0)
        return float4 {(float)vector.s0, (float)vector.s1, (float)vector.s2, (float)vector.s3};
    return float4 {vector.s0 / lenght, vector.s1 / lenght, vector.s2 / lenght, vector.s3 / lenght};
}

inline int2 operator - (int2 const & left, int2 const & right) {
    return int2 {left.s0 - right.s0, left.s1 - right.s1};
}

inline int2 operator + (int2 const & left, int2 const & right) {
    return int2 {left.s0 + right.s0, left.s1 + right.s1};
}

inline float2 normalize(int2 const & vector) {
    float lenght = sqrt(pow(vector.s0, 2) + pow(vector.s1, 2));
    if (lenght == 0)
        return float2 {(float)vector.s0, (float)vector.s1};
    return float2 {vector.s0 / lenght, vector.s1 / lenght};
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
