QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(libs/QLightTerminal/QLightTerminal.pri)

SOURCES += \
    angular/chars.cpp \
    angular/lexer.cpp \
    angular/parser.cpp \
    estree/estree.cpp \
    angularformatter.cpp \
    codeeditor.cpp \
    formattedtext.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    angular/chars.h \
    angular/lexer.h \
    angular/parser.h \
    estree/estree.h \
    estree/types.h \
    angularformatter.h \
    codeeditor.h \
    formattedtext.h \
    formatter.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
