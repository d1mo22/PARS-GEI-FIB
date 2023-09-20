#include <iostream>
#include <cmath>
using namespace std;

struct Punt {
    double x, y;
};

struct Cercle {
    Punt centre;
    double radi;
};

double distancia(const Punt& a, const Punt& b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void desplaca(Punt& p1, Punt& p2) {
    p1.x += p2.x;
    p1.y += p2.y;
}

void escala(Cercle& c, double esc) {
    c.radi *= esc; 
}

void desplaca(Cercle& c, const Punt& p) {
    c.centre.x += p.x;
    c.centre.y += p.y;
}

bool es_interior (const Punt& p, const Cercle& c) {
    return distancia(c.centre, p) < c.radi;
}

