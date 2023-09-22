/** @file Procesador.hh
   @brief Especificacion de la classe Procesador
*/

#ifndef PROCESSADOR_HH
#define PROCESSADOR_HH
#include "Job.hh"

#ifndef NO_DIAGRAM
#include <set>
#include <map>

#endif

using namespace std;

/** @class Procesador
    @brief Representa un procesador con su memoria.


    Para ello tenemos 3 mapas diferentes, el primero (b) es un mapa que tiene 
    la id de cada job asociada a la posicion de memoria que se encuentra.\n
    El siguiente mapa (m) es el mapa de memoria que tiene las posiciones de memoria associadas a el job
    que se esta ejecutando en esa posicion.\n
    Finalmente esta el mapa (huecos) que tiene el tamaño del hueco associado a las diferentes posiciones de memoria
    que tienen un hueco de ese tamaño. Este mapa se usa principalmente para poder insertar jobs correctamente.
    Despues tenemos 2 variables tipo int que una (mem) es la memoria total que tiene el procesador y la otra
    (mem_free) es la memoria que tiene libre actualmente el procesador
*/
class Procesador {

private:
    /** @brief Total de memoria libre que dispone el procesador*/
    int mem_free;
    /** @brief Memoria total del procesador*/ 
    int mem; 
    /** @brief Mapa de los identificadores de los jobs y en que posicion de memoria se encuentran*/ 
    map<int,int> b;
    /** @brief Mapa de la posicion de memoria y el job que tiene asignado*/ 
    map<int,Job> m;
    /** @brief Mapa para ver los huecos que hay en la memoria del procesador*/ 
    map<int,set<int>> huecos;
    
public:
    
    //Constructoras

    /**  @brief Constructora por defecto.
     
     *   \pre Cierto.
     *   \post El resultado es un procesador.
    */
    Procesador();

    /**  @brief Constructora con parametros.
     
     *  \pre En el canal de entrada tenemos el id y la memoria que dispone
        el procesador.
     *  \post El resultado es un procesador con identificador id y memoria mem.
    */
    Procesador(const int& memory);

    //Consultoras

    /**  @brief Consultar en que posicion se puede insertar el job.
     
     *  \pre Cierto
     *  \post Devuelve el hueco donde esta mas ajustado el job j.\n
     *  Si no se puede insertar en el procesador devuelve -1.
     *  \coste Logaritmica
    */
    int consultar_memoria(const Job& j) const;
    
    /**  @brief Consulta cuanta memoria libre tiene el procesador.

     *  \pre Cierto.
     *  \post Devuelve la cantidad de memoria libre.
     *  \coste Constante
    */
    int free_mem() const;

    int quants_jobs() const;

    /**  @brief Consultar si existe un job con esa id.
     
     *  \pre Tenemos una id de un job.
     *  \post True si existe un job con esa id.\n
     *  False si no existe ningun job con esa id.
     *  \coste Logaritmica
    */
    bool existe_job(const int& id) const;

    /**  @brief Consultar si el procesador tiene job pendiente.

     *  \pre Cierto.
     *  \post Devuelve True si el procesador no tiene job pendiente.\n
     *  False si tiene job pendiente.
     *  \coste Constante
    */
    bool te_job() const;
    
    /**  @brief Consultar la posicion del job id

     *  \pre Se garantiza que el job id existe en el mapa
     *  \post Devuelve la posicion de memoria donde se encuantra el job
     *  \coste Logaritmica
    */
    //int posicio_job(const int& id) const;

    //Escritura

    /**  @brief Imprime el procesador.
     
     *  \pre Cierto
     *  \post Por el canal de salida tenemos los jobs
     *  del procesador en orden creciente de memoria con su posicion,
     *  y los dados de cada job con el tiemop restante.
     *  \coste Lineal
    */
    void imprimir_procesador() const;

    //Modificadores

    /**  @brief  Inserta un job en el procesador.
     
     *  \pre Se garantiza que el job no existe ya en el procesador y tambien que cabe.
     *  \post Se añade el job a la posicion de memoria mas ajustada del procesador.
     *  \coste Logaritmica
    */
    void insertar_job(const Job& job);

    /**  @brief Elimina un job con id job_id del procesador.
     
     *  \pre Se garantiza que el job existe en el procesador.
     *  \post Elimina el job del procesador.
     *  \coste Logaritmica
    */
    void eliminar_job(const int& job_id);

    /** @brief Avanza el tiempo temps unidades
    
        \pre Tenemos el tiempo que ha pasado desde la ultima actualizacion.
        \post Se han eliminado los jobs que ya se han completado de memoria.\n
        Si no se han completado se resta el tiempo de ejecucion.
        \coste Lineal
    */
    void pasar_temps(const int& temps);

    /**  @brief Compacta la memoria del procesador
     
     *  \pre Cierto
     *  \post La memoria del procesador se ha compactado.\n
     *  Si la memoria no estava llena solo queda un hueco en la parte inferior de la memoria. 
     *  \coste Lineal
    */
    void compactar_mem();
};
#endif