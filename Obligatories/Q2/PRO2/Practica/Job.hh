/** @file Job.hh
   @brief Especificacion de la classe Job
*/

#ifndef JOB_HH
#define JOB_HH

#ifndef NO_DIAGRAM
using namespace std;
#include <iostream>
#endif

/** @class Job
    @brief Representa un proceso con la cantidad de memoria que ocupa
    y su tiempo de ejecucion
*/
class Job {

private:
    /** @brief Identificador del job*/
    int id;
    /** @brief Memoria que ocupa el job*/
    int mem;
    /** @brief Tiempo que tarda en ejecutarse el job*/
    int t;

public:
    //Constructoras

    /**  @brief Constructora por defecto
     
     *   \pre Cierto
     *   \post El resultado es un nuevo job
    */
    Job();

    /**  @brief Constructora definida
     
     *   \pre Tenemos en el canal de entrada los datos de un job
     *   \post El resultado es un job con esos datos
    */
    Job(const int& idj, const int& memj, const int& tj);

    //Consultoras

    /**  @brief Consulta la memoria que ocupa el job
    
     *  \pre Cierto
     *  \post Devuelve la memoria que ocupa el job
     *  \coste Constante
    */
    int consultar_mem() const;


    /**  @brief Consulta el tiempo restante del job
    
     *  \pre Cierto
     *  \post Devuelve el tiempo restante para ocmpletar el job
     *  \coste Constante
    */
    int consultar_temps() const;

    /** @brief Consulta el identificador del job.
     * 
     *  \pre Cierto.
     *  \post Devuelve el identificador del job.
     *  \coste Constante
    */
    int consultar_id() const;

    //Modificadoras

    /** @brief Resta el tiempo de cada job.
    
        \pre Tenemos la cantidad de tiempoq que tenemos que restar.
        \post Devuelve el job con el tiempo restado.
        \coste Constante
    */
    void restar_temps(const int& temps);

    //Escritura

    /** @brief Imprime los parametros del job.
     
        \pre Cierto.
        \post Tenemos por el canal de salida los parametros del job.
        \coste Constante
    */
    void imprimir_job() const;
};
#endif