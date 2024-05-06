#include <MyProgressBar.h>
#include <QtMath>
#include <iostream>
using namespace std;

MyProgressBar::MyProgressBar(QWidget *parent = 0) : QProgressBar(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(oscilation()));
    ences = false;
}

void MyProgressBar::inicialize()
{
    wavelength = 0.5;
    phase = 0.0;

    double aux = wavelength * qSin(0 + phase);
    int result = int(aux * 100);
    QProgressBar::setValue(result);

    emit update_next(1, wavelength, phase);
    emit update_wavelength(0.5);
    emit update_phase(0.0);
}

void MyProgressBar::update_progressbar(int position, double a, double p)
{
    wavelength = a;
    phase = p;

    double aux = a * qSin(position + p);
    int result = int(aux * 100);
    QProgressBar::setValue(result);

    emit update_next(position + 1, a, p);
}

void MyProgressBar::update_value_WL(double wl)
{
    wavelength = wl;

    double aux = wavelength * qSin(0 + phase);
    int result = int(aux * 100);
    QProgressBar::setValue(result);

    emit update_progressbar(1, wavelength, phase);
}

void MyProgressBar::update_value_PH(double ph)
{
    phase = ph;

    double aux = wavelength * qSin(0 + phase);
    int result = int(aux * 100);
    QProgressBar::setValue(result);

    emit update_progressbar(1, wavelength, phase);
}

void MyProgressBar::timer_ences()
{
    ences = !ences;
    if (ences)
        timer.start(100);
    else
        timer.stop();
}

void MyProgressBar::oscilation()
{
    phase += 0.1;
    update_progressbar(0, wavelength, phase);
}