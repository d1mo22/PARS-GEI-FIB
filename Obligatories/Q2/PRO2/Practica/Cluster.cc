/** @file Cluster.cc
    @brief Código de la clase Cluster
 
*/
#include "Cluster.hh"

Cluster::Cluster() {}

void Cluster::configurar_cluster() {
    mp.clear();
    c = BinTree<string>();
    leer_bintree(c, mp);
}

void Cluster::leer_bintree(BinTree<string>& c, map<string, Procesador>& mp) 
{
    string s;
    cin >> s;
    if (s != "*") {
        int memory;
        cin >> memory;
        mp[s] = Procesador(memory);
        BinTree<string> esquerra, dreta;
        leer_bintree(esquerra, mp);
        leer_bintree(dreta, mp);
        c = BinTree<string> (s, esquerra, dreta);
    }
    else return;
}

void Cluster::poda(string& id)
{   
    if (mp.find(id) == mp.end()) cout << "error: no existe procesador" << endl;
    else if (c.value() == id) cout << "error: se intenta borrar la raiz" << endl;
    else {
        int jobs = 0;
        int prc = 0;
        i_poda(c, mp, id, prc, jobs);
        cout << "Poda" << " " << prc << " " << jobs << endl;
    }
    
}

void Cluster::i_poda(BinTree<string>& t, map<string, Procesador>& mp, const string& id, int& prc, int& jobs)
{
    if (t.empty()) return;

    if (t.value() == id) {
        elimina_prc(t, mp, prc, jobs);
        t = BinTree<string>();
    }
    else {
        BinTree<string> left = t.left();
        BinTree<string> right = t.right();

        i_poda(left, mp, id, prc, jobs);
        i_poda(right, mp, id, prc, jobs);

        t = BinTree<string>(t.value(), left, right);
    }
}

void Cluster::elimina_prc(BinTree<string>& t, map<string, Procesador>& mp, int& prc, int& jobs) 
{
    if (not t.empty()){
        prc += 1;
        auto it = mp.find(t.value());
        jobs += it->second.quants_jobs();
        mp.erase(it);

        BinTree<string> left = t.left();
        BinTree<string> right = t.right();

        elimina_prc(left, mp, prc, jobs);
        elimina_prc(right, mp, prc, jobs);
    }
}

void Cluster::insertar_cluster(const string& p)
{
    BinTree<string> aux;
    map<string,Procesador> help;
    leer_bintree(aux, help);
    map<string, Procesador>::iterator it = mp.find(p);
    if (it == mp.end()) cout << "error: no existe procesador" << endl;
    else if (not it->second.te_job()) cout << "error: procesador con procesos" << endl;
    else if (procesador_aux(p)) cout << "error: procesador con auxiliares" << endl;
    else {
        insertar_bintree(c, p, aux);    
        insertar_mapa(mp, help, p);
    }
}

void Cluster::insertar_mapa(map<string,Procesador>& p, map<string,Procesador>& nuevo, const string& s) 
{
    p.erase(s);
    p.insert(nuevo.begin(), nuevo.end());
    nuevo.clear();
}

void Cluster::insertar_bintree(BinTree<string>& a,const string& id, const BinTree<string>& nuevo) {
    if (a.empty()) return;
    if (a.value() == id) {

        a = BinTree<string>(nuevo.value(), nuevo.left(), nuevo.right());
        return;
    }
    BinTree<string> derecha, izquierda;
    derecha = a.right();
    izquierda = a.left();
    insertar_bintree(izquierda, id, nuevo);
    insertar_bintree(derecha, id, nuevo);
    a = BinTree<string> (a.value(), izquierda, derecha);
}

void Cluster::añadir_job_procesador(const string& s, const int& idj, const Job& j)
{
    if (mp.find(s) == mp.end()) cout << "error: no existe procesador" << endl;
    else if (mp[s].existe_job(idj)) cout << "error: ya existe proceso" << endl;
    else if (mp[s].consultar_memoria(j) == -1) cout << "error: no cabe proceso" << endl;
    else {
        mp[s].insertar_job(j);
    }
}

