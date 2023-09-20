#include "Procesador.hh"

Procesador::Procesador()
{
    mem = 0;
}

Procesador::Procesador(const int& memory)
{
    mem = mem_free = memory ;
    huecos[memory].insert(0);
    
}

int Procesador::consultar_memoria(const Job& j) const
{
    int p;
    auto it = huecos.lower_bound(j.consultar_mem());
    if (it == huecos.end()) {
        p = -1;
        return p;
    }
    return p = it->first;
}

int Procesador::free_mem() const
{
    return mem_free;
}

bool Procesador::existe_job(const int& id) const
{
    if (b.find(id) == b.end()) return false;
    return true;
}

bool Procesador::te_job() const 
{
    return b.empty();
}

void Procesador::imprimir_procesador() const
{
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << it->first << " ";
        it->second.imprimir_job();
        cout << endl;
    }
}

void Procesador::insertar_job(const Job& job)
{   
    int memory = job.consultar_mem();
    map<int,set<int>>::iterator it = huecos.lower_bound(memory);
    //int pos_h = *(prev(it->second.end()));
    int pos_h = *(it->second.begin());
    int tam_h = it->first;

    if (it->second.size() > 1) {
        it->second.erase(pos_h);
    }
    else {
        huecos.erase(it);
    }
    if (tam_h != memory) {
        tam_h -= memory;
        it = huecos.find(tam_h);
        if (it != huecos.end()) {
            it->second.insert(pos_h + memory);
        }
        else {
            set<int> s;
            s.insert(pos_h+memory);
            huecos.insert(make_pair(tam_h, s));
        }
    }
    b.insert(make_pair(job.consultar_id(), pos_h));
    m.insert(make_pair(pos_h, job));
    mem_free -= memory;
}

int Procesador::quants_jobs() const {
    return m.size();
}

void Procesador::eliminar_job(const int& idj)
{
    //map<int, int>
    map<int, int>::iterator it = b.find(idj);
    if (it == b.end()) {}
    else {
        //map<int, proces>
        map<int, Job>::iterator ita = m.find(it->second);
        map<int, Job>::iterator itb = ita;
        map<int, Job>::iterator itc = ita;
        mem_free += ita->second.consultar_mem();
        int pos = it->second;
        int mida = ita->second.consultar_mem();
        int pos_dalt = pos;
        int pos_baix = pos + mida;
        int mida_total = mida;
        int pos_total = pos;
        int mida_hueco_dalt = 0;
        int mida_hueco_baix = 0;

        ++itc;
        if (itc == m.end()) {
            if (pos + mida != mem) {
                pos_baix = pos + mida;
                mida_hueco_baix = mem - pos_baix;
                mida_total += mida_hueco_baix;
            }
        }
        else {
            pos_baix = pos + mida;
            mida_hueco_baix = itc->first - pos_baix;
            mida_total += mida_hueco_baix;
        }
        if (ita == m.begin()) {
            if (pos_dalt != 0) {
                mida_hueco_dalt = pos;
                pos_dalt = 0;
                mida_total += pos;
            }
        }
        else {
            --itb;
            pos_dalt = itb->first + itb->second.consultar_mem();
            if (pos_dalt != pos) {
                mida_hueco_dalt = pos - pos_dalt;
                mida_total += mida_hueco_dalt;
            }
        }
        pos_total = pos_dalt;
        if (mida_hueco_baix > 0) {
            map<int,set<int>>::iterator it_baix = huecos.find(mida_hueco_baix);
            set<int>::iterator it_baix2 = it_baix->second.find(pos_baix);
            it_baix->second.erase(it_baix2);
            if (it_baix->second.empty()) huecos.erase(it_baix);
        }
        if (mida_hueco_dalt > 0) {
            map<int,set<int>>::iterator it_dalt = huecos.find(mida_hueco_dalt);
            set<int>::iterator it2 = it_dalt->second.find(pos_dalt);
            it_dalt->second.erase(it2);
            if (it_dalt->second.empty()) huecos.erase(it_dalt);
        }

        map<int,set<int>>::iterator it_add = huecos.find(mida_total);
        if (it_add != huecos.end()) it_add->second.insert(pos_total);
        else {
            set<int> s;
            s.insert(pos_total);
            huecos.insert(make_pair(mida_total, s));
        }
        m.erase(ita);
        b.erase(it);
    }
}

void Procesador::pasar_temps(const int& tiempo) {
    auto it = m.begin();
    auto aux = it;
    int suma = 0;
    while (it != m.end()) {
        it->second.restar_temps(tiempo);
        it = aux;
        ++aux;
        if (it->second.consultar_temps() <= 0) {
            int id = it->second.consultar_id();
            eliminar_job(id);
        } 
        it = aux;
        ++suma;
    } 
}

void Procesador::compactar_mem()
{
    int suma = 0;
    huecos.clear();
    b.clear();
    map<int, Job> a;
    for (auto it = m.begin(); it != m.end(); ++it) {     
        a[suma] = it->second;
        b.insert(make_pair(it->second.consultar_id(), suma));
        suma += it->second.consultar_mem();
    }
    huecos[mem-suma].insert(suma);
    m = a;
}