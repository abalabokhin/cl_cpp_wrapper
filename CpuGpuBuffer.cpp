#include "CpuGpuBuffer.h"

template <typename T>
CpuGpuBuffer<T>::CpuGpuBuffer(cl::Context context, BufferType bufferType, size_t bufferSize)
    :   type(bufferType), size(bufferSize)
{
    switch (bufferType) {
        case BufferType::CPU:
            cpuBuffer = QVector<T>(size);
            break;
        case BufferType::GPU:
            gpuBuffer = cl::Buffer(context, CL_MEM_READ_WRITE, size * sizeof(T));
    }
}

template <typename T>
T * CpuGpuBuffer<T>::getCpuBuffer(cl::CommandQueue &cq) {
    if (type == BufferType::GPU && !isSynchronized) {
        cq.enqueueReadBuffer(gpuBuffer, CL_TRUE, 0, size * sizeof(T), cpuBuffer.data());
    }
    return cpuBuffer.data();
}

template <typename T>
cl::Buffer & CpuGpuBuffer<T>::getGpuBuffer(cl::CommandQueue &cq) {
    if (type == BufferType::CPU && !isSynchronized) {
        cq.enqueueWriteBuffer(gpuBuffer, CL_TRUE, 0, size * sizeof(T), cpuBuffer.data());
    }
    return gpuBuffer;
}

template <typename T>
void CpuGpuBuffer<T>::markBufferAsChanged(BufferType bufferType) {
    type = bufferType;
}
