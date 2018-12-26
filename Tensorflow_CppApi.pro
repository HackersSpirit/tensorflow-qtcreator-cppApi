QT += core
QT -= gui

CONFIG += c++11

TARGET = Tensorflow_CppApi
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# Provide the link to the libtensorflow.dll file
win32: LIBS += -L$$PWD/../tensorflow_1.8/lib/ -ltensorflow

# Link to the include files
INCLUDEPATH += $$PWD/../tensorflow_1.8/lib/include
DEPENDPATH += $$PWD/../tensorflow_1.8/lib/include

#Below include path for opencv release library files


