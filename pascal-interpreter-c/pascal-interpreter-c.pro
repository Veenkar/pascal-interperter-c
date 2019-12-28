TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(pascal-interpreter-c-sources.pri)

SOURCES += \
        main.c

DISTFILES += \
    interpreter.py

