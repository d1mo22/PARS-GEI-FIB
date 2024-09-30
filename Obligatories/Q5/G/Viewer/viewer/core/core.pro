TEMPLATE    = lib
TARGET      = core
DEFINES     += CORE_LIBRARY  # See Qt Ref doc, "Creating Shared Libraries"

CONFIG      += release plugin
CONFIG      += build_all

INCLUDEPATH += include

DESTDIR     = $$(PWD)/../bin


MOC_DIR = build
OBJECTS_DIR = build
RCC_DIR = build

win32:INCLUDEPATH += E:/lib/glew-1.10.0/include/
win32:LIBS += -LE:/lib/glew-1.10.0/lib/Release/Win32
win32:LIBS += -lglew32

macx:LIBS +=  -install_name $$DESTDIR/libcore.dylib
HEADERS	+= include/*.h
SOURCES	+= src/*.cpp
