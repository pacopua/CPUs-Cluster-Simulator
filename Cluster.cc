/** @file Cluster.cc
    @brief archivo .cc de la clase Cluster
*/

#include "Cluster.hh"

//Constructora

Cluster::Cluster() {
    temps = 0;
}

//Modificadoras

BinTree<string> Cluster::llegir_BinTree() {
    string ID_cpu;
    cin >> ID_cpu;
    
    if (ID_cpu != "*") {
        int capacitat;
        cin >> capacitat;

        Cpu p;
        p.asignar_valores_cpu(ID_cpu, capacitat);
        mapa.insert(make_pair(ID_cpu, p));

        BinTree<string> left = llegir_BinTree();
        BinTree<string> right = llegir_BinTree();

        return BinTree<string>(ID_cpu, left, right);
    }

    else {
        return BinTree<string>();
    }
}

void Cluster::configurar_cluster() {
    mapa.clear();
    b = llegir_BinTree();
}

//Modificadoras

bool Cluster::inmersio_modificar_cluster(BinTree<string>& arb, const string& cpu) {
    if (arb.empty()) return false;
    if (arb.value() == cpu) {
        if (not arb.left().empty() or not arb.right().empty()) {
        cout << "error: procesador con auxiliares" << endl;
        return true;
        }
        mapa.erase(arb.value());
        arb = llegir_BinTree();
        return true;
    }
    else {
        bool trobat = false;
        BinTree<string> left = arb.left();
        trobat = inmersio_modificar_cluster(left, cpu);
        if (not trobat) {
            BinTree<string> right = arb.right();
            trobat = inmersio_modificar_cluster(right, cpu); 

            arb = BinTree<string>(arb.value(), left, right);
            return trobat;
        }

        arb = BinTree<string>(arb.value(), left, arb.right());
        return trobat;
    }
}

void Cluster::modificar_cluster(const string& cpu) {
    // "b" es un BinTree<string> 
    if (b.value() == cpu) {
        if (not b.left().empty() or not b.right().empty()) {
            cout << "error: procesador con auxiliares" << endl;
            return;        
        }
        mapa.erase(b.value());
        b = llegir_BinTree();
        return;
    }
    else {
        bool trobat = false;
        BinTree<string> left = b.left();
        trobat = inmersio_modificar_cluster(left, cpu);
        if (not trobat) {
            BinTree<string> right = b.right();
            trobat = inmersio_modificar_cluster(right, cpu); 

            b = BinTree<string>(b.value(), left, right);
            return;
        }

        b = BinTree<string>(b.value(), left, b.right());
        return;
    }

}

void Cluster::compactar_memoria_cluster() {
    if (not mapa.empty()) {
        for (map <string, Cpu>::iterator it = mapa.begin(); it != mapa.end(); ++it) {
            it -> second.compactar_memoria_procesador();
        }
    }
}

void Cluster::compactar_memoria_cpu(map<string, Cpu>::iterator& it) {
    it -> second.compactar_memoria_procesador();
}

void Cluster::alta_proceso_procesador(map <string, Cpu>::iterator& it, Proces& proces) {
    it -> second.alta_proceso_procesador(proces);
}

void Cluster::baja_proceso_procesador(map <string, Cpu>::iterator& it, const int& proces) {
    it -> second.baja_proceso_procesador(proces);
}

void Cluster::avanzar_tiempo(const int& t) {
    map <string, Cpu>::iterator it = mapa.begin();
    while (it != mapa.end()) {
        it -> second.avanzar_tiempo(t);
        ++it;
    }
}

//Escritoras

void Cluster::imprimir_procesador(map<string, Cpu>::iterator& it) const {
    it -> second.imprimir_procesador();
}

void inmersion_imprimir_estructura(BinTree<string> b) {
    cout << '(' << b.value(); 
    if (not b.left().empty()) inmersion_imprimir_estructura(b.left());
    else cout <<' ';

    if (not b.right().empty()) inmersion_imprimir_estructura(b.right());
    else cout << ' ';
    cout << ')';
}

void Cluster::imprimir_estructura() const {
    cout << '(' << b.value();
    
    if (not b.left().empty()) inmersion_imprimir_estructura(b.left());
    else cout << ' ';

    if (not b.right().empty()) inmersion_imprimir_estructura(b.right());
    else cout << ' ';
    
    cout << ')' << endl;
}

void Cluster::imprimir_procesadores() const {
    if (not mapa.empty()) {
        map<string, Cpu>::const_iterator it = mapa.begin();
        while (it != mapa.end()) {
            it -> second.imprimir_ID();
            it -> second.imprimir_procesador();
            ++it;
        }
    }
}

//Consultoras

void Cluster::checkear_arbol_dist_esqu(const BinTree<string>& arb, list<string>& l) {
    if (not arb.empty()) {
        queue <BinTree<string>> c;
        c.push(arb);
        while (not c.empty()) {
            BinTree<string> aux(c.front());
            l.insert(l.end(), aux.value());
            if (not aux.left().empty()) c.push(aux.left());
            if (not aux.right().empty()) c.push(aux.right());
            c.pop();
        }
    }
}

bool Cluster::eleccio_cpu(string& ID, Proces& p) {

    int ocupa = p.consultar_memoria();
    int ID_proces = p.consultar_ID();
    map<string, Cpu>::const_iterator it = mapa.begin();
    
    ID = it -> first;
    int memoria = it -> second.consultar_memoria_lliure();
    int hueco_min = it -> second.tamaño_hueco_minimo(ocupa, ID_proces);

    ++it;

    string ID_aux;
    int memoria_aux;
    int hueco_min_aux;

    set<string> Cpus;
    Cpus.insert(ID);

    while (it != mapa.end()) {

        ID_aux = it -> first;
        hueco_min_aux = it -> second.tamaño_hueco_minimo(ocupa, ID_proces);
        if (hueco_min_aux != -1) {

            if (hueco_min_aux < hueco_min or hueco_min == -1) {
                ID = ID_aux;
                hueco_min = hueco_min_aux;
                memoria = it -> second.consultar_memoria_lliure();
                Cpus.clear();
                Cpus.insert(ID);
            }

            else if (hueco_min_aux == hueco_min) {

                memoria_aux = it -> second.consultar_memoria_lliure();
                
                if (memoria_aux > memoria) {
                    ID = ID_aux;
                    hueco_min = hueco_min_aux;
                    memoria = memoria_aux;
                    Cpus.clear();
                    Cpus.insert(ID);
                }
                
                else if (memoria_aux == memoria) Cpus.insert(ID_aux);
            }
        }
        ++it;
    }

    if (hueco_min == -1) return false;
    if (Cpus.size() == 1) return true;
    else {
        //int pos_esq = 1;
        list<string> l;
        checkear_arbol_dist_esqu(b, l);
        for (list<string>::iterator it_list = l.begin(); it_list != l.end(); ++it_list) {
            if (Cpus.count(*it_list) == 1) {
                ID = *it_list;
                return true;
            }
        }
        return false;
    }
    
}

map<string, Cpu>::iterator Cluster::buscar_procesador(string& ID_Cpu) {
    return mapa.find(ID_Cpu);
}

bool Cluster::existeix_cpu(const string& cpu, map <string, Cpu>::iterator& it){
    it = mapa.find(cpu);
    return (it != mapa.end());
}

bool Cluster::cpu_te_procesos(map <string, Cpu>::iterator& it) const {
    return (it -> second.te_processos());
}

bool Cluster::cpu_existeix_proces(map <string, Cpu>::iterator& it,const int& proces) const {
    return (it -> second.existeix_proces(proces));
}