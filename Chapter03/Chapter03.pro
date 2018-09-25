QT -= gui
QT += concurrent

TARGET = Chapter03
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

include(qpm.pri)

SOURCES += \
    main.cpp \
    record.cpp

HEADERS += \
    record.h
