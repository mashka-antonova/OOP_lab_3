QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    binary_operator.cpp \
    binary_operator_factory.cpp \
    main.cpp \
    mainwindow.cpp \
    number.cpp \
    number_factory.cpp \
    token.cpp \
    token_creator.cpp \
    tokenizer.cpp \
    tokenizer_dependency_provider.cpp \
    unary_operator.cpp \
    unary_operator_factory.cpp

HEADERS += \
    binary_operator.h \
    binary_operator_factory.h \
    mainwindow.h \
    number.h \
    number_factory.h \
    token.h \
    token_creator.h \
    token_factory.h \
    tokenizer.h \
    tokenizer_dependency_provider.h \
    tokenizer_error.h \
    unary_operator.h \
    unary_operator_factory.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
