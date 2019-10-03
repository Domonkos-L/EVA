QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE      = app
HEADERS       = iconeditor.h \
    mainwindow.h \
    selectcolorbutton.h
SOURCES       = iconeditor.cpp \
                main.cpp \
                mainwindow.cpp \
                selectcolorbutton.cpp
RESOURCES     = iconeditor.qrc

