// main.cpp
#include <QApplication>
#include "Sinus.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Sinus form;
    form.show();
    return app.exec();
}