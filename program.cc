/** @file progam.cc
    @brief El programa main
*/

/** @mainpage Página Principal:
 * Simulación del funcionamiento de una arquitectura multiprocesador, con procesadores que contienen
 * cada uno memoria exclusiva, con ejecución de procesos simultaneos
*/

#include "Area_de_espera.hh"
#include "Cluster.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#endif
using namespace std;
/** @brief Se inicializan el cluster y el Area de espera que usaremos. El main recibe los comandos que nos permitirán 
 * modificar el Area de espera y el cluster, añadiendo y eliminando procesos, prioridades, procesadores... 
*/

int main() {
Cluster cl;
cl.configurar_cluster();

Area_de_espera ade;
ade.llegir_area_de_espera();

string command;
cin >> command;
while (command != "fin") {

	if (command == "configurar_cluster" or command == "cc") {
		cout << "#" << command << endl;
		cl.configurar_cluster();
	}

	else if (command == "modificar_cluster" or command == "mc") {
		string cpu;
		cin >> cpu;

		cout << "#" << command << " " << cpu << endl;

		map<string, Cpu>::iterator it;

		if (not cl.existeix_cpu(cpu, it)) cout << "error: no existe procesador" << endl;
		else if (cl.cpu_te_procesos(it)) cout << "error: procesador con procesos" << endl;
		else cl.modificar_cluster(cpu);
	}

	else if (command == "alta_prioridad" or command == "ap")    {
		string prioritat;
		cin >> prioritat;

		cout << "#" << command << " " << prioritat << endl;
		
		if (ade.existeix_prioritat(prioritat)) cout << "error: ya existe prioridad" << endl;
		
		else ade.alta_prioridad(prioritat);
	}

	else if (command == "baja_prioridad" or command == "bp") {
		string prioritat;
		cin >> prioritat;

		cout << "#" << command << " " << prioritat << endl;

		map<string, Prioritat>::iterator it;
		if (not ade.existeix_prioritat(prioritat, it)) cout << "error: no existe prioridad" << endl;
		else if (ade.prioritat_te_processos(it)) cout << "error: prioridad con procesos" << endl;
		
		else ade.baja_prioridad(it);
	}

	else if (command == "alta_proceso_espera" or command == "ape") {
		string prioritat;
		cin >> prioritat;
		
		Proces p;
		p.llegir();

		cout << "#" << command << " " << prioritat << " " << p.consultar_ID() << endl;

		map<string, Prioritat>::iterator it;
		if (not ade.existeix_prioritat(prioritat, it)) cout << "error: no existe prioridad" << endl;
		else if (ade.prioritat_existeix_proces(p.consultar_ID(), it)) cout << "error: ya existe proceso" << endl;
		else ade.alta_proceso_espera(it, p); 
	}

	else if (command == "alta_proceso_procesador" or command == "app") {
		string cpu;
		cin >> cpu;
		
		Proces proces;
		proces.llegir();

		cout << "#" << command << " " << cpu << " " << proces.consultar_ID() << endl;

		map <string, Cpu>::iterator it;

		if (not cl.existeix_cpu(cpu, it)) cout << "error: no existe procesador" << endl;
		else if (cl.cpu_existeix_proces(it, proces.consultar_ID())) cout << "error: ya existe proceso" << endl;
		else cl.alta_proceso_procesador(it, proces);
	}

	else if (command == "baja_proceso_procesador" or command == "bpp"){
		string cpu;
		int proces;
		cin >> cpu >> proces;

		cout << "#" << command << " " << cpu << " " << proces << endl;

		map <string, Cpu>::iterator it;

		if (not cl.existeix_cpu(cpu, it)) cout << "error: no existe procesador" << endl;
		else if (not cl.cpu_existeix_proces(it, proces)) cout << "error: no existe proceso" << endl;

		else cl.baja_proceso_procesador(it, proces);
	}

	else if (command == "enviar_procesos_cluster" or command == "epc") {
		int n;
		cin >> n;

		cout << "#" << command << " " << n << endl;

		ade.enviar_procesos_cluster(n, cl);
	} 

	else if (command == "avanzar_tiempo" or command == "at") {
		int tiempo;
		cin >> tiempo;

		cout << "#" << command << " " << tiempo << endl;

		cl.avanzar_tiempo(tiempo);
	}

	else if (command == "imprimir_prioridad" or command == "ipri") {
		string prioridad;
		cin >> prioridad;

		cout << "#" << command << " " << prioridad << endl;

		map<string, Prioritat>::iterator it;

		if (not ade.existeix_prioritat(prioridad, it)) cout << "error: no existe prioridad" << endl;
		else ade.imprimir_prioridad(it);
	}

	else if (command == "imprimir_area_espera" or command == "iae") {

		cout << "#" << command << endl;

		ade.imprimir_area_espera();
	}

	else if(command == "imprimir_procesador" or command == "ipro") {
		string cpu;
		cin >> cpu;

		cout << "#" << command << " " << cpu << endl;

		map<string, Cpu>::iterator it;

		if (not cl.existeix_cpu(cpu, it)) cout << "error: no existe procesador" << endl;
		else cl.imprimir_procesador(it);
	}

	else if (command == "imprimir_procesadores_cluster" or command == "ipc") {
		
		cout << "#" << command << endl;
		
		cl.imprimir_procesadores();
	}

	else if (command == "imprimir_estructura_cluster" or command == "iec") {

		cout << "#" << command << endl;

		cl.imprimir_estructura();
	}

	else if (command == "compactar_memoria_procesador" or command == "cmp"){
		string cpu;
		cin >> cpu;

		cout << "#" << command << " " << cpu << endl;

		map<string, Cpu>::iterator it;

		if (not cl.existeix_cpu(cpu, it)) cout << "error: no existe procesador" << endl;
		else cl.compactar_memoria_cpu(it);
	}

	else if (command == "compactar_memoria_cluster" or command == "cmc") {

		cout << "#" << command << endl;

		cl.compactar_memoria_cluster();
	}
	cin >> command;

}
}
