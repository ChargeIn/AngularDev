QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(libs/QLightTerminal/QLightTerminal.pri)

SOURCES += \
    parser/angular/typescript/chars.cpp \
    parser/angular/typescript/lexer.cpp \
    parser/angular/angularformatter.cpp \
    codeeditor.cpp \
    formattedtext.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    parser/angular/typescript/chars.h \
    parser/angular/typescript/lexer.h \
    parser/angular/angularformatter.h \
    codeeditor.h \
    formattedtext.h \
    formatter.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    styles/main.qss

DESTDIR = $$OUT_PWD
QMAKE_POST_LINK = $(COPY_DIR) $$PWD/styles $$DESTDIR

# Default rules for deployment.

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
