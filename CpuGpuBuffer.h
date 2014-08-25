#ifndef CPUGPUBUFFER_H
#define CPUGPUBUFFER_H

#include <vector>
#include <CL/cl.hpp>

enum class BufferType {
    CPU,
    GPU
};

template <typename T>
class CpuGpuBuffer {
public:
    CpuGpuBuffer(cl::Context context, BufferType bufferType, size_t bufferSize);

    size_t getSize() { return size; }

    T * getCpuBuffer(cl::CommandQueue &cq);

    cl::Buffer & getGpuBuffer(cl::CommandQueue &cq);

    void markBufferAsChanged(BufferType bufferType);

private:
    std::vector<T> cpuBuffer;
    cl::Buffer gpuBuffer;
    BufferType type;
    size_t size;
    bool isSynchronized = false;
};

#endif // CPUGPUBUFFER_H
