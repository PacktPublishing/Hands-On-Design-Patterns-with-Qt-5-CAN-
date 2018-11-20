QT       +=  core widgets

TARGET = Ch11Spec
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

ROOT_DIR = $$absolute_path($$PWD)

DEFINES += QT_DEPRECATED_WARNINGS

include(qpm.pri)

SOURCES += \
    main.cpp
