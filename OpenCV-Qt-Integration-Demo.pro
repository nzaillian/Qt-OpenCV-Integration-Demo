#-------------------------------------------------
#
# Project created by QtCreator 2010-08-05T05:00:13
#
#-------------------------------------------------

QT += core gui

TARGET = OpenCV-Qt-Integration-Demo
TEMPLATE = app
INCLUDEPATH += /opt/local/include/opencv
LIBS += -L/opt/local/lib -lcvaux -lcv -lhighgui -lcxcore
SOURCES += main.cpp\
        toplevelwindow.cpp\
        cvutil.cpp \
        cvwidget.cpp \
        cvimage.cpp \
    imageprocessingthread.cpp \
    cvimageprocessor.cpp \
    cvlabel.cpp

HEADERS  += toplevelwindow.h cvutil.h cvwidget.h cvimage.h \
    imageprocessingthread.h \
    cvimageprocessor.h \
    GlobalEnums.h \
    cvlabel.h

FORMS    += toplevelwindow.ui
RESOURCES += resources.qrc
