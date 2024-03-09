TEMPLATE    = app
QT         += opengl widgets openglwidgets

INCLUDEPATH +=  /user/include/glm

FORMS += MyForm.ui

HEADERS += MyForm.h MyGLWidget.h

SOURCES += main.cpp \
        MyForm.cpp MyGLWidget.cpp
