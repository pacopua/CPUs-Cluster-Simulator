/** @file Cpu.cc
    @brief archivo .cc de la clase Cpu
*/

#include "Cpu.hh"

//Constructora

Cpu::Cpu() {
    ID = "#";
    capacitat = memoria_lliure = 0;
}

//Llegir

void Cpu::asignar_valores_cpu(const string& ID, const int& capacitat) {
    this -> ID = ID;
    this -> memoria_lliure = this -> capacitat = capacitat;

    set <int> p = {0};
    mapa_forats.insert(make_pair(this -> capacitat, p));
}

void Cpu::llegir() {
    cin >> ID;
    cin >> capacitat;
    memoria_lliure = capacitat;
    set <int> p = {0};
    mapa_forats.insert(make_pair(capacitat, p));
}

//Modificadoras

void Cpu::alta_proceso_procesador(Proces& proces) {
    int ocupa = proces.consultar_memoria();

    if (mapa_forats.count(ocupa) == 1) {
        map <int, set<int>>::iterator it = mapa_forats.find(ocupa);
        set<int>::iterator it2 = it -> second.begin();

        int pos = *it2;

        it -> second.erase(pos); 
        if (it -> second.empty()) mapa_forats.erase(it);
    
        memoria_lliure -= ocupa;
        mapa_posiciones.insert(make_pair(proces.consultar_ID(), pos));        
        mapa_processos.insert(make_pair(pos, proces));
    }

    else {
        map<int, set<int>>::iterator it = mapa_forats.lower_bound(ocupa);

        if(it == mapa_forats.end()) cout << "error: no cabe proceso" << endl;
        else { 
            memoria_lliure -= ocupa;
            set<int>::iterator it2 = it -> second.begin();

            int pos_forat = *it2;
            int tamany = it -> first;

            it -> second.erase(it2);

            if (it -> second.empty()) mapa_forats.erase(it);

            mapa_posiciones.insert(make_pair(proces.consultar_ID(), pos_forat));        
            mapa_processos.insert(make_pair(pos_forat, proces));

            int forat_sobrant = tamany - ocupa;
            int pos_forat_sobrant = pos_forat + ocupa;
        
            if (mapa_forats.count(forat_sobrant) == 1) {
                map <int, set<int>>::iterator seter = mapa_forats.find(forat_sobrant);
                seter -> second.insert(pos_forat_sobrant);
            }

            else {
                set<int> p = {pos_forat_sobrant};
                mapa_forats.insert(make_pair(forat_sobrant, p));
            }
        }
    }
}

void Cpu::baja_proceso_procesador(const int& proces) {
    map<int, int>::iterator it_pos = mapa_posiciones.find(proces);
    map<int, Proces>::iterator it_proc = mapa_processos.find(it_pos -> second);

    int ocupat = it_proc -> second.consultar_memoria();
    int pos = it_proc -> first;

    if (mapa_forats.count(ocupat) == 1) {
        map<int, set<int>>::iterator it_forats = mapa_forats.find(ocupat);
        it_forats -> second.insert(pos); 
    }

    else {
        //terminar esto
        set<int> p = {pos};
        mapa_forats.insert(make_pair(ocupat, p));
    }
    memoria_lliure += ocupat;
    mapa_posiciones.erase(it_pos);
    mapa_processos.erase(it_proc);
    ajustar_huecos();
}

