QT       +=  core widgets

TARGET = Chapter07
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

include(qpm.pri)

SOURCES += \
    main.cpp \
    messagequeue.cpp \
    logger.cpp \
    message.cpp

HEADERS += \
    messagequeue.h \
    logger.h \
    message.h
