QT += widgets
CONFIG += c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = BookCatalog

SOURCES += \
    src/main.cpp \
    src/windows/mainwindow.cpp

HEADERS += \
    src/windows/mainwindow.h

INCLUDEPATH += src/windows

RESOURCES += resources/resources.qrc