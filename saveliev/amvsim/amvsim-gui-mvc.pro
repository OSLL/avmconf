#-------------------------------------------------
#
# Project created by QtCreator 2012-04-08T15:44:57
#
#-------------------------------------------------

QT       += core gui

TARGET = AVMSimulator
TEMPLATE = app


SOURCES += main.cpp\
    api/StorageDescriptor.cpp \
    api/Container.cpp \
    api/AndroidDevice.cpp \
    api/Saver.cpp \
    ContainerDelegate.cpp \
    ContainerWidget.cpp \
    DeviceModel.cpp \
    MainWindow.cpp \
    CreateContainerDialog.cpp \
    ContainersListView.cpp \
    ErrorLabel.cpp \
    CreateContainerDialog2.cpp \
    CreateContainerDialog2.cpp

HEADERS  += \
    api/StorageDescriptor.h \
    api/Container.h \
    api/AndroidDevice.h \
    api/ContainerState.h \
    api/ContainerInfo.h \
    api/Saver.h \
    ContainerDelegate.h \
    ContainerWidget.h \
    ContainersListView.h \
    DeviceModel.h \
    MainWindow.h \
    CreateContainerDialog.h \
    ErrorLabel.h \
    CreateContainerDialog2.h

OTHER_FILES +=

FORMS += \
    CreateContainerDialog2.ui




















































































