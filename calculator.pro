TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    stack.h \
    stackseq.h \
    input.h \
    calculator.h

SOURCES += \
    stack.cpp \
    stackseq.cpp \
    input.cpp \
    main.cpp \
    calculator.cpp
