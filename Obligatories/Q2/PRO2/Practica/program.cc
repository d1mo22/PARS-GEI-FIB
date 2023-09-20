#include "Area_espera.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#endif


using namespace std;

int main() {
    Cluster c;
    c.configurar_cluster();
    Area_espera area;
    area.llegir_area();
    string comando;
    cin >> comando;
    while (comando != "fin") {
    //1 
        if (comando == "configurar_cluster" or comando == "cc") {
            cout << '#' << comando << endl;
            c.configurar_cluster();
        }
    //2
        else if (comando == "modificar_cluster" or comando == "mc") {
            string s;
            cin >> s;
            cout << "#" << comando << " " << s << endl;
            c.insertar_cluster(s);
        }
    //3 
        else if (comando == "alta_prioridad" or comando == "ap") {
            string id_prio;
            cin >> id_prio;
            cout << '#' << comando << " " << id_prio << endl;
            area.añadir_prioridad(id_prio);
        }
    //4 
        else if (comando == "baja_prioridad" or comando == "bp") {
            string p;
            cin >> p;
            cout << '#' << comando << " " << p << endl;
            area.eliminar_prioridad(p);
        }
    //5  
        else if (comando == "alta_proceso_espera" or comando == "ape") {
            string s;
            cin >> s;
            int idj, memj, tj;
            cin >> idj >> memj >> tj;
            cout << '#' << comando << " " << s << " " << idj << endl;
            area.añadir_job(s, idj, memj, tj);
        }
    //6 
        else if (comando == "alta_proceso_procesador" or comando == "app") {
            string s;
            cin >> s;
            int id, mem, t;
            cin >> id >> mem >> t;
            if (comando == "alta_proceso_procesador") cout << "#alta_proceso_procesador " << s << " " << id << endl;
            else cout << '#' << comando << " " << s << " " << id << endl;
            Job j(id, mem, t);
            c.añadir_job_procesador(s, id, j);
        }
    //7 
        else if (comando == "baja_proceso_procesador" or comando == "bpp") {
            string s;
            int id;
            cin >> s >> id;
            cout << '#' << comando << " " << s << " " << id << endl;
            c.eliminar_job_procesador(s, id);
        }
    //8
        else if (comando == "enviar_procesos_cluster" or comando == "epc") {
            int n;
            cin >> n;
            cout << "#" << comando << " " << n << endl;
            area.enviar_job_cluster(n, c);
        }
    //9 
        else if (comando == "avanzar_tiempo" or comando == "at") {
            int t;
            cin >> t;
            cout << '#' << comando << " " << t << endl;
            c.avanzar_tiempo(t);
        }
    //10  
        else if (comando == "imprimir_prioridad" or comando == "ipri") {
            string s;
            cin >> s;
            cout << '#' << comando << " " << s << endl;
            area.imprimir_prio(s);
        }
    //11 
        
        if (comando == "imprimir_area_espera" or comando == "iae") {  
            if (comando == "imprimir_area_espera") cout << "#imprimir_area_espera" << endl;
            else cout << '#' << comando << endl;
            area.imprimir_area_espera();
        }
    //12 
        else if (comando == "imprimir_procesador" or comando == "ipro") {
            string id_prc;
            cin >> id_prc;
            cout << '#' << comando << " " << id_prc << endl;          
            c.imprimir_prc(id_prc);
        }
    //13 
        else if (comando == "imprimir_procesadores_cluster" or comando == "ipc") {
            cout << '#' << comando << endl;
            c.escribir_cluster();
        }
    //14 
        else if (comando == "imprimir_estructura_cluster" or comando == "iec") {
            cout << '#' << comando << endl;
            c.estructura_cluster();
        }    

    //15
        else if (comando == "compactar_memoria_procesador" or comando == "cmp") {
            string s; cin >> s;
            cout << "#" << comando << " " << s << endl;
            c.compactar_memoria(s);
        }  
    //16
        else if (comando == "compactar_memoria_cluster" or comando == "cmc") {
            cout << "#" << comando << endl;
            c.compactar_memoria_cluster();
        }
    //Examen
        else if (comando == "podar_cluster" or comando == "pc") {
            string s; cin >> s;
            cout << "#" << comando << " " << s << endl;
            //Antes de llamar a la funcion comprovar que existe o que es la raiz
            c.poda(s);
        }
        cin >> comando;
    }
}