TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    stack.h \
    #stackseq.h \
    input.h \
    calculator.h \
    Tree.h \
    Scanner.h \
    parser.h \
    HTable.h \
    List.h \
    Store.h \
    SymTab.h \
    FunTab.h \
    dynarray.h \
    StrBuf.h

SOURCES += \
    #stack.cpp \
    #stackseq.cpp \
    input.cpp \
    main.cpp \
    calculator.cpp \
    Tree.cpp \
    Scanner.cpp \
    parser.cpp \
    Store.cpp \
    SymTab.cpp \
    HTable.cpp \
    FunTab.cpp \
    StrBuf.cpp
