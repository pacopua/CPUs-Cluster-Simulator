/** @file Proces.hh
    @brief Especificación de la clase Proces
*/

#ifndef CLASS_Proces_HH
#define CLASS_Proces_HH

#ifndef NO_DIAGRAM
#include <iostream>
#endif
using namespace std;

/** @class Proces
    @brief Los procesos tienen un int identificador, y dos int más que indican cuanto espacio ocupan 
    y cuanto tiempo tarda en ejecutarse
*/

class Proces {
private:

int ID;
int memreq;
int temps;

public:
//Constructora

/** @brief Creadora por defecto que se ejecuta al declarar un proceso
    \pre <em>Cierto</em>
    \post El resultado es un proceso no inicializado
    \coste Constante
*/

Proces();
//Lectura

/** @brief Lee los parametros de un proceso
    \pre <em>Cierto</em>
    \post Se leen los parametros del parametro implicito, en ese caso el proceso.
    \coste Constante 
*/

void llegir();

//Modificadoras

/** @brief Avanza el tiempo t unidades
    \pre <em>Cierto</em>
    \post El parametro 'tiempo' del parametro implicito proceso, disminuye t unidades.
    \coste Constante
*/

void modificar_temps(int t);

//Escritura

/** @brief Imprime el tiempo que le queda al proceso
    \pre Que el parametro 'tiempo' tenga un valor asignado
    \post Imprime el tiempo que le queda al proceso para terminar su ejecución en el canal de salida principal
    \coste Constante
*/

int consultar_temps() const;

/** @brief Imprime la memoria que ocupa el proceso
    \pre Que el parametro 'memoria' tenga un valor asignado 
    \post Imprime el espacio de memoria que ocupa este proceso en el canal de salida principal
    \coste Constante
*/

int consultar_memoria() const;

/** @brief Imprime todos los parametros del proceso
    \pre Que los parametros del proceso estén ya inicializados
    \post Imprime en el canal de salida principal los parametros 'ID', 'memoria' y 'tiempo' del proceso
    \coste Constante
*/

void imprimir() const;

//Consultora

/** @brief Consulta el identificador de el proceso
    \pre Que el int 'ID' tenga ya unos caracteres asignados
    \post Devuelve el int 'ID'
    \coste Constante
*/

int consultar_ID() const;

};

#endif
