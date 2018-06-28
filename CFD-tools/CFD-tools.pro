TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tri_of_STL.cpp \
    kd_tree.cpp

HEADERS += \
    define.h \
    kd_tree.h \
    thirdparty/nanoflann/include/nanoflann.hpp
