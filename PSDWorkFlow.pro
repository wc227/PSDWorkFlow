#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T22:30:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PSDWorkFlow
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS\
    WINDOW

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        dlgworkflow.cpp \
    cbaritem.cpp \
    cgraphicsobjectitem.cpp \
    cgraphicsscene.cpp \
    citempropertydialog.cpp \
    cmypathitem.cpp \
    coutitem.cpp \
    cwidget.cpp \
    tpsdevts.cpp

HEADERS  += dlgworkflow.h \
    cbaritem.h \
    CGraphicsObjectItem.h \
    cgraphicsscene.h \
    citempropertydialog.h \
    cmypathitem.h \
    coutitem.h \
    cwidget.h \
    tpsdevts.h \
    Mems/mem/APPid.h \
    Mems/mem/AutoSaveFile.h \
    Mems/mem/cfgInc.h \
    Mems/mem/EvtDefines.h \
    Mems/mem/hwndInc.h \
    Mems/mem/logInc.h \
    Mems/mem/Mems.h \
    Mems/mem/MemsInc.h \
    Mems/mem/processInc.h \
    Mems/mem/psdABInc.h \
    Mems/mem/PSDdb.h \
    Mems/mem/PSDDogAppID.h \
    Mems/mem/PSDDogDef.h \
    Mems/mem/psdEvtInc.h \
    Mems/mem/PSDStructs.h \
    Mems/mem/sectionInc.h \
    Mems/mem/SoftDogDef.h

FORMS += \
    citempropertydialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Mems/ -lMems
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Mems/ -lMemsd

INCLUDEPATH += $$PWD/Mems
DEPENDPATH += $$PWD/Mems
