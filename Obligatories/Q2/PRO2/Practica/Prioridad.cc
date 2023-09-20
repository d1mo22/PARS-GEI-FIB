#include "Prioridad.hh"

Prioridad::Prioridad() 
{
    enviados = 0;
    rechazos = 0;
}

bool Prioridad::existe_job(const int& idj) const 
{
    if (m.find(idj) == m.end()) return false;
    else return true;
}

bool Prioridad::job_pendent() const
{
    if (l.empty()) return false;
    return true;
}

void Prioridad::añadir_job(const int& idj, const Job& j) 
{   
    m[idj] = j;
    l.push_back(j);
}

void Prioridad::escribir_jobs() const
{
    auto itr = l.begin();
    for (auto it = l.begin(); it != l.end(); ++it) {
        int id = it->consultar_id();
        Job j = m.at(id);
        j.imprimir_job();
        cout << endl;
        }
    cout << enviados << " " << rechazos << endl;
}

void Prioridad::enviar_prc(int& n, Cluster& c) {
    list<Job>::iterator it = l.begin();
    int mida = l.size();
    while (n > 0 and mida > 0) {
        if (c.job_enviat(*it)) {
            it = l.erase(it);
            ++enviados;
            --n;
        }
        else {
            Job j = *it;
            l.erase(it);
            l.push_back(j);
            ++rechazos;
            it = l.begin();
        }
        --mida;
    }
}