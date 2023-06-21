#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

using x = string;

class libreria {
public:
	libreria() {}
	void nuevoLibro(int num, string nom) {
		if (libros.count(nom) == 0) libros.insert({ nom, num });
		else libros[nom] = libros[nom] + num;
	}

	void comprar(string nom) {
		if (libros.count(nom) == 0) throw std::invalid_argument("Libro no existente");
		else if (libros[nom] == 0) throw std::out_of_range("No hay ejemplares");
		else {
			libros[nom]--;
			if (ventas.count(nom) == 0) ventas.insert({ nom, 1 });
			else ventas[nom]++;
		}
	}

	bool estaLibro(string nom){
		if (libros.count(nom) != 0) return true;
		else return false;
	}

	void elimLibro(string nom) {
		if (libros.count(nom) != 0) libros.erase(nom);
	}

	bool numEjemplares(string nom, int& nums) {
		if (libros.count(nom) != 0) {
			nums = libros[nom];
			return true;
		}
		else {
			throw std::invalid_argument("Libro no existente");
			return false;
		}
	}

	void top10() {
		int i = 0;
		cout << "TOP10" << endl;
		auto it = ventas.begin();
		while (i < 10 && i < ventas.size()) {
			cout << "    " << (*it).first << endl;
			i++;
			it++;
		}
	}

private:
	std::unordered_map<x, int> libros;
	std::unordered_map<x,int> ventas;
};

bool tratar_caso() {
	int n;
	cin >> n;
	if (cin.eof()) return false;
	libreria l;
	int i = 0; string op;
	while (i < n) {
		cin >> op;
		try {
			if (op == "nuevoLibro") {
				int num; string nom; 
				cin >> num; cin.ignore(); std::getline(std::cin, nom);
				l.nuevoLibro(num, nom);
			}
			else if (op == "comprar") {
				string nom; cin.ignore(); getline(cin, nom);
				l.comprar(nom);
			}
			else if (op == "estaLibro") {
				string nom; cin.ignore(); getline(cin, nom);
				if (l.estaLibro(nom)) cout << "El libro " << nom << " esta en el sistema" << endl;
				else cout << "No existe el libro " << nom << " en el sistema" << endl;
			}
			else if (op == "elimLibro") {
				string nom; cin.ignore(); getline(cin, nom);
				l.elimLibro(nom);
			}
			else if (op == "numEjemplares") {
				string nom; cin.ignore(); getline(cin, nom);
				int nums;
				if (l.numEjemplares(nom, nums)) cout << "Existen " << nums << " ejemplares del libro " << nom << endl;
				else cout << "No existe el libro " << nom << " en el sistema" << endl;
			}
			else if (op == "top10") l.top10();  
		}
		catch (exception &e) {
			cout << "ERROR " << e.what() << endl;
		}
		i++;
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