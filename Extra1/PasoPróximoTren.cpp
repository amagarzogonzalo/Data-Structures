#include <iostream>
#include <fstream>
#include <ostream>
#include <assert.h>
#include <vector>

using namespace std;

const int MAX = 1000;

class Hora{
private: 
	int hora;
	int minuto;
	int segundo;

public:
	Hora(): hora(100), minuto(100), segundo(100){}
	Hora(int hora, int minuto, int segundo) {
		this->hora = hora;
		if (hora >= 24) this->hora = 100;
		this->minuto = minuto;
		if(minuto >= 60) this->minuto = 100;
		this->segundo = segundo;
		if (segundo >= 60) this->segundo = 100;
	}

	int getHora() { return hora; }
	int getMinuto() { return minuto; }
	int getSegundo() { return segundo; }
	bool operator<(const Hora& other);
};

void operator<<( Hora& h,ostream &out) {
	if (h.getHora() < 10) out << 0;
	out << h.getHora() << ":";
	if (h.getMinuto() < 10) out << 0;
	out << h.getMinuto() << ":";
	if (h.getSegundo() < 10) out << 0;
	out << h.getSegundo() << endl;
}


bool Hora:: operator<(const Hora & other) {
	if (this->hora < other.hora) return true;
	else if (this->hora > other.hora) return false;
	else {
		if (this->minuto < other.minuto) return true;
		else if (this->minuto > other.minuto) return false;
		else {
			if (this->segundo <= other.segundo) return true;
			else return false;
		}
	}
}

bool tratar_caso() {
	int ntrenes, nhoras;
	cin >> ntrenes; cin >> nhoras;
	if (ntrenes == 0 & nhoras == 0) return false;
	else {
		assert(ntrenes > 0 && ntrenes < 1000);
		Hora trenes[MAX];
		Hora horasc[MAX];
		
		for (int j = 0; j < ntrenes; j++) {
			int ho, mi, se;
			cin >> ho;
			cin.ignore();
			cin >> mi;
			cin.ignore();
			cin >> se;
			Hora h(ho, mi, se);
			trenes[j] = h;
		}
		for (int j = 0; j < nhoras; j++) {
			int ho, mi, se;
			cin >> ho;
			cin.ignore();
			cin >> mi;
			cin.ignore();
			cin >> se;
			Hora h(ho, mi, se);
			horasc[j] = h;
		}

		for (int i = 0; i < nhoras; i++) {
			bool found = false;
			if (horasc[i].getHora() == 100 || horasc[i].getMinuto() == 100 || horasc[i].getSegundo() == 100) {
				cout << "ERROR" << endl;
			}
			else {
				for (int j = 0; j < ntrenes && !found; j++) {
					if (horasc[i].operator<(trenes[j])) {
						found = true;
						operator<<(trenes[j], cout);
					}
				}
				if (!found) cout << "NO" << endl;
			}
		}
		cout << "---" << endl;
		return true;
	}
}


int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while(tratar_caso());
	

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//Descomentar si se trabaja en Windows
	system("PAUSE");
#endif
	return 0;
}

