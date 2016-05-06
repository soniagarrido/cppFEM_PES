QT += core
QT -= gui

CONFIG += c++11

TARGET = cppFEM_PES
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    bc_class.cpp \
    classelem_2d_tri_linear.cpp \
    ClassNodes.cpp \
    postprocess_class.cpp \
    read_files.cpp \
    solver.cpp

HEADERS += \
    bc_class.h \
    class_aux.h \
    classelem_2d_tri_linear.h \
    ClassNodes.h \
    postprocess_class.h \
    read_files.h \
    solver.h
