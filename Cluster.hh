/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef CLASS_Cluster_HH
#define CLASS_Cluster_HH

#include "Cpu.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <queue>
#include "BinTree.hh"
#endif
using namespace std;

/** @class Cluster
    @brief El cluster desde donde se almacenan y administran todos los procesadores, de los cuales se guardan 
    en un BinTree de string sus Identificadores estructurados segun la lectura, y un mapa para poder acceder 
    a ellos más rapidamente
*/

class Cluster {

private:

int temps;

BinTree <string> b;
map <string, Cpu> mapa;

//Modificadoras

/** @brief Es la inmersión de la función modificar_cluster, busca un nodo por referencia
    \pre <em>Cierto</em>
    \post Devuelve un bool diciendo si ha encontrado el procesador sobre el que se ha de modificar el 
    cluster, y cuando lo encuentra modifica el nodo con 'llegir_BinTree', mirando antes si tiene auxiliares
    \coste Lineal
*/

bool inmersio_modificar_cluster(BinTree<string>& arb, const string& cpu);

/** @brief Retorna el arbol leido, y apunta los procesadores al mapa de procesadores del Cluster
    \pre <em>Cierto</em>
    \post Los procesadores leidos han sido añadidos al Cluster y el BinTree que se devuelve es
    un BinTree de strings de procesadores
    \coste Lineal
*/

BinTree<string> llegir_BinTree();

//Consultoras

/** @brief Apunta en una lista el orden en el que aparecen los procesadores

    \pre <em>Cierto</em>
    \post Modifica la lista 'l' añadiendo a la lista los ID de los procesadores, primero insertanto 
    la raiz, luego todos los nodos del nivel uno de izquierda a derecha, y así por cada nivel hasta que 
    no quede más arbol que recorrer
    \coste Constante
*/

void checkear_arbol_dist_esqu(const BinTree<string>& arb, list<string>& l);

public:

/** @brief Creadora por defecto, se ejecuta al declarar el cluster
    \pre <em>Cierto</em>
    \post El resultado es un cluster vacio
*/

Cluster();



//Modificadoras

/** @brief Lee un nuevo BinTree de Cpus a traves del canal de entrada estandar, si ya existia uno se elimina
    \pre <em>Cierto</em>
    \post Crea un BinTree con las Cpus seleccionadas
    \coste Lineal
*/

void configurar_cluster(); 

/** @brief Lee un nuevo BinTree y se lo añade al BinTree ya existente a una Cpu seleccionada
    \pre La Cpu seleccionada no tiene procesadores auxiliares, tampoco procesos en ejecucion y existe en el BinTree
    \post Devuelve un nuevo BinTree, resultado de fusionar el BinTree anterior y el nuevo, el nuevo se lee usando la 
    función 'llegir_BinTree'
    \coste Lineal
*/

void modificar_cluster(const string& cpu);

/** @brief Envía el proceso al procesador seleccionado
    \pre El procesador seleccionado existe, y el proceso se puede añadir a la memoria de el procesador
    \post El proceso se envía al procesador seleccionado para llamar otra función en el procesador que lo añade a su memoria
    \coste Logaritmico
*/

void alta_proceso_procesador(map <string, Cpu>::iterator& it, Proces& proces);

/** @brief Elimina el proceso del procesador seleccionado
    \pre El procesador seleccionado existe, y el proceso existe dentro del procesador
    \post Se llama a una funcion en el procesador seleccionado que elimina el proceso de su memoria
    \coste Lineal
*/

void baja_proceso_procesador(map <string, Cpu>::iterator& it,const int& proces);

/** @brief Avanza el tiempo de todos los procesadores
    \pre <em>Cierto</em>
    \post En cada procesador del cluster se avanza el tiempo seleccionado, esto se hace llamando a la función
    'avanzar_tiempo' que hay en la clase CPU, eliminando así también los procesos que hayan acabado de su memoria
    \coste Lineal
*/

void avanzar_tiempo(const int& t);

/** @brief Se compacta la memoria del procesador seleccionado
    \pre El procesador seleccionado existe en el cluster, y el iterador señala a este mismo
    \post Compacta la memoria del procesador moviendo todos los procesos al principio de la memoria, respetando el 
    orden inicial, y si dejar huecos ni solapandose
    \coste Lineal
*/

void compactar_memoria_cpu(map<string, Cpu>::iterator& it);

/** @brief Se compacta la memoria de todos los procesadores del cluster
    \pre <em>Cierto</em>
    \post Compacta la memoria de todos los procesadores siguiendo el criterio de la función 'compactar_memoria_cpu'
    \coste Lineal
*/

void compactar_memoria_cluster();

//Escritura

/** @brief Imprime el procesador seleccionado
    \pre El procesador seleccionado existe en el cluster
    \post Escribe en el canal de salida estandar la memoria del procesador, escribiendo los procesos por orden creciente
    desde primera posicion de memoria, junto a la posición del proceso y el resto de sus datos, incluyendo el tiempo restante 
    para que se acabe de ejecutar el proceso, para esto llama a la funcion 'void imprimir_procesador() const' que hay en la clase 'Cpu'
    \coste Constante
*/

void imprimir_procesador(map<string, Cpu>::iterator& it) const;

/** @brief Imprime la estructura del BinTree
    \pre <em>Cierto</em>
    \post Imprime en el canal de salida estandar la estructura del BinTree de procesadores del cluster
    \coste Lineal
*/

void imprimir_estructura() const;

/** @brief Imprime todos los procesadores del cluster
    \pre <em>Cierto</em>
    \post Escribe en el canal de salida estandar todos los procesadores del cluster por orden creciente de identificador, 
    siguiendo los criterios de la función 'void imprimir_procesador(string cpu)'
    \coste Lineal
*/

void imprimir_procesadores() const; 

//Consultoras

/** @brief Consulta si el procesador seleccionado existe
    \pre <em>Cierto</em>
    \post Devuelve un booleano que indica si existe un procesador con el identificador seleccionado, al encontrarlo,
    devuelve un iterador con su ubicación
    \coste Logaritmico
*/

bool existeix_cpu(const string& cpu, map <string, Cpu>::iterator& it);

/** @brief Busca el string ID de la Cpu en la que se ha de meter el proceso
    \pre <em>Cierto</em>
    \post Devuelve un booleano que indica si se puede meter el proceso, y modifica por referencia el string
    'ID', que devuelve el ID del procesador que sea mejor candidato 
    \coste Lineal
*/

bool eleccio_cpu(string& ID, Proces& p);

/** @brief Consulta si la cpu seleccionada tiene procesos en su memoria
    \pre La Cpu seleccionada existe, i el iterador señala a esta misma
    \post Devuelve un booleano que indica si existen procesos en la memoria de la cpu seleccionada, accediendo a 
    la función 'bool te_procesos() const' que hay en la clase Cpu
    \coste Constante
*/

bool cpu_te_procesos(map <string, Cpu>::iterator& it) const;

/** @brief Consulta mediante un identidicador de proceso si este proceso existe en el procesador seleccionado mediante
 * un iterador 
    \pre La Cpu seleccionada existe
    \post Devuelve un booleano que indica si existe el proceso seleccionado en el procesador, llamando a la 
    funcion 'bool existeix_proces(const string proces) const' que hay en la clase Cpu
    \coste Logaritmico
*/

bool cpu_existeix_proces(map <string, Cpu>::iterator& it, const int& proces) const;

/** @brief Busca en el cluster un procesador con la ID introducida
    \pre La Cpu seleccionada existe
    \post Devuelve un iterador apuntando a la ubicacion en el mapa de la Cpu que se ha buscado
    \coste Logaritmico
*/

map<string, Cpu>::iterator buscar_procesador(string& ID_Cpu);

};
#endif