void Cpu::ajustar_huecos() {
    mapa_forats.clear();

    int posicion_hueco = 0;
    int ocupa_hueco = 0;
    map<int, Proces>::iterator it = mapa_processos.begin();
    if (mapa_processos.empty()) {
        set<int> p = {0};
        mapa_forats.insert(make_pair(capacitat, p));
    }
    else {
        if (it -> first != 0) {
            set<int> p = {0};
            mapa_forats.insert(make_pair(it -> first, p));
        }

        while (it != mapa_processos.end()) {
        
        posicion_hueco = it -> first + it->second.consultar_memoria();
        
        if (mapa_processos.count(posicion_hueco) == 0) {
            map<int, Proces>::iterator it2 = mapa_processos.lower_bound(posicion_hueco); 
            
            if (it2 != mapa_processos.end()) {
                ocupa_hueco = it2 -> first - posicion_hueco;
                if (mapa_forats.count(ocupa_hueco) == 0) {
                    set<int> p = {posicion_hueco};
                    mapa_forats.insert(make_pair(ocupa_hueco, p));
                }
                else {
                    mapa_forats.find(ocupa_hueco) -> second.insert(posicion_hueco);
                }
            }

            else {
                ocupa_hueco = capacitat - posicion_hueco;
                if (ocupa_hueco > 0) {
                    if (mapa_forats.count(ocupa_hueco) == 0) {
                    set<int> p = {posicion_hueco};
                    mapa_forats.insert(make_pair(ocupa_hueco, p));
                    }
                    else {
                    mapa_forats.find(ocupa_hueco) -> second.insert(posicion_hueco);
                }
                }
            }
        }
        ++it;
        }
    }

}

void Cpu::avanzar_tiempo(const int& t) {
    map<int, Proces>::iterator it_processos = mapa_processos.begin();
    map<int, Proces>::iterator it_aux =  it_processos;

    while (it_processos != mapa_processos.end()) {

        ++it_processos;

        it_aux -> second.modificar_temps(t);
        if (it_aux -> second.consultar_temps() <= 0) {
            int ID = it_aux -> second.consultar_ID();
            memoria_lliure += it_aux -> second.consultar_memoria();
            mapa_posiciones.erase(mapa_posiciones.find(ID));
            mapa_processos.erase(it_aux);
        }
        it_aux = it_processos;
    }
    ajustar_huecos();
}

void Cpu::compactar_memoria_procesador() {

    if (not mapa_processos.empty()) {
        map<int, Proces>::iterator it = mapa_processos.begin();
        int pos_nova = 0;
        while (it != mapa_processos.end()) {
            Proces p = it -> second;
            int pos_antiga = it -> first;
            mapa_posiciones.find(p.consultar_ID()) -> second = pos_nova; 
            if (pos_nova != pos_antiga) { 
                mapa_processos.insert(make_pair(pos_nova, p));
                it = mapa_processos.erase(it);
            }
            else ++it;
            
            pos_nova += p.consultar_memoria();
        }

        int pos_forat = capacitat - memoria_lliure;
        mapa_forats.clear();
        if (pos_forat != capacitat) {
            set<int> x = {pos_forat};
            mapa_forats.insert(make_pair(memoria_lliure, x));
        }
    }
}


//Escritoras

void Cpu::imprimir_ID() const {
    cout << ID << endl;
}


void Cpu::imprimir_procesador() const {
    if (not mapa_processos.empty()) {
    map<int, Proces>::const_iterator it = mapa_processos.begin();
    while (it != mapa_processos.end()) {
        cout << it -> first << " ";
        it -> second.imprimir();
        ++it;
    }
    }
}

//Consultoras

int Cpu::tamaño_hueco_minimo(const int& ocupa,const int& ID_proces) const {
    if (mapa_posiciones.count(ID_proces) == 1) return -1;

    if (mapa_forats.count(ocupa) == 1) return mapa_forats.find(ocupa) -> first;
    
    map<int, set<int>>::const_iterator it = mapa_forats.lower_bound(ocupa);
    if (it != mapa_forats.end()) return it -> first;
    return -1; 
}

int Cpu::consultar_memoria_lliure() const {
    return memoria_lliure;
}

string Cpu::consultar_ID() const {
    return ID;
}

bool Cpu::te_processos() const {
    return (not mapa_processos.empty());
}

bool Cpu::existeix_proces(const int& proces) const {
    return (mapa_posiciones.find(proces) != mapa_posiciones.end());
}