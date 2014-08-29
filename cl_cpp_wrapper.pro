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

SOURCES += \
    CpuGpuBuffer.cpp \
    clManager.cpp \
    KernelRunningSettings.cpp \
    clProgramWrapper.cpp

HEADERS += \
    clcpu.h \
    clgpu.h \
    clcpugpu.cl.h \
    CpuGpuBuffer.h \
    clManager.h \
    KernelRunningSettings.h \
    clKernelWrapper.h \
    clProgramWrapper.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:INCLUDEPATH += "/opt/AMDAPP/include"
