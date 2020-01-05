
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/psc_interpreter.h \
    $$PWD/psc_lexer.h \
    $$PWD/psc_token.h

SOURCES += \
    $$PWD/psc_interpreter.c \
    $$PWD/psc_lexer.c \
    $$PWD/psc_token.c

DISTFILES += \
    $$PWD/interpreter.py \
    $$PWD/template.txt
