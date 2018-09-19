QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += ordered
#TEMPLATE = subdirs
TEMPLATE = app

SOURCES +=  tst_testone.cpp

include(sdlpri.pri)
SUBDIRS += sdl-NoEverythingInMain
