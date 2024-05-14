/** @file Area_de_espera.hh
    @brief Especificación de la clase Area_de_espera
*/



#ifndef CLASS_Area_de_espera_HH
#define CLASS_Area_de_espera_HH

#include "Prioritat.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#include <map>
#endif

/** @class Area_de_espera
    @brief Aquí se guardan los procesos a la espera de ser enviados al cluster, por orden de prioridad, estas se guardan 
    con un identificador de Prioridad, y su prioridad correspondiente
*/

class Area_de_espera {

private:

map <string, Prioritat> prioritats;

public:
//Inicialización 

/** @brief Creadora por defecto, se ejecuta al declarar el area de espera
    \pre <em>Cierto</em>
    \post El resultado es una area de espera vacia
*/

Area_de_espera();

//Modificadoras
/** @brief Hace una lectua de les prioritats del Area de espara
    \pre <em>Cierto</em>
    \post Devuelve el Area de espera con las prioridades leidas
    \coste Constante
*/

void llegir_area_de_espera();

/** @brief Añade la prioridad seleccionada a el area de espera 
    \pre La prioridad seleccionada no existe en el Area de espera
    \post Se añade la prioridad seleccionada en la lista de prioridades de el area de espera
    \coste Constante 
*/

void alta_prioridad(const string& ID_Prioritat);

/** @brief Elimina la prioridad seleccionada de la area de espera
    \pre La prioridad seleccionada existe en la area de espera y no tiene procesos pendientes
    \post Se elimina la prioridad seleccionada de la lista de prioridades de la area de espera
    \coste Constante
*/

void baja_prioridad(map<string, Prioritat>::iterator& it);

/** @brief Añade el proceso seleccionado a la cola de procesos que hay en la prioridad seleccionada 
    \pre La prioridad seleccionada existe en el Area de espera y el iterador señala a esta 
    \post El proceso se añade al principio de la cola de procesos de prioridad, llamando a la función 
    'void añadir_proceso(const Proces& proces)' que hay en la clase 'Prioritat'
    \coste Constante
*/

void alta_proceso_espera(map<string, Prioritat>::iterator& it, const Proces& proces);

/** @brief Envía al cluster n numero de procesos, o hasta que no se puedan enviar más
    \pre <em>cierto</em>
    \post Envía n procesos al cluster, o hasta que el Area de espera se quede sin procesos, y los envia
    por orden de prioridad, y dentro de este orden, se envian por orden de antigüedad. Los procesos son enviados
    uno a uno al cluster usando la función 'void enviar_procesos_cluster(int& n, Cluster& cl)' ubicada en 
    la classe 'Prioritat'
    \coste Lineal
*/

void enviar_procesos_cluster(int& n, Cluster& cl);


//Consultoras

/** @brief Consulta si existe el proceso seleccionado en la prioridad seleccionada 
    \pre La prioridad existe en el Area de espera y el iterador señala a esta misma
    \post Devuelve un booleano que indica si existe o no el proceso, usando la función 
    'bool existeix_proces(const int& proces) const' ubicada en la classe 'Prioritat' 
    \coste Logaritmico
*/

bool prioritat_existeix_proces(const int& proces, map<string, Prioritat>::iterator it) const;

/** @brief Consulta si existe la prioridad seleccionada en el Area de espera
    \pre <em>Cierto</em>
    \post Devuelve un booleano que indica si existe o no la prioridad en el Area de espera 
    \coste Logaritmico
*/

bool existeix_prioritat(const string& ID_Prioritat) const;

/** @brief Consulta si existe la prioridad seleccionada en el Area de espera 
    \pre <em>Cierto</em>
    \post Devuelve un booleano que indica si existe o no la prioridad en el Area de espera y ademas modifica 
    el iterador enviado para que señale al lugar en el mapa de el Area_de_espera en que está la prioridad 
    \coste Logaritmico
*/

bool existeix_prioritat(const string& ID_Prioritat, map<string, Prioritat>::iterator& it);

/** @brief Consulta si existe algun proceso en la prioridad seleccionada 
    \pre La prioridad existe en el Area de espera, y el iterador señala a esta
    \post Devuelve un booleano que indica si existe algún proceso, usando la función 'bool existeixen_processos() const'
    ubicada en la classe 'Prioritat' 
    \coste Constante
*/

bool prioritat_te_processos(const map<string, Prioritat>::iterator& it) const;

//Escritura

/** @brief Imprime la prioridad seleccionada
    \pre La prioridad existe en el Area de espera, y el iterador señala a esta misma
    \post Se imprimen los procesos que hay en la prioridad en orden decreciente de antigüedad, y después se imprimen
    la cantidad de procesos que se han enviado al cluster de esa prioridad y la cantidad de procesos que se han intentado
    enviar pero no se ha podido, eso se hace accediendo a la función de imprimir que hay en la clase 'Prioritat'
    \coste Lineal
*/

void imprimir_prioridad(map<string, Prioritat>::iterator& it);

/** @brief Imprime todas las prioridades  
    \pre <em>Cierto</em>
    \post Hace lo mismo que la función 'void imprimir_prioridad(const string& prioridad)' pero para todas las
    prioridades que hay en el Area de espera
    \coste Lineal
*/

void imprimir_area_espera() const;

}
;
#endif