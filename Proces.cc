/** @file Proces.cc
    @brief archivo .cc de la clase Proces
*/

#include "Proces.hh"

//Constructoras

Proces::Proces() {
    ID = memreq = temps = 0;
}

//Lectoras

void Proces::llegir() {
    cin >> ID >> memreq >> temps;
}

//Modificadoras

void Proces::modificar_temps(int t) {
    temps -= t;
}

//Consultoras

int Proces::consultar_temps() const {
    return temps;
}

int Proces::consultar_memoria() const {
    return memreq;
}

int Proces::consultar_ID() const {
    return ID;
}

//Escritras

void Proces::imprimir() const {
    cout << ID << " " << memreq << " " << temps << endl;
}