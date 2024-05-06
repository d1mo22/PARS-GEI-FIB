#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget *parent):QLineEdit(parent) {
    connect(this, SIGNAL(returnPressed()), this, SLOT(tractaReturn()));
}

void MyLineEdit::tractaReturn() {
    emit returnPressed(text());
}