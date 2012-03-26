# -------------------------------------------------
# Project created by QtCreator 2012-03-19T01:16:50
# -------------------------------------------------
QT += testlib
QT -= gui
TARGET = avmsim
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    Container.cpp \
    AndroidDevice.cpp \
    StorageDescriptor.cpp \
    tests.cpp
HEADERS += StorageDescriptor.h \
    Container.h \
    AndroidDevice.h \
    tests.h
