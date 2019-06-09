#-------------------------------------------------
#
# Project created by QtCreator 2019-05-05T23:40:07
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogViewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    logmodel.cpp \
    searchlogmodel.cpp \
    settingsdialog.cpp \
    configuration.cpp \
    filterdialog.cpp \
    newprojecwizardpage.cpp \
    project.cpp \
    newprojectwizard.cpp \
    projectattributeswizardpage.cpp \
    fieldmodel.cpp \
    fielddelegate.cpp \
    fieldview.cpp \
    field.cpp

HEADERS += \
        mainwindow.h \
    logmodel.h \
    searchlogmodel.h \
    settingsdialog.h \
    configuration.h \
    filterdialog.h \
    newprojecwizardpage.h \
    project.h \
    newprojectwizard.h \
    projectattributeswizardpage.h \
    fieldmodel.h \
    fielddelegate.h \
    fieldview.h \
    field.h

FORMS += \
        mainwindow.ui \
    settingsdialog.ui \
    filterdialog.ui \
    newprojecwizardpage.ui \
    projectattributeswizardpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
