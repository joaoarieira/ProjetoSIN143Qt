#-------------------------------------------------
#
# Project created by QtCreator 2019-06-13T16:42:21
#
#-------------------------------------------------

QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

TARGET = ProjetoSIN143Qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 release

SOURCES += \
        crudprodutowindow.cpp \
        crudusuariowindow.cpp \
        fluxocaixa.cpp \
        loginwindow.cpp \
        main.cpp \
        mainwindow.cpp \
        md5.cpp \
        novoprodutowindow.cpp \
        novousuariowindow.cpp

HEADERS += \
        crudprodutowindow.h \
        crudusuariowindow.h \
        fluxocaixa.h \
        loginwindow.h \
        mainwindow.h \
        md5.h \
        novoprodutowindow.h \
        novousuariowindow.h

FORMS += \
        crudprodutowindow.ui \
        crudusuariowindow.ui \
        fluxocaixa.ui \
        loginwindow.ui \
        mainwindow.ui \
        novoprodutowindow.ui \
        novousuariowindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
