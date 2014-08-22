#-------------------------------------------------
#
# Project created by QtCreator 2014-08-22T12:28:50
#
#-------------------------------------------------

QT       -= gui

TARGET = cl_cpp_wrapper
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS += \
    clcpu.h \
    clgpu.h \
    clcpugpu.cl.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:INCLUDEPATH += "/opt/AMDAPP/include"
