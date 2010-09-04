#-------------------------------------------------
#
# Project created by QtCreator 2010-08-05T05:00:13
#
#-------------------------------------------------

QT += core gui

TARGET = OpenCV Qt Integration Demo
TEMPLATE = app
INCLUDEPATH += /opt/local/include/opencv
LIBS += -L/opt/local/lib -lcvaux -lcv -lhighgui -lcxcore
SOURCES += src/main.cpp\
        src/toplevelwindow.cpp\
        src/cvutil.cpp \
        src/cvwidget.cpp \
        src/cvimage.cpp \
    	src/imageprocessingthread.cpp \
    	src/cvimageprocessor.cpp \
    	src/cvlabel.cpp

HEADERS  += src/toplevelwindow.h src/cvutil.h src/cvwidget.h src/cvimage.h \
    	src/imageprocessingthread.h \
    	src/cvimageprocessor.h \
    	src/GlobalEnums.h \
    	src/cvlabel.h

FORMS    += src/toplevelwindow.ui
RESOURCES += resources.qrc
ICON = resources/z_black_on_white.icns

