QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    replace.cpp \
    search.cpp

HEADERS += \
    mainwindow.h \
    replace.h \
    search.h

FORMS += \
    mainwindow.ui \
    replace.ui \
    search.ui

MAJOR_VERSION = 1
MINOR_VERSION = 0
DEFINES += \
    MAJOR_VERSION=$$MAJOR_VERSION \
    MINOR_VERSION=$$MINOR_VERSION


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

