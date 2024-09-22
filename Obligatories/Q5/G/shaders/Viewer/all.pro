TEMPLATE=subdirs
SUBDIRS= viewer plugins
CONFIG += ordered
CONFIG += silent

plugins.depends += viewer/bin/libglwidget.so
plugins.depends += viewer/bin/libcore.so