void Cluster::eliminar_job_procesador(const string& s,const int& idj)
{
    if (mp.find(s) == mp.end()) cout << "error: no existe procesador" << endl;
    else if (not mp[s].existe_job(idj)) cout << "error: no existe proceso" << endl;
    else {
        mp[s].eliminar_job(idj);
    }
}

void Cluster::avanzar_tiempo(const int& temps)
{
    for (map<string, Procesador>::iterator it = mp.begin(); it != mp.end(); ++it) {
        it->second.pasar_temps(temps);
    }
}

void Cluster::compactar_memoria_cluster()
{
    for (map<string, Procesador>::iterator it = mp.begin(); it != mp.end(); ++it) {
        it->second.compactar_mem();
    }
}

void Cluster::compactar_memoria(const string& s) {
    map<string, Procesador>::iterator it = mp.find(s);
    if (it == mp.end()) cout <<"error: no existe procesador" << endl;
    else {
        it->second.compactar_mem();
    } 
}

void Cluster::escribir_cluster() const
{   
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        cout << it->first << endl;
        it->second.imprimir_procesador();
    }
}

void Cluster::estructura_cluster() const
{
    estructura(c); cout << endl;
}

void Cluster::estructura(const BinTree<string>& c) const
{
    if (c.empty()) cout << " ";
    else {
        cout <<"(" << c.value();
        estructura(c.left());
        estructura(c.right());
        cout << ")";
    }
}

void Cluster::imprimir_prc(const string& s) const
{   
    auto it = mp.find(s);
    if (it == mp.end()) cout <<"error: no existe procesador" << endl;
    else {
        it->second.imprimir_procesador();
    } 
}

bool Cluster::procesador_aux(const string& s) const
{
    return te_fills(c, s);
}

bool Cluster::te_fills(const BinTree<string>& a, const string& id) const
{
    if (a.empty()) return false;
    if (a.value() == id) return (!a.left().empty() or !a.right().empty());
    BinTree<string> derecha, izquierda;
    return (te_fills(a.right(), id) or te_fills(a.left(), id));
}

bool Cluster::job_enviat(const Job& job) {
    map<string, Procesador>::iterator it = mp.end();
    Compare comp;
    comp.espai_ajd = -1;
    int profundidad = 0;
    if (enviar_prc_recursiu(c, job, it, comp, profundidad)) {
        it->second.insertar_job(job);
        return true;
    }
    return false;
}

bool Cluster::enviar_prc_recursiu(const BinTree<string>& c, const Job& job, map<string, Procesador>::iterator& it_best, Compare& comp, int& profunditat)
{
    if (c.empty()) return false;
    else {
        map<string, Procesador>::iterator it_actual = mp.find(c.value());
        int x = best_prc(job, comp, it_actual, profunditat);
        if (x == 1) it_best = it_actual;
        ++profunditat;
        enviar_prc_recursiu(c.left(), job, it_best, comp, profunditat);
        enviar_prc_recursiu(c.right(), job, it_best, comp, profunditat);
        --profunditat;
        if (comp.espai_ajd != -1) return true;
        return false;
    }
}

int Cluster::best_prc(const Job& job, Compare& comp_best, map<string, Procesador>::iterator& it_actual, int& profunditat)
{
    //Millor prc 0
    //Actual prc 1
    int best_prc = 0;
    int memory = it_actual->second.consultar_memoria(job);
    if (not it_actual->second.existe_job(job.consultar_id())) {
        if (memory != -1) {
            if (memory < comp_best.espai_ajd) {
                best_prc = 1;
            }
            else if (memory == comp_best.espai_ajd) {
                if (it_actual->second.free_mem() > comp_best.free_mem) {
                    best_prc = 1;
                }
                else if (it_actual->second.free_mem()  == comp_best.free_mem) {
                    if (profunditat < comp_best.profunditat) {
                        best_prc = 1;
                    }
                }
            }
        }
        if (best_prc == 1) {
            comp_best.espai_ajd = memory;
            comp_best.free_mem = it_actual->second.free_mem();
            comp_best.profunditat = profunditat;
        }
        else if (comp_best.espai_ajd == -1) {
            comp_best.espai_ajd = memory;
            comp_best.free_mem = it_actual->second.free_mem();
            comp_best.profunditat = profunditat;
            best_prc = 1;
        }
    }
    return best_prc;
}
