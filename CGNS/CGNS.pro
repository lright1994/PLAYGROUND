TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += \
    cgns-3.2.1/include \
    cgns-3.2.1/include/adf

SOURCES += \
        main.cpp \
    main.cpp \
    cgns-3.2.1/src/ADF_interface.c \
    cgns-3.2.1/src/ADF_internals.c \
    cgns-3.2.1/src/cgns_error.c \
    cgns-3.2.1/src/cgns_internals.c \
    cgns-3.2.1/src/cgns_io.c \
    cgns-3.2.1/src/cgnslib.c \
    cgnsclass.cpp

HEADERS += \
    cgns-3.2.1/include/adf/ADF.h \
    cgns-3.2.1/include/adf/ADF_fbind.h \
    cgns-3.2.1/include/adf/ADF_internals.h \
    cgns-3.2.1/include/cg_malloc.h \
    cgns-3.2.1/include/cgns_header.h \
    cgns-3.2.1/include/cgns_io.h \
    cgns-3.2.1/include/cgnslib.h \
    cgns-3.2.1/include/cgnstypes.h \
    cgns-3.2.1/include/fortran_macros.h \
    cgnsclass.h
