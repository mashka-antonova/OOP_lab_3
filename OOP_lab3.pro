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
    operation_factory.cpp \
    shunting_yard.cpp \
    token.cpp \
    token_creator.cpp \
    tokenizer.cpp \
    tokenizer_provider.cpp \
    unary_operator.cpp \
    unary_operator_factory.cpp

HEADERS += \
    add_operation.h \
    binary_operator.h \
    binary_operator_factory.h \
    cos_operation.h \
    ctg_operation.h \
    devide_operation.h \
    i_binary_operation.h \
    i_operation.h \
    i_unary_operation.h \
    mainwindow.h \
    multiply_operation.h \
    number.h \
    number_factory.h \
    operation_factory.h \
    reciprocal_operation.h \
    shunting_yard.h \
    sin_operation.h \
    sqrt_operation.h \
    subtract_operation.h \
    tg_operation.h \
    token.h \
    token_creator.h \
    token_factory.h \
    tokenizer.h \
    tokenizer_error.h \
    tokenizer_provider.h \
    unary_minus_operation.h \
    unary_operator.h \
    unary_operator_factory.h \
    unary_plus_operation.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
