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

    CpuGpuBuffer(const cl::Context & context, const cl::CommandQueue &cq, size_t bufferSize, T const & defaultValue)
    :   size(bufferSize), defaultCq(&cq)
    {
        cpuBuffer = std::vector<T>(size, defaultValue);
        gpuBuffer = cl::Buffer(context, CL_MEM_READ_WRITE, size * sizeof(T));
        defaultCq->enqueueWriteBuffer(gpuBuffer, CL_TRUE, 0, size * sizeof(T), cpuBuffer.data());
    }

    CpuGpuBuffer() {}

    size_t getSize() { return size; }

    CpuGpuBuffer<T> CopyBuffer(const cl::Context & context) {
        CpuGpuBuffer<T> result(context, *defaultCq, size);
        result.type = type;
        if (type == BufferType::GPU) {
            defaultCq->enqueueCopyBuffer(getGpuBuffer(), result.getGpuBuffer(), 0, 0, size * sizeof(T));
        } else {
            result.cpuBuffer = cpuBuffer;
        }
        return result;
//        if (type == BufferType::GPU) {
//            defaultCq->enqueueReadBuffer(gpuBuffer, CL_TRUE, 0, size * sizeof(T), cpuBuffer.data());
//        }
//        type = BufferType::CPU;
//        return cpuBuffer.data();
    }

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

    void setGpuBuffer(cl::Buffer & newGpuBuffer) {
        type = BufferType::GPU;
        gpuBuffer = newGpuBuffer;
    }

private:
    std::vector<T> cpuBuffer;
    cl::Buffer gpuBuffer;
    BufferType type = BufferType::NONE;
    size_t size = 0;
    const cl::CommandQueue * defaultCq;
};

#endif // CPUGPUBUFFER_H
