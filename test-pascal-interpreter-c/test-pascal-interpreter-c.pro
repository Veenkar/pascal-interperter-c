include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
    tst_pascal_token.h

SOURCES += \
        main.C

include(../pascal-interpreter-c/pascal-interpreter-c-sources.pri)

DISTFILES +=
