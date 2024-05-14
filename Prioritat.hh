/** @file Prioritat.hh
    @brief Especificación de la clase Prioritat
*/

#ifndef CLASS_Prioritat_HH
#define CLASS_Prioritat_HH

#include "Cluster.hh"
#include "Proces.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#endif

/** @class Prioritat
    @brief La prioridad son clases en el Area de espera que sirven para saber que procesos se mandan antes o después, 
    la prioridad trata con una lista de procesos, para poder enviarlos luegos
*/

class Prioritat {
private:

list <Proces> processos;

int proces_enviats;
int proces_denegats;

public:
//Constructora

/** @brief Creadora por defecto se ejecuta al declarar una prioritat
    \pre <em>Cierto</em>
    \post El resultado es una prioridad no inicializada
*/
Prioritat();

/** @brief Envia n numero de procesos al cluster
    \pre <em>Cierto</em>
    \post Envia al cluster n numero de procesos, o si la lista de procesos es mayor que n, envía todos los procesos de la prioridad,
    se envian primero los mas antiguos, osea los que estan en el begin 
    \coste Lineal
*/

void enviar_procesos_cluster(int& n, Cluster& cl);

/** @brief Añade el proceso seleccionado a la cola de procesos que hay en prioridad
    \pre <em>Cierto</em>
    \post El proceso se añade al principio de la cola de procesos de prioridad
    \coste Constante

*/

void añadir_proceso(const Proces& proces);

//Escritura

/** @brief Imprime todos los procesos de la prioridad
    \pre <em>Cierto</em>
    \post Escribe en el canal estandar de salida las prioridades en orden decre3ciente de antigüedad, se imprimen 
    también el número de procesos enviados al cluster y el número de intentos fallidos
    \coste Lineal
*/

void imprimir_prioridad() const;

//Consultoras

/** @brief Consulta la ID de la prioritat
    \pre La prioridad tiene ID 
    \post Devuelve el string 'ID' de la prioridad
    \coste Constante
*/

string consultar_ID();

/** @brief Consulta si el proceso seleccionado existe
    \pre <em>Cierto</em>
    \post Devuelve un booleano que determina si el proceso buscado existe o no
    \coste Logaritmico
*/

bool existeix_proces(const int& proces) const;

/** @brief Consulta si hay procesos con esta prioridad
    \pre <em>Cierto</em>
    \post Devuelve un booleano que indica si hay o no procesos
    \coste Constante
*/

bool existeixen_processos() const;

};

#endif