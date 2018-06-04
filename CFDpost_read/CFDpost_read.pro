TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    cfd_post_face.cpp \
    dataio.cpp \
    get_neighbor.cpp

HEADERS += \
    define.h
