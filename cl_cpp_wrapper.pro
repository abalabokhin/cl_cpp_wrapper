#-------------------------------------------------
#
# Project created by QtCreator 2014-08-22T12:28:50
#
#-------------------------------------------------

QT       -= gui

TARGET = cl_cpp_wrapper
TEMPLATE = lib
CONFIG += staticlib
QMAKE_CXXFLAGS += -std=gnu++0x

DEFINES += "CL_HPP_TARGET_OPENCL_VERSION=120"
DEFINES += "CL_HPP_MINIMUM_OPENCL_VERSION=110"
DEFINES += "CL_HPP_CL_1_2_DEFAULT_BUILD"

SOURCES += \
    clManager.cpp \
    clProgramWrapper.cpp

HEADERS += \
    clcpu.h \
    clgpu.h \
    clcpugpu.cl.h \
    CpuGpuBuffer.h \
    clManager.h \
    KernelRunningSettings.h \
    clProgramWrapper.h \
    clGpuKernel.h \
    clCpuKernel.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:INCLUDEPATH += "$$(AMDAPPSDKROOT)/include"
unix:INCLUDEPATH += "/opt/AMDAPPSDK-3.0/include/"
