QT       -= gui core

TARGET = Chapter03
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

ROOT_DIR = $$absolute_path($$PWD)

DEFINES += QT_DEPRECATED_WARNINGS

include(qpm.pri)

SOURCES += \
    main.cpp
