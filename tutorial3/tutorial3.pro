#-------------------------------------------------
#
# Project created by QtCreator 2014-09-30T16:22:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tutorial3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$quote(D:\libraries\opencv300a\include)\
               $$quote(D:\libraries\opencv300a\include\opencv2)

OPENCVLIB += $$quote(D:\libraries\opencv300a\lib)

CONFIG(debug, debug|release){
LIBS+= $$OPENCVLIB/opencv_world300d.lib\
       $$OPENCVLIB/opencv_ts300d.lib
}

CONFIG(release, debug|release){
LIBS+= $$OPENCVLIB/opencv_world300.lib\
       $$OPENCVLIB/opencv_ts300.lib
}
