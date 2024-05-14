/** @file Cpu.hh
    @brief Especificación de la clase Cpu
*/

#ifndef CLASS_CPU_HH
#define CLASS_CPU_HH

#include "Proces.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <list>
#include <set>
#endif
using namespace std;

/** @class Cpu 
    @brief Las CPUs son los procesadores en los que se ejecutan los procesos, tiene un string Identificador, dos ints
    uno para la capacidad total, y otro para la memoria libre, dos mapas para buscar, encontrar y manipular procesos,
    y un ultimo mapa para manipular los huecos que quedan en los procesos, apuntanto sus medidas, y posiciones 
*/

class Cpu {

private:

string ID;
int capacitat;
int memoria_lliure;

map <int, int> mapa_posiciones; //Id_proces, posicio
map <int, Proces> mapa_processos; //posicio, Proces
map <int, set<int>> mapa_forats; //mida_forat, set<posicio>
 
public:

//Constructora
/** @brief Creadora por defecto que se ejecuta al declarar una CPU
    \pre <em>Cierto</em>
    \post Devuelve una CPU no inicializada
*/

Cpu();

//Lectura

/** @brief Copia los parametros de la CPU
    \pre <em>Cierto</em>
    \post El procesador utiliza pos parametros enviados como Identificador y para determinar su capacidad de memoria 
    \coste Logaritmico
*/

void asignar_valores_cpu(const string& ID, const int& capacitat);

/** @brief Lee los parametros de la CPU
    \pre Que en el canal de entrada haya un string 'ID' y un int 'Capacidad'
    \post Al parametro 'ID' del parametro implicito, se le asigna un string i un int 
    leidos por el canal de entrada principal  
    \coste Logaritmico
*/

void llegir();

//Modificadoras

/** @brief Reajusta el mapa de huecos
    \pre <em>Cierto</em>
    \post Ajusta los huecos del mapa de huecos del procesador, para que si hay dos huecos juntos
    hagan entre los dos uno de mayor tamaño
    \coste Lineal 
*/

void ajustar_huecos();

/** @brief Añade un proceso al procesador
    \pre Que haya espacio en la memoria del procesador
    \post Le añade a la memoria del procesador el proceso seleccionado en la posición más pequeña que deje el hueco más ajustado
    \coste Logaritmico
*/

void alta_proceso_procesador(Proces& proces);

/** @brief Junta todos los procesos de la memoria
    \pre <em>Cierto</em>
    \post Pega todo lo que pueda los procesos con la memoria, y crea un hueco con el espacio 
    sobrante posicionado después del ultimo proceso
    \coste Lineal
*/

void compactar_memoria_procesador();

/** @brief Elimina un proceso del procesador
    \pre El proceso seleccionado existe
    \post El proceso seleccionado se elimina de la memoria del procesador
    \coste Lineal
*/

void baja_proceso_procesador(const int& proces);

/** @brief Avanza el tiempo de los procesos del procesador, al int 't' se le va 
 * restando el tiempo que consume cada procesador, hasta que 't' llega a '0', los procesos se van 
 * eliminando
    \pre <em>Cierto<em>
    \post Los procesos que hayan sido ejecutados en ese tiempo se eliminan de la memoria de la cpu, si la 
    cpu se queda sin 
    \coste Constante
*/

void avanzar_tiempo(const int& t);

//Escritura

/** @brief Escribe los procesos de la memoria en orden creciente desde la primera posicion
    \pre <em>Cierto</em>
    \post Escribe en el canal de salida estandar la memoria del procesador, escribiendo los procesos por orden creciente
    desde primera posicion de memoria, junto a la posición del proceso y el resto de sus datos, incluyendo el tiempo restante 
    para que se acabe de ejecutar el proceso
    \coste Lineal
*/

void imprimir_procesador() const;

/** @brief Escribe la ID del procesador 
    \pre <em>Cierto</em>
    \post Escribe en el canal de salida estandar el ID del procesador
    \coste Constante
*/

void imprimir_ID() const;

//Consultoras

/** @brief Devuelve el tamaño del hueco mas ajustado en el que cabe el proceso
    \pre <em>Cierto</em>
    \post devuelve un int indicando el tamaño del hueco mas ajustado, si el proceso ya existia
    o si no cabe en el procesador devuelve '-1'
    \coste Logaritmico
*/

int tamaño_hueco_minimo(const int& ocupa,const int& ID_proces) const;

/** @brief Consulta cuanta memoria libre le queda al procesador
    \pre <em>Cierto</em>
    \post Devuelve un int con la memoria libre que tiene el procesador
    \coste Lineal
*/

int consultar_memoria_lliure() const;

/** @brief Consulta el identificador del procesador
    \pre <em>Cierto</em>
    \post Devuelve un string con la ID del procesador
    \coste Lineal
*/

string consultar_ID() const;

/** @brief Consulta si el procesador tiene algun proceso
    \pre <em>Cierto</em>
    \post Devuelve un booleano que indica si existe un proceso en ejecucion en el procesador
    \coste Lineal
*/

bool te_processos() const; 

/** @brief Consulta mediante un identidicador de proceso si este proceso existe en el procesador
    \pre <em>Cierto</em>
    \post Devuelve un booleano que indica si existe el proceso seleccionado o no en el procesador
    \coste Logaritmico
*/

bool existeix_proces(const int& proces) const;

 
};

#endif
