/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 * Indica el nombre y apellidos de los componentes del
 * grupo:
 *
 * Nombre 1: Pablo González Corredor
 * Nombre 2: Alejandro Magarzo Gonzalo
 * ---------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <list>

using namespace std;

bool es_toeplitz(const list<list<int>> &matriz) {
	bool ok = true, recorrido = true;
	auto current = matriz.begin();
	auto next = matriz.begin(); next++;
	while (ok && next != matriz.end()) {
		auto c = *current; auto n = *next;
		auto numCurrent = c.begin(); auto numNext = n.begin(); numNext++;
		while (ok && numNext != n.end()) {
			if (*numCurrent != *numNext) ok = false;
			numCurrent++;
			numNext++;
		}
		current++;
		next++;
	}
	return ok;
}
// Coste: Cuadrático O(nxm): siendo n el número de listas y m el número de elementos de cada lista.
// El coste en el caso peor será si el algoritmo es toeplitz ya que se realizaran todas las iteraciones posibles y ok será siempre true.
// En dicho caso el primer while se realizará mientras que la lista next sea distinto de end, es decir el numero de listas - 1 veces.
// Por otra parte el segundo bucle while, el interior, recorrerá todos los elementos de la lista numNext - 1 y todos los elementos de la lista
// numCurrent -1. Como conclusión, el coste sera cuadrático O((n-1) x (m-1)) equivalente a O(n x m), siendo n el número de listas de la matriz y 
// m el número de elementos de cada lista.

bool tratar_caso() {
	list <list<int>> matriz;
	int a; 
	cin >> a;
	if (a == 0) return false;
	while (a != 0) {
		list<int> lista;
		while (a != 0) {
			lista.push_back(a);
			cin >> a;
		}
		matriz.push_back(lista);
		cin >> a;
	}
	bool ok = es_toeplitz(matriz);
	if (ok) cout << "SI" << endl;
	else cout << "NO" << endl;
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
	system("PAUSE");
#endif

	return 0;
}