/** @file Prioridad.hh
   @brief Especificacion de la classe Prioridad
*/
//Usar una struct para algo?
#ifndef PRIORIDAD_HH
#define PRIORIDAD_HH
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <list>
#endif
using namespace std;

/** @class Prioridad
    @brief Representa un conjunto de jobs con la misma prioridad

    Tenemos una lista (l) de enteros que nos guarda los jobs por orden de insercion en la prioridad.
    Despues tenemos un map (m) de int y job que nos proporciona rapido acceso a todos los jobs que hay en la prioridad.
    Finalmente tenemos 2 variables rechazos y enviados que son el numero de jobs respestivamente que se han enviado 
    al cluster y los que se han rechazado.
*/
class Prioridad {
private:
    /** @brief Lista de enteros que guarda los jobs por orden de insercion*/
    list<Job> l;
    /** @brief Mapa de int (id) y job ordenado crecientemente*/
    map<int, Job> m;
    /** @brief Numero de jobs rechazados al enviarlos al cluster*/
    int rechazos;
    /** @brief Numero de jobs enviados al cluster*/
    int enviados;

public:
    //Constructora
    Prioridad();

    //Consultoras
    /**  @brief Consulta si existe job con el identificador id
     
     *  \pre Tenemos el identificador del job
     *  \post True: si existe un job en la lista con ese identificador
        False si no existe ningun job con ese identificador
        \cost Logaritmica
    */
    bool existe_job(const int& id) const;
    
    /** @brief Mira si hay jobs pendientes en la prioridad.
     
        \pre Cierto.
        \post True: Si la lista no esta vacia.\n
        False: Si la lista esta vacia.
        \cost Constante
    */
    bool job_pendent() const;

    /** @brief Escribe los jobs con la misma prioridad.
      
     *  \pre Cierto.
     *  \post Por el canal de salida estan todos los jobs en orden
     *  decreciente de antiguedad, desde su ultima alta.
     *  \cost Lineal
    */
    void escribir_jobs() const;

    /**  @brief Añade un job a la prioridad.
     
     *  \pre Se garantiza que el job no existe en la prioridad.
     *  \post Añade el job a la lista de prioridad.
     *  \cost Constante
    */
    void añadir_job(const int& idj, const Job& j);

    //Job consultar_job(const int& id);
    /** @brief Envia n jobs al cluster c 
     * 
     *  \pre Tenemos el numero de jobs a enviar y el cluster.
     *  \post Se han enviado n jobs al cluster.
     *  Y actualizado el numero de rechazos y enviados.
    */
    void enviar_prc(int& n, Cluster& c);

};
#endif