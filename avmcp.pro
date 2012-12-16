#-------------------------------------------------
#
# Project created by QtCreator 2012-04-08T15:44:57
#
#-------------------------------------------------

QT       += core gui

TARGET = avmcp
TEMPLATE = app


SOURCES += main.cpp\
    api/Smartphone.cpp \
    MainWindow.cpp \
    api/Parameter.cpp \
    Views/ContainerWidget.cpp \
    Views/ContainerListView.cpp \
    Views/ContainerDelegate.cpp \
    Models/ContainerListModel.cpp \
    Elements/SwitchButtons.cpp \
    Elements/ErrorLabel.cpp \
    Dialogs/NewContainerDialog.cpp \
    Dialogs/ContainerParametersWidget.cpp \
    Dialogs/ContainerDialog.cpp \
    WPA/wpagui.cpp \
    WPA/userdatarequest.cpp \
    WPA/stringquery.cpp \
    WPA/scanresults.cpp \
    WPA/peers.cpp \
    WPA/networkconfig.cpp \
    WPA/eventhistory.cpp \
    WPA/addinterface.cpp \
    WPA/wpa_ctrl.c \
    WPA/common.c \
    WPA/wpa_debug.c \
    WPA/wpabuf.c \
    WPA/trace.c \
    WPA/os_unix.c

HEADERS  += \
    api/StorageDescriptor.h \
    api/Container.h \
    api/ContainerState.h \
    api/ContainerInfo.h \
    api/Saver.h \
    MainWindow.h \
    api/NoSuchContainerException.h \
    api/Service.h \
    api/Parameter.h \
    api/IContainer.h \
    api/IDevice.h \
    api/Smartphone.h \
    Views/ContainerWidget.h \
    Views/ContainerListView.h \
    Views/ContainerDelegate.h \
    Models/ContainerListModel.h \
    Elements/SwitchButtons.h \
    Elements/ErrorLabel.h \
    Dialogs/NewContainerDialog.h \
    Dialogs/ContainerParametersWidget.h \
    Dialogs/ContainerDialog.h \
    SupervisorListener.h \
    WPA/wpamsg.h \
    WPA/wpagui.h \
    WPA/userdatarequest.h \
    WPA/stringquery.h \
    WPA/scanresults.h \
    WPA/peers.h \
    WPA/networkconfig.h \
    WPA/eventhistory.h \
    WPA/addinterface.h \
    WPA/wpa_ctrl.h \
    WPA/includes.h \
    WPA/build_config.h \
    WPA/common.h \
    WPA/wpa_debug.h \
    WPA/os.h \
    WPA/wpabuf.h \
    WPA/trace.h

OTHER_FILES += \
    device.txt \

FORMS += \
    Dialogs/NewContainerDialog.ui \
    WPA/wpagui.ui \
    WPA/userdatarequest.ui \
    WPA/scanresults.ui \
    WPA/peers.ui \
    WPA/networkconfig.ui \
    WPA/eventhistory.ui

INCLUDEPATH += ./WPA/


















































































