TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    stack.h \
    stackseq.h \
    input.h \
    calculator.h \
    tree/Tree.h \
    Scanner.h \
    parser.h \
    symboltable.h \
    HTable.h \
    List.h \
    Store.h \
    SymTab.h \
    FunTab.h

SOURCES += \
    stack.cpp \
    stackseq.cpp \
    input.cpp \
    main.cpp \
    calculator.cpp \
    tree/Tree.cpp \
    Scanner.cpp \
    parser.cpp \
    symboltable.cpp \
    List.cpp \
    Store.cpp \
    SymTab.cpp \
    HTable.cpp \
    FunTab.cpp
