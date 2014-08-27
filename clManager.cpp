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

OpenCLManager::OpenCLManager()
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl_context_properties cps[3] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)(platforms[0])(),
        0
    };

    defaultContext = cl::Context(CL_DEVICE_TYPE_GPU, cps);
    // Get a list of devices on this platform
    std::vector<cl::Device> devices = defaultContext.getInfo<CL_CONTEXT_DEVICES>();
    // Create a command queue and use the first device
    defaultCommandQueue = cl::CommandQueue(defaultContext, devices[0]);
}
