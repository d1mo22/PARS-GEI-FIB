TEMPLATE    = app
QT         += opengl widgets openglwidgets

INCLUDEPATH +=  /usr/include/glm  \
                ./Model 

FORMS += MyForm.ui

HEADERS += MyForm.h LL2GLWidget.h MyGLWidget.h

SOURCES += main.cpp MyForm.cpp \
           LL2GLWidget.cpp MyGLWidget.cpp  \
           ./Model/model.cpp
