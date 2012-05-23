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
    api/Parameter.cpp \
    MainWindow.cpp \
    Elements/ErrorLabel.cpp \
    Dialogs/NewContainerDialog.cpp \
    Dialogs/ContainerDialog.cpp \
    Dialogs/DeviceParametersDialog.cpp \
    ParameterWidgets/ParameterWidget.cpp \
    ParameterWidgets/ParametersWidget.cpp \
    ParameterWidgets/OptionsParameterWidget.cpp \
    ParameterWidgets/DoubleParameterWithRangeWidget.cpp \
    ParameterWidgets/BoolParameterWidget.cpp \
    ContainerList/ContainerWidget.cpp \
    ContainerList/ContainerListView.cpp \
    ContainerList/ContainerListModel.cpp \
    ContainerList/ContainerDelegate.cpp \
    ContainerList/PowerButton.cpp \
    ContainerList/SwitchButton.cpp

HEADERS  += \
    api/StorageDescriptor.h \
    api/Container.h \
    api/AndroidDevice.h \
    api/ContainerState.h \
    api/ContainerInfo.h \
    api/Saver.h \
    api/NoSuchContainerException.h \
    api/Service.h \
    api/Parameter.h \
    api/IContainer.h \
    api/IDevice.h \
    MainWindow.h \
    Elements/ErrorLabel.h \
    Dialogs/NewContainerDialog.h \
    Dialogs/ContainerDialog.h \
    Dialogs/DeviceParametersDialog.h \
    ParameterWidgets/ParameterWidget.h \
    ParameterWidgets/ParametersWidget.h \
    ParameterWidgets/OptionsParameterWidget.h \
    ParameterWidgets/DoubleParameterWithRangeWidget.h \
    ParameterWidgets/BoolParameterWidget.h \
    ContainerList/ContainerWidget.h \
    ContainerList/ContainerListView.h \
    ContainerList/ContainerListModel.h \
    ContainerList/ContainerDelegate.h \
    ContainerList/PowerButton.h \
    ContainerList/SwitchButton.h

OTHER_FILES += \
    device.txt \
    Images/button-enabled.png \
    Images/button-disabled.png \

FORMS += \
    Dialogs/NewContainerDialog.ui




















































































