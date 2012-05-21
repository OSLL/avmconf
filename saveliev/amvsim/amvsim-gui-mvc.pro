#-------------------------------------------------
#
# Project created by QtCreator 2012-04-08T15:44:57
#
#-------------------------------------------------

QT       += core gui

TARGET = AVMSimulator
TEMPLATE = app


SOURCES += main.cpp\
    api/Container.cpp \
    api/AndroidDevice.cpp \
    api/Saver.cpp \
    MainWindow.cpp \
    api/Parameter.cpp \
    Views/ContainerWidget.cpp \
    Views/ContainerListView.cpp \
    Views/ContainerDelegate.cpp \
    Models/ContainerListModel.cpp \
    Elements/ErrorLabel.cpp \
    Dialogs/NewContainerDialog.cpp \
    Dialogs/ContainerDialog.cpp \
    Views/ParametersWidget.cpp \
    Dialogs/DeviceParametersDialog.cpp

HEADERS  += \
    api/StorageDescriptor.h \
    api/Container.h \
    api/AndroidDevice.h \
    api/ContainerState.h \
    api/ContainerInfo.h \
    api/Saver.h \
    MainWindow.h \
    api/NoSuchContainerException.h \
    api/Service.h \
    api/Parameter.h \
    api/IContainer.h \
    api/IDevice.h \
    Views/ContainerWidget.h \
    Views/ContainerListView.h \
    Views/ContainerDelegate.h \
    Models/ContainerListModel.h \
    Elements/ErrorLabel.h \
    Dialogs/NewContainerDialog.h \
    Dialogs/ContainerDialog.h \
    Views/ParametersWidget.h \
    Dialogs/DeviceParametersDialog.h

OTHER_FILES += \
    device.txt

FORMS += \
    Dialogs/NewContainerDialog.ui




















































































