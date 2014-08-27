#ifndef CLMANAGER_H
#define CLMANAGER_H

#include <memory>
#include <CL/cl.hpp>

class OpenCLManager
{
public:
    static OpenCLManager * GetInstance();
    cl::Context &GetDefaultContext();
    cl::CommandQueue & GetDefaultCommandQueue();

private:
    OpenCLManager();
    static std::unique_ptr<OpenCLManager> instance;
    cl::Context defaultContext;
    cl::CommandQueue defaultCommandQueue;
};

#endif // CLMANAGER_H
