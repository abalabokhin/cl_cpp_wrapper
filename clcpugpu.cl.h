#ifndef CLCPUGPU_CL_H
#define CLCPUGPU_CL_H

#ifdef GPU_OPENCL
    #include "clgpu.h"
#endif
#ifndef GPU_OPENCL
    #include "clcpu.h"
#endif

#endif // CLCPUGPU_CL_H
