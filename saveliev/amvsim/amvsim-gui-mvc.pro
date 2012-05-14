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
    Containers/NewContainerDialog.cpp \
    Containers/ContainerWidget.cpp \
    Containers/ContainerListView.cpp \
    Containers/ContainerListModel.cpp \
    Containers/ContainerDelegate.cpp \
    Containers/SwitchButtons.cpp \
    Services/ContainerParametersWidget.cpp \
    api/Parameter.cpp

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
    api/Service.h \
    Containers/NewContainerDialog.h \
    Containers/ContainerWidget.h \
    Containers/ContainerListView.h \
    Containers/ContainerListModel.h \
    Containers/ContainerDelegate.h \
    OptionsParameterWidget.h \
    Containers/SwitchButtons.h \
    Services/ContainerParametersWidget.h \
    api/Parameter.h

OTHER_FILES += \
    device.txt

FORMS += \
    Containers/NewContainerDialog.ui




















































































