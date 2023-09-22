#include "Job.hh"

Job::Job()
{
    t = 0;
    mem = 0;
}

Job::Job(const int& idj, const int& memj,const int& tj)
{
    id = idj;
    mem = memj;
    t = tj;
}

int Job::consultar_mem() const
{
    return mem;
}

int Job::consultar_temps() const 
{
    return t;
}

int Job::consultar_id() const
{
    return id;
}

void Job::imprimir_job() const 
{
    cout << id << " " << mem << " " << t;
}

void Job::restar_temps(const int& temps) 
{
    t -=temps;
}