/** @file Prioritat.cc
    @brief archivo .cc de la clase Prioritat
*/

#include "Prioritat.hh"
using namespace std;

//Constructora

Prioritat::Prioritat() {
    proces_enviats = 0;
    proces_denegats = 0;
    processos = {};
}

//Modificadoras

void Prioritat::añadir_proceso(const Proces& proces) {
    processos.push_back(proces);
}

void Prioritat::enviar_procesos_cluster(int& n, Cluster& cl) {
    list<Proces>::iterator it = processos.begin();
    int i = processos.size();
    while (n > 0 and  i > 0) {
        
        string ID_cpu;
        if (cl.eleccio_cpu(ID_cpu, *it)) {
            map<string, Cpu>::iterator it2 = cl.buscar_procesador(ID_cpu);
            cl.alta_proceso_procesador(it2, *it);
            it = processos.erase(it);
            --n;
            ++proces_enviats;
        }
        else {
            processos.insert(processos.end(), *it);
            it = processos.erase(it);
            ++proces_denegats;
        }
        --i;
    }
}

//Escritoras

void Prioritat::imprimir_prioridad() const {
    
    if (not processos.empty()) {
        for (list<Proces>::const_iterator it = processos.begin(); it != processos.end(); ++it) {
            it -> imprimir();
        }
    }
    cout << proces_enviats << " " << proces_denegats << endl;
}

//Consultoras

bool Prioritat::existeix_proces(const int& proces) const {
    bool existeix = false;
    if (not processos.empty()) {
        list<Proces>::const_iterator it = processos.begin();
        while(it != processos.end() and (not existeix)) {
            if (it -> consultar_ID() == proces) existeix = true;
            ++it;
        }
    }
    return existeix;
}

bool Prioritat::existeixen_processos() const {
    return (not processos.empty());
}