#ifndef CLMANAGER_H
#define CLMANAGER_H

#include <memory>
#include <CL/cl.hpp>

enum class ClDeviceType {CPU, GPU};

struct OpenCLEntity {
    cl::Device device;
    cl::CommandQueue queue;
    cl::Context context;
    ClDeviceType deviceType;
    std::string name;
};

class OpenCLManager
{
public:
    static OpenCLManager * GetInstance();
    cl::Context &GetDefaultContext();
    cl::CommandQueue & GetDefaultCommandQueue();
    std::vector<cl::Device> const & GetDefaultDevices();

private:
    OpenCLManager();
    static std::unique_ptr<OpenCLManager> instance;
    std::vector<OpenCLEntity> entities;
    cl::Context defaultContext;
    cl::CommandQueue defaultCommandQueue;
    std::vector<cl::Device> defaultDevice;
};

#endif // CLMANAGER_H
