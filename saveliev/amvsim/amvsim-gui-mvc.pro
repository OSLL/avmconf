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
    ErrorLabel.cpp \
    Services/ServiceView.cpp \
    Services/ServiceModel.cpp \
    Services/ServiceListView.cpp \
    Services/ServiceListModel.cpp \
    Containers/NewContainerDialog.cpp \
    Containers/ContainerWidget.cpp \
    Containers/ContainerListView.cpp \
    Containers/ContainerListModel.cpp \
    Containers/ContainerDelegate.cpp \
    api/ServiceInfo.cpp \
    Containers/SwitchButtons.cpp

HEADERS  += \
    api/StorageDescriptor.h \
    api/Container.h \
    api/AndroidDevice.h \
    api/ContainerState.h \
    api/ContainerInfo.h \
    api/Saver.h \
    MainWindow.h \
    ErrorLabel.h \
    NewContainerDialog.h \
    api/NoSuchContainerException.h \
    api/ServiceInfo.h \
    api/Service.h \
    Services/ServiceView.h \
    Services/ServiceModel.h \
    Services/ServiceListView.h \
    Services/ServiceListModel.h \
    Containers/NewContainerDialog.h \
    Containers/ContainerWidget.h \
    Containers/ContainerListView.h \
    Containers/ContainerListModel.h \
    Containers/ContainerDelegate.h \
    OptionsParameterWidget.h \
    Containers/SwitchButtons.h

OTHER_FILES += \
    device.txt

FORMS += \
    Containers/NewContainerDialog.ui




















































































