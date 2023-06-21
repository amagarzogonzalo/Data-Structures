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
#include <map>

using namespace std;

using jugador = std::string;

class Buscaminas {
public:
	Buscaminas() {	
		num_minas = 0;
		initBordes();
	}
	// O (1)

	void anyadir_mina(int x, int y) {
		auto it = minas.find(x);
		if (it == minas.end()) {
			minas.insert({ x,{y} });
			if (num_minas == 0) {
				min_x = x; max_x = x;
				min_y = y; max_y = y;
			}
			else {
				if (x < min_x) min_x = x;
				else if (x > max_x) max_x = x;
				if (y < min_y) min_y = y;
				else if (y > max_y) max_y = y;
			}
			num_minas++;
		}
		else if ((*it).second.count(y) == 0) {
			(*it).second.insert(y);
			if (y < min_y) min_y = y;
			else if (y > max_y) max_y = y;
			num_minas++;
		}
	}
	// O(1)

	void anyadir_jugador(jugador j) {
		if (jugadores.count(j) >= 1) throw std::invalid_argument("Jugador existente");
		else jugadores.insert({j ,0});
	}
	// O(1)

	int explorar(jugador j, int x, int y) {
		if (jugadores.count(j) == 0) throw std::invalid_argument("Jugador no existente");
		else {
			int minas_cercanas = 0;
			for (auto c = minas.begin(); c != minas.end(); c++) {
				if ((*c).first == x || (*c).first == (x + 1) || (*c).first == (x - 1)) {
					for (auto  f = (*c).second.begin(); f != (*c).second.end(); f++) {
						if ((*f) == (y + 1) || (*f) == (y - 1) || ((*f) == y && x!= (*c).first)) minas_cercanas++;
						else if ((*f) == y && x == (*c).first) {
							jugadores.erase(j);
							return -1;
						}
					}
				}
			}
			return minas_cercanas;
		}
	}
	// O(filasxcol) = O(num_minas)

	bool bandera(jugador j, int x, int y) {
		if (jugadores.count(j) == 0) throw std::invalid_argument("Jugador no existente");
		else {
			int minas_cercanas = explorar(j,x,y);
			if (minas_cercanas == -1) {
				jugadores[j] += 1;
				return true;
			}
			else {
				jugadores[j] -= 5;
				return false;
			}
		}
	}
	// O(num_minas) de explorar() + O(1) = O(num_minas)

	int puntuacion(jugador j) {
		if (jugadores.count(j) == 0) throw std::invalid_argument("Jugador no existente");
		else return jugadores[j];
	}
	// O(1)

	int getNum_minas() {
		return num_minas;
	}
	// O(1)

	bool bordes_tablero(int &min_x, int &min_y, int &max_x, int &max_y) {
		if (num_minas == 0) throw std::domain_error("Tablero vacio");
		else {
			min_x = this->min_x; min_y = this->min_y; max_x = this->max_x; max_y = this->max_y;
			return true;
		}
	}
	// O(1)

private:
	std::unordered_map<jugador, int> jugadores;
	std::unordered_map <int, unordered_set<int>> minas; 
	int num_minas, min_x, min_y, max_x, max_y;

	void initBordes() {
		min_x = -1;
		min_y = -1;  
		max_x = -1;
		max_y = -1;
	}
	// O(1)

};


bool tratar_caso() {
	bool fin = false;
	std::string tmp;
	Buscaminas b;
	while (!fin) {
		int x, y; string j;
		cin >> tmp;
		try {
			if (tmp == "FIN") fin = true;
			else if (tmp == "mina") {
				cin >> x; cin >> y;
				b.anyadir_mina(x, y);
				cout << b.getNum_minas() << endl;
			}
			else if (tmp == "jugador") {
				cin >> j;
				b.anyadir_jugador(j);
			}
			else if (tmp == "explorar") {
				cin >> j;
				cin >> x; cin >> y;
				int minas_cercanas = b.explorar(j, x, y);
				if (minas_cercanas == -1) cout << "Has perdido" << endl;
				else cout << minas_cercanas << endl;

			}
			else if (tmp == "bandera") {
				cin >> j;
				cin >> x; cin >> y;
				bool ok = b.bandera(j, x, y);
				if (ok) cout << "Si ";
				else cout << "No ";
				cout << b.puntuacion(j) << endl;

			}
			else if (tmp == "bordes") {
				try {
					int min_x, min_y, max_x, max_y;
					bool ok = b.bordes_tablero(min_x, min_y, max_x, max_y);
					if(ok) cout << min_x << " " << min_y << " " << max_x << " " << max_y << endl;
				}
				catch (std::domain_error& e) {
					cout << e.what() << endl;
				}
			}
			else return false;
		} catch (std::invalid_argument& e) {
			cout << e.what() << endl;
		}
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
	// system("PAUSE");
#endif
	return 0;
}
