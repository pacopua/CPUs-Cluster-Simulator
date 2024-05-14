/** @file Area_de_espera.cc
    @brief archivo .cc de la clase Area_de_espera
*/

#include "Area_de_espera.hh"

//Consultoras

Area_de_espera::Area_de_espera() {
    prioritats = {};
}

//Modificadoras

void Area_de_espera::llegir_area_de_espera() {
    int n;
    cin >> n;
    string prioritat;
    for (int i = 0; i < n; ++i) {
        cin >> prioritat;
        alta_prioridad(prioritat);         
    }
}

void Area_de_espera::alta_prioridad(const string& ID_Prioritat) {
    Prioritat p;
    prioritats.insert(make_pair(ID_Prioritat, p));
}

void Area_de_espera::baja_prioridad(map<string, Prioritat>::iterator& it) {
    prioritats.erase(it);
}

void Area_de_espera::alta_proceso_espera(map<string, Prioritat>::iterator& it, const Proces& proces) {
    it -> second.añadir_proceso(proces);
    
}

void Area_de_espera::enviar_procesos_cluster(int& n, Cluster& cl) {
    map<string, Prioritat>::iterator it = prioritats.begin();
    while (n > 0 and it != prioritats.end()) {
        it -> second.enviar_procesos_cluster(n, cl);
        ++it;
    }
}

//Consultoras

bool Area_de_espera::existeix_prioritat(const string& ID_Prioritat, map<string, Prioritat>::iterator& it) {
    it = prioritats.find(ID_Prioritat);
    return (it != prioritats.end());
}

bool Area_de_espera::existeix_prioritat(const string& ID_Prioritat) const {
    if(prioritats.count(ID_Prioritat) == 1) return true;
    return false;
}

bool Area_de_espera::prioritat_existeix_proces(const int& proces, map<string, Prioritat>::iterator it) const {
    return it -> second.existeix_proces(proces); 
}

bool Area_de_espera::prioritat_te_processos(const map<string, Prioritat>::iterator& it) const {
    return it -> second.existeixen_processos();
}

//Escritura

void Area_de_espera::imprimir_prioridad(map<string, Prioritat>::iterator& it) {
    it -> second.imprimir_prioridad();
}

void Area_de_espera::imprimir_area_espera() const {
    for (map <string, Prioritat>::const_iterator it = prioritats.begin(); it != prioritats.end(); ++it) {
        cout << it -> first << endl;
        it -> second.imprimir_prioridad();
    }
}

