/** @file Area_espera.hh
   @brief Especificacion de la classe Area_espera
*/

#ifndef AREA_JOB_PENDENT_HH
#define AREA_JOB_PENDENT_HH

#include "Prioridad.hh"

using namespace std;

/** @class Area_espera
    @brief Representa un conjunto de prioridades en orden creciente con sus operaciones.

    Tenemos un mapa que ordena las prioridades por identificador en orden creciente y nos facilita la busqueda
    y acceso a diferentes prioridades.
*/
class Area_espera {
private: 
    /** @brief Mapa ordenado por strings (identificador) de las prioridades*/
    map<string, Prioridad> ae;
    
public: 
    //Constructoras

    /**  @brief Constructora por defecto
      
     *   \pre Cierto
     *   \post El resultado es un area de espera
    */
    Area_espera();

    /**  @brief Leer area espera.
     * 
    *   \pre Cierto.
    *   \post Se guarda en el area de espera la informacion proporcionada 
    *   en el canal de entrada.
    *   \coste Logaritmica
    */
    void llegir_area();

    //Escritura

    /**  @brief Imprime el area de espera.
     
     *  \pre Cierto.
     *  \post Tenemos en el canal de salida todos los job pendientes
        en orden creciente de prioridad.
        \coste Lineal
    */
    void imprimir_area_espera() const;

    /** @brief Imprime una prioridad especifica
     
        \pre Tenemos s que es el identificador de una prioridad
        \post Por el canal de salida tenemos la prioridad con los jobs
        por orden de insercion.\n
        Si no existe la prioridad imprime un mensaje de error.
        \coste Lineal
    */
    void imprimir_prio(const string& s) const;

    //Modificadoras

    /**  @brief Añade una prioridad al area de espera
      .
     *  \pre Tenemos un identificador de prioridad que no existe en el area
     *  \post Añade al area de prioridad en posicion la nueva prioridad.\n
     *  Si la prioridad ya existe envia un mensaje de error.
     *  \coste Constante 
    */
    void añadir_prioridad(const string& identificador);

    /**  @brief Elimina una prioridad.
     
     *  \pre Tenemos un identificador de prioridad que existe en el area.
     *  \post Elimina la prioridad del area de prioridad.\n
     *  Si no existe la prioridad o tiene procesos en ella envia un mensaje de error.
     *  \coste Logaritmica
    */
    void eliminar_prioridad(const string& identificador);

    /**  @brief Añade un job a la prioridad s
     * 
    *   \pre Tenemos el identificador de la prioridad y un job
    *   \post Se añade el job a la prioridad.\n
    *   Si no existe la prioridad o el job ya existe en la prioridad,
    *   envia un mensaje de error
    *   \coste Logaritmica
    */
    void añadir_job(const string& s, const int& idj, const int& memj, const int& tj);

    /**  @brief Envia n procesos al cluster.
     
     *  \pre Tenemos un entero n que es la cantitdad de jobs que hay que enviar
        y el cluster al que hay que enviarlo
     *  \post Se han colocado los jobs que pueden ir a un procesador
        en el cluster, y los que no han vuelto al area de espera.
        Tambien nos deja 2 variables int con el numero de rechazos
        y jobs colocados en el cluster.
    */
    void enviar_job_cluster(int& n, Cluster& c);
};

#endif