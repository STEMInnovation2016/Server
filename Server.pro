
TEMPLATE = app
QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server

PRE_TARGETDEPS += 
QMAKE_EXTRA_TARGETS += sdk sdkclean
sdk.commands = make
sdkclean.commands = make clean

DEPENDPATH += .
INCLUDEPATH += .

DESTDIR=.
OBJECTS_DIR=gen_objs
MOC_DIR=gen_mocs

HEADERS += *.h

SOURCES += *.cpp

unix:LIBS += 

unix:QMAKE_CLEAN += -r $(OBJECTS_DIR) $${MOC_DIR}

