#ifndef CPUGPUBUFFER_H
#define CPUGPUBUFFER_H

#include <vector>
#include <CL/cl.hpp>

enum class BufferType {
    NONE,
    CPU,
    GPU
};

template <typename T>
class CpuGpuBuffer {
public:
    CpuGpuBuffer(const cl::Context & context, size_t bufferSize)
    :   type(BufferType::NONE), size(bufferSize)
    {
        cpuBuffer = std::vector<T>(size);
        gpuBuffer = cl::Buffer(context, CL_MEM_READ_WRITE, size * sizeof(T));
    }

    size_t getSize() { return size; }

    T * getCpuBuffer(cl::CommandQueue &cq) {
        if (type == BufferType::GPU) {
            cq.enqueueReadBuffer(gpuBuffer, CL_TRUE, 0, size * sizeof(T), cpuBuffer.data());
        }
        type = BufferType::CPU;
        return cpuBuffer.data();
    }

    cl::Buffer & getGpuBuffer(cl::CommandQueue &cq) {
        if (type == BufferType::CPU) {
            cq.enqueueWriteBuffer(gpuBuffer, CL_TRUE, 0, size * sizeof(T), cpuBuffer.data());
        }
        type = BufferType::GPU;
        return gpuBuffer;
    }

private:
    std::vector<T> cpuBuffer;
    cl::Buffer gpuBuffer;
    BufferType type;
    size_t size;
};

#endif // CPUGPUBUFFER_H
