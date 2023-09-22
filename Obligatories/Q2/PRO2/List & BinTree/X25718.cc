#include "LlistaIOEstudiant.hh"
#include "solution.hh"

void esborra_tots(list<Estudiant> &t, int x) 
{
    list<Estudiant>::const_iterator it = t.begin();
    while (it != t.end()) {
        Estudiant e = *it;
        if (e.consultar_DNI() == x) it = t.erase(it);
        else ++it;
    }
}