include(gtest_dependency.pri)

TEMPLATE = app
#CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

CONFIG += c++1z
QMAKE_CXXFLAGS += -std=c++17

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14

    QMAKE_MAC_SDK = macosx10.14

win32 {
    QMAKE_CXXFLAGS += -std:c++17 -Zc:__cplusplus
}

HEADERS += \
    tst_testproject.h \
    primefactors.h

SOURCES += \
        main.cpp \
    tst_testproject.cpp \
    primefactors.cpp
