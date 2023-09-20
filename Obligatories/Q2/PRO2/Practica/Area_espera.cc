#include "Area_espera.hh"

Area_espera::Area_espera() {}


void Area_espera::llegir_area()
{
    int x;
    string s;
    cin >> x;
    for (int i = 0; i < x; ++i) {
        cin >> s;
        Prioridad p;
        ae[s] = p;
    }
}

void Area_espera::imprimir_area_espera() const
{
    for (auto it = ae.begin(); it != ae.end(); ++it) {
        cout << it->first << endl;
        it->second.escribir_jobs();
    }
}

void Area_espera::imprimir_prio(const string& s) const
{
    auto it = ae.find(s);
    if (it == ae.end()) cout << "error: no existe prioridad" << endl;
    else {
        Prioridad p = it->second;
        p.escribir_jobs();
    }
}

void Area_espera::añadir_prioridad(const string& id_prio)
{
    if (ae.find(id_prio) != ae.end()) cout << "error: ya existe prioridad" << endl;
    else {
        Prioridad p;
        ae[id_prio] = p;
    }
}

void Area_espera::eliminar_prioridad(const string& p)
{
    if (ae.find(p) == ae.end()) cout << "error: no existe prioridad" << endl;
    else if (ae[p].job_pendent()) cout << "error: prioridad con procesos" << endl;
    else {
        map<string, Prioridad>::iterator it = ae.find(p);
        ae.erase(it);
    }
}

void Area_espera::añadir_job(const string& s, const int& idj, const int& memj, const int& tj) {
    if (ae.find(s) == ae.end()) cout << "error: no existe prioridad" << endl;
    else if (ae[s].existe_job(idj)) cout << "error: ya existe proceso" << endl;
    else {
        Job j(idj, memj, tj);
        ae[s].añadir_job(idj, j);
    }
}

void Area_espera::enviar_job_cluster(int& n, Cluster& c)
{   
    map<string, Prioridad>::iterator it = ae.begin();
    while (it != ae.end() and n > 0) {
        it->second.enviar_prc(n, c);
        ++it;
    }
}