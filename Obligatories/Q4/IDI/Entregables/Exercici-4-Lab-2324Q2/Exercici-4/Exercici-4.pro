TEMPLATE    = app
QT         += opengl widgets openglwidgets

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH += ./Model

FORMS += MyForm.ui

HEADERS += MyForm.h LL4GLWidget.h MyGLWidget.h

SOURCES += main.cpp  MyForm.cpp \
        LL4GLWidget.cpp MyGLWidget.cpp ./Model/model.cpp


