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
    CpuGpuBuffer(const cl::Context & context, const cl::CommandQueue &cq, size_t bufferSize)
    :   size(bufferSize), defaultCq(&cq)
    {
        cpuBuffer = std::vector<T>(size);
        gpuBuffer = cl::Buffer(context, CL_MEM_READ_WRITE, size * sizeof(T));
    }

    CpuGpuBuffer() {}

    size_t getSize() { return size; }

    T * getCpuBuffer() {
        if (type == BufferType::GPU) {
            defaultCq->enqueueReadBuffer(gpuBuffer, CL_TRUE, 0, size * sizeof(T), cpuBuffer.data());
        }
        type = BufferType::CPU;
        return cpuBuffer.data();
    }

    cl::Buffer & getGpuBuffer() {
        if (type == BufferType::CPU) {
            defaultCq->enqueueWriteBuffer(gpuBuffer, CL_TRUE, 0, size * sizeof(T), cpuBuffer.data());
        }
        type = BufferType::GPU;
        return gpuBuffer;
    }

private:
    std::vector<T> cpuBuffer;
    cl::Buffer gpuBuffer;
    BufferType type = BufferType::NONE;
    size_t size = 0;
    const cl::CommandQueue * defaultCq;
};

#endif // CPUGPUBUFFER_H
