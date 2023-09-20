/** @file Cluster.hh
   @brief Especificacion de la classe Cluster
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH
#include "Procesador.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <string>
#endif

/** @class Cluster
    @brief Representa un conjunto de procesadores en forma de BinTree y
    sus operaciones.

    Tenemos dos elementos principales un arbol binario con los identificadores de los procesadores
    y luego un map que nos da un acceso mas facil a buscar cualquier procesador que este presente en
    el arbol
*/
class Cluster {
private:
    /** @brief Estructura del cluster */
    BinTree<string> c;
    /** @brief Mapa ordenado por strings que nos proporciona facil acceso a cualquier procesador */
    map<string, Procesador> mp;
    /** @brief Estructura que se usa para ciertas condiciones */
    struct Compare {
        int profunditat;
        int free_mem;
        int espai_ajd;
    };

    //Funciones auxiliares

    /** @brief Funcion auxiliar de estructura_cluster.*/
    void estructura(const BinTree<string>& c) const;

    /** @brief Funcion auxiliar de configurar cluster*/
    void leer_bintree(BinTree<string>& c, map<string,Procesador>& mp);

    /** @brief Funcion auxiliar de modificar cluster*/
    void insertar_bintree(BinTree<string>& a,const string& id, const BinTree<string>& nuevo);

    /** @brief Funcion auxiliar de modificar cluster*/
    void insertar_mapa(map<string,Procesador>& p, map<string,Procesador>& nuevo, const string& s);

    /** @brief Funcion auxiliar de modificar cluster*/
    bool te_fills(const BinTree<string>& a,const string& id) const; 

    /** @brief Funcion auxiliar de enviar procesos cluster*/
    bool enviar_prc_recursiu(const BinTree<string>& c, const Job& job, map<string, Procesador>::iterator& it, Compare& comp, int& profunditat);

    /** @brief Funcion auxiliar de enviar procesos cluster*/
    int best_prc(const Job& job, Compare& comp_best, map<string, Procesador>::iterator& it_actual, int& profunditat);

public:
    //Constructoras

    /** @brief Creadora por defecto 
    
        \pre Cierto.
        \post Crea un cluster vacio.
    */
    Cluster();

    //Modificadoras

        /** @brief Configurar cluster
    
        \pre Cierto.
        \post Devuelve un cluster con sus procesadores y memoria
        si existia un cluster, deja de existir y lo remplaza.
        \coste Lineal
    */
    void configurar_cluster();

    void poda(string& id);

    /** @brief Funcion auxiliar de modificar cluster*/
    bool procesador_aux(const string& s) const;

    void i_poda(BinTree<string>& t, map<string, Procesador>& mp, const string& id, int& prc, int& jobs);

    void elimina_prc(BinTree<string>& t, map<string, Procesador>& mp, int& prc, int& jobs); 
    
    /** @brief Inserta un cluster en la posicion del procesador con id p
     *   
     *  \pre Un identificador p .
     *  \post El nuevo cluster esta en la posicion del indentificador
        ampliando asi el cluster base.
        \coste Lineal
    */
    void insertar_cluster(const string& p);

    /** @brief Añade un job al procesador s.
    
        \pre Tenemos el identificador del procesador y el job con su id.
        \post Se guarda el job con su id en el procesador s.\n
        Si el procesador no existe o si el job ya existe envia un mensaje de error.
        \coste Constante
    */ 
    void añadir_job_procesador(const string& s,const int& idj,const Job& j);

    /** @brief Elimina un job (id) del procesador s.
     
        \pre Tenemos el identificador del procesador y el identificador del job.
        \post Elimina el job del procesador restableciendo la memoria que ocupaba.\n
        Si el procesador no existe o el job no existe envia un mensaje de error.
        \coste Logaritmico
    */
    void eliminar_job_procesador(const string& s,const int& idj);

    /** @brief Avanza el tiempo del cluster.
      
     *  \pre Tenemos t que es el tiempo que ha transcurido desde la 
        ultima actualizacion de tiempo.
     *  \post Todos los job que tengan un tiempo inferior a este seran 
        eliminados ya que han acabado.
        \coste Lineal
    */
    void avanzar_tiempo(const int& t);

    /** @brief Compacta la memoria de un procesador
       
     *  \pre Tenemos s que representa la id de un procesador
     *  \post El procesador con el id, tiene toda la memoria compactada.\n
        Si el procesador no existe envia un mensaje de error.\n
        No - existe error
        \coste Constante
    */
    void compactar_memoria(const string& s);
    
    /** @brief Compacta la memoria de todo el cluster
       
     *  \pre Cierto
     *  \post Cada procesador del cluster tiene la memoria compactada
     *  \coste Lineal
    */
    void compactar_memoria_cluster();

    //Escritura

    /** @brief Escribe el cluster en el canal de salida.
       
     *  \pre Cierto.
     *  \post Por el canal de salida escribe el cluster en preorden 
     *  con todos los procesadores y sus procesos activos.
     *  \coste Lineal
    */
    void escribir_cluster() const;

    /** @brief Escribe la estructura del cluster en el canal de salida.
     
     * \pre Cierto.
     * \post Escribe la estructura del cluster en preorden por el canal de salida.
     * \coste Lineal
    */
    void estructura_cluster() const;

    /** @brief Escribe el procesador s.
    
        \pre Tenemos el id del procesador.
        \post Escribe por en canal de salida el procesador s.\n
        Si el procesador s no existe envia un mensaje de error.
        \coste Logaritmica
    */
    void imprimir_prc(const string& s) const;

    /** @brief Funcion auxiliar de enviar procesos cluster*/
    bool job_enviat(const Job& job);
};
#endif