/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
 * Comienza poniendo el nombre de los/as componentes del grupo:
 *
 * Estudiante 1: Alejandro Magarzo Gonzalo
 * Estudiante 2: Pablo González Corredor
 */


#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <list>
#include <map>
#include <vector>
#include <set>

using namespace std;

class Supermercado {
public:
	Supermercado(int _num_cajas) {
		num_cajas = _num_cajas;
	}
	// O(1)

	void nuevo_cliente(std:: string cod_cliente, int num_cola) { 
		if (num_cola >= num_cajas || num_cola < 0) throw std:: domain_error("Cola inexistente");
		else if (clientes.count(cod_cliente) != 0) throw std::domain_error("Cliente duplicado");
		else {
			colas[num_cola].push_back(cod_cliente);
			clientes[cod_cliente] = num_cola;
		}
	}
	// O(n) debido al count, siendo n el número de clientes en el TAD clientes
	
	void cambiar_cola(std::string cod_cliente, int num_cola) {
		if (num_cola >= num_cajas || num_cola < 0) throw std::domain_error("Cola inexistente");
		else if (clientes.empty() || clientes.count(cod_cliente) == 0) throw std::domain_error("Cliente inexistente");
		else if (num_cola != clientes[cod_cliente]){
			int c = clientes[cod_cliente];
			auto it = colas[c].begin(); 
			while(it != colas[c].end()){
				if ((*it) == cod_cliente) {
					colas[c].erase(it);
					break;
				}
				else ++it;
			}
			colas[num_cola].push_back(cod_cliente); 
			clientes[cod_cliente] = num_cola;
		}
	}
	// O(colas[c]); siendo c el número de cola del cliente en el TAD colas

	int consultar_cliente(std::string cod_cliente) {
		if (clientes.empty() || clientes.count(cod_cliente) == 0) throw std::domain_error("Cliente inexistente");
		else return clientes[cod_cliente]; 
	}
	// O(n) debido al cout, siendo n el número de clientes del TAD clientes

	int cuantos_en_cola(int num_cola) { 
		if (num_cola >= num_cajas || num_cola < 0) throw std::domain_error("Cola inexistente");
		else return colas[num_cola].size();
	}
	// O(n) debido al size, siendo n el tamaño de la cola[num_colas]

	list<string> clientes_en_cola(int num_cola, bool &ok) { 
		if (num_cola >= num_cajas || num_cola < 0) throw std::domain_error("Cola inexistente");
		else {
			ok = true;
			return colas[num_cola]; 
		}
	}
	// O(1)


private: 
	int num_cajas;

	std::unordered_map<int,std:: list<string>> colas;
	std::unordered_map<std::string, int> clientes; // cliente y en que cola esta
};


bool tratar_caso() {
	int num_cajas, n;
	std::string g, c;
	cin >> num_cajas;
	if (std::cin.eof()) return false;
	Supermercado s(num_cajas);
	cin >> g;
	while (g != "FIN") {
		try {
			if (g == "nuevo_cliente") {
				cin >> c >> n;
				s.nuevo_cliente(c, n);
			}
			else if (g == "cambiar_cola") {
				cin >> c >> n;
				s.cambiar_cola(c, n);
			}
			else if (g == "consultar_cliente") {
				cin >> c;
				int tmp = s.consultar_cliente(c);
				cout << "El cliente " << c << " esta en la cola " << tmp << endl;
			}
			else if (g == "cuantos_en_cola") {
				cin >> n;
				int tmp = s.cuantos_en_cola(n);
				cout << "En la cola " << n << " hay " << tmp << " clientes" << endl;
			}
			else if (g == "clientes_en_cola") {
				cin >> n;
				bool ok = false;
				std::list <std::string> c_encola = s.clientes_en_cola(n, ok);
				if (ok) {
					cout << "En la cola " << n << " estan: ";
					auto it = c_encola.end();
					while (it != c_encola.begin()) {
						--it;
						cout << (*it) << " ";
					}
					cout << endl;
				}
			}
		}
		catch (std::exception & e) {
			cout << "ERROR: " << e.what() << endl;
		}
		cin >> g;
	}

	cout << "---" << endl;
	return true;
}



int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	//system("PAUSE");
#endif
	return 0;
}