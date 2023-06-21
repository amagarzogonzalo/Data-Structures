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
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

void mostrar_ganadores(const std::set <string>& ganadores) {
	for (auto it = ganadores.begin(); it != ganadores.end(); it++) 
		cout << *it << " ";
	
	cout << endl;
}

bool resolver_caso(std::map<int, std::unordered_set<string>>& numero_jugadores, int num, std::map <string, int>& jugador_numeros_restantes, std::set <string>& ganadores) {
	bool ok = false;
	if (numero_jugadores.count(num) >= 1) {
		auto it = numero_jugadores[num];
		for (auto j = it.begin(); j != it.end(); j++) {
			jugador_numeros_restantes[(*j)] = jugador_numeros_restantes[(*j)] - 1;
			if (jugador_numeros_restantes[(*j)] == 0) {
				ok = true;
				ganadores.insert((*j));
			}
		}
	}
	

	return ok;
}

bool tratar_caso() {
	int n; cin >> n;
	if (n == 0) return false;
	else {
		std::map<int, std::unordered_set<string>> numero_jugadores;
		std::map <string, int> jugador_numeros_restantes;
		while (n > 0) {
			std::string jug;
			cin >> jug;
			int c, numeros_jug = 0;
			cin >> c;
			while (c != 0) {
				if (numero_jugadores.count(c) >= 1) {
					numero_jugadores.at(c).insert(jug);
				}
				else {
					std::unordered_set<string> jugs;
					jugs.insert(jug);
					numero_jugadores.insert({c, jugs});
				}
				cin >> c;
				numeros_jug++;
			}
			jugador_numeros_restantes.insert({jug, numeros_jug});
			n--;
		}
		int num;
		bool ok = false;
		std::set <string> ganadores;
		while (!ok) {
			cin >> num;
			ok = resolver_caso(numero_jugadores, num, jugador_numeros_restantes, ganadores);
			if (ok) mostrar_ganadores(ganadores);
		}
		return true;
	}
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
