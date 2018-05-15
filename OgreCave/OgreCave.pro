TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

OGRE_V110_VC15 = E:\ENVS\OgreSDK_vc15_v1-10-11\\snapshot


SOURCES += main.cpp \
    ogremain.cpp \
    main.cpp

HEADERS += \
    ogremain.h


INCLUDEPATH +=$${OGRE_V110_VC15}\\include\\OGRE
INCLUDEPATH +=$${OGRE_V110_VC15}\\include\\OGRE\\Bites
INCLUDEPATH +=$${OGRE_V110_VC15}\\include\\OGRE\\RTShaderSystem
INCLUDEPATH +=$${OGRE_V110_VC15}\\SDL2-2.0.8\\include

LIBS *= user32.lib
LIBS +=-L$${OGRE_V110_VC15}\\lib
LIBS +=-L$${OGRE_V110_VC15}\\lib\\OGRE

debug {
    TARGET = $$join(TARGET,,,d)
    LIBS *= -lOgreMain -lOgreBites -lOgreRTShaderSystem
}
release {
    LIBS *= -lOgreMain -lOgreBites -lOgreRTShaderSystem
}



