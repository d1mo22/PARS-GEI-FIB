TEMPLATE   = lib

# CONFIG
CONFIG += plugin 
CONFIG += debug
CONFIG -= release
CONFIG += warn_on 
equals(QT_MAJOR_VERSION, 5): QT += opengl
equals(QT_MAJOR_VERSION, 6): QT += openglwidgets



# INPUTS 
INCLUDEPATH += include
INCLUDEPATH += ../core/include
INCLUDEPATH += ../interfaces

HEADERS += include/*.h 
SOURCES	+= src/*.cpp


# OUTPUTS
TARGET     = glwidget
DESTDIR = $$(PWD)/../bin
#message("will install in $$DESTDIR")

MOC_DIR = build
OBJECTS_DIR = build
RCC_DIR = build
QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/.\''

win32:INCLUDEPATH += E:/lib/glew-1.10.0/include/
win32:LIBS += -LE:/lib/glew-1.10.0/lib/Release/Win32
win32:LIBS += -lglew32

# GLEW
macx{
   LIBS +=  -L../bin/  -lcore -install_name $$DESTDIR/libglwidget.dylib
} else {
   LIBS += -Wl,--rpath-link=../bin -L../bin  -lGLU -lcore -lGL # Cal a linux, però no a Mac...
}

DEFINES += PLUGINGLWIDGET_LIBRARY   # see Qt docs, "Creating shared libraries"


