#include "clManager.h"

std::unique_ptr<OpenCLManager> OpenCLManager::instance;

OpenCLManager *OpenCLManager::GetInstance()
{
    if (!instance)
        instance = std::unique_ptr<OpenCLManager>(new OpenCLManager);
    return instance.get();
}

cl::Context &OpenCLManager::GetDefaultContext()
{
    return defaultContext;
}

cl::CommandQueue &OpenCLManager::GetDefaultCommandQueue()
{
    return defaultCommandQueue;
}

const std::vector<cl::Device> &OpenCLManager::GetDefaultDevices()
{
    return defaultDevice;
}

OpenCLManager::OpenCLManager()
{
    int defaultEntityNumber = 1;

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    for (auto & platform : platforms) {
        cl_context_properties cps[3] = {
            CL_CONTEXT_PLATFORM,
            (cl_context_properties)(platform)(),
            0
        };

        cl::Context context(CL_DEVICE_TYPE_ALL, cps);

        std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

        for (auto & device : devices) {
            int type = device.getInfo<CL_DEVICE_TYPE>();
            if (type == CL_DEVICE_TYPE_CPU) {
                auto name = device.getInfo<CL_DEVICE_NAME>();
                cl::CommandQueue queue = cl::CommandQueue(context, device);
                entities.push_back({device, queue, context, ClDeviceType::CPU, name});
            } else if (type == CL_DEVICE_TYPE_GPU) {
                auto name = device.getInfo<CL_DEVICE_NAME>();
                cl::CommandQueue queue = cl::CommandQueue(context, device);
                entities.push_back({device, queue, context, ClDeviceType::GPU, name});
            }
        }
    }

    if ((size_t)defaultEntityNumber < entities.size()) {
        defaultContext = entities[defaultEntityNumber].context;
        defaultCommandQueue = entities[defaultEntityNumber].queue;
        defaultDevice = {entities[defaultEntityNumber].device};
    }
}
