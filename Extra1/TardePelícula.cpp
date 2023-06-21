#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <vector>
#include <algorithm>

using namespace std;

class Hora {
private:
	int hora;
	int minuto;
	int segundo;

public:
	Hora() : hora(100), minuto(100), segundo(100) {}
	Hora(int hora, int minuto, int segundo) {
		this->hora = hora;
		if (hora >= 24) this->hora = 100;
		this->minuto = minuto;
		if (minuto >= 60) this->minuto = 100;
		this->segundo = segundo;
		if (segundo >= 60) this->segundo = 100;
	}

	int getHora() { return hora; }
	int getMinuto() { return minuto; }
	int getSegundo() { return segundo; }
	bool operator<(const Hora& other);
	bool operator==(const Hora& other);
	Hora operator+(const Hora &other);
	Hora operator>>(istream & in);
};

class Pelicula {
public:
	string nom;
	Hora inicio;
	Hora fin;
	Hora dur;
public: 
	Pelicula() {}
	Pelicula operator>>(istream& in);
	const void display(ostream & out);
	 bool operator<(const Pelicula& other);
};


void operator<<(Hora& h, ostream &out) {
	if (h.getHora() < 10) out << 0;
	out << h.getHora() << ":";
	if (h.getMinuto() < 10) out << 0;
	out << h.getMinuto() << ":";
	if (h.getSegundo() < 10) out << 0;
	out << h.getSegundo();
}


bool Hora:: operator<(const Hora & other) {
	if (this->hora < other.hora) return true;
	else if (this->hora > other.hora) return false;
	else {
		if (this->minuto < other.minuto) return true;
		else if (this->minuto > other.minuto) return false;
		else {
			if (this->segundo <other.segundo) return true;
			else return false;
		}
	}
}

bool Hora::operator==(const Hora & other){
	return (this->hora == other.hora && this->minuto == other.minuto && this->segundo == other.segundo);
}

Hora Hora::operator+(const Hora & other){
	int tmpm = 0,seg = this->segundo + other.segundo;
	while (seg >= 60) {
		tmpm += 1;
		seg -= 60;
	}
	int tmph = 0, min = this->minuto + other.minuto + tmpm;
	while (min >= 60) {
		tmph += 1;
		min -= 60;
	}
	int hor = this->hora + other.hora + tmph;
	return Hora(hor, min,seg);
}

bool tratar_caso() {
	int n;
	cin >> n;
	if (n == 0) return false;
	else {
		std::vector <Pelicula> l;
		for (int j = 0; j < n; j++) {
			Pelicula p, pel;
			pel = p.operator>>(cin);
			//pel.display(cout);
			l.push_back(pel);
		}
		std::sort(l.begin(), l.end());
		for (int j = 0; j < n; j++) {
			l.at(j).display(cout);
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
	while (tratar_caso());


#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//Descomentar si se trabaja en Windows
	system("PAUSE");
#endif
	return 0;
}

Hora Hora::operator>>(istream& in) {
	int hor, min, seg;
	in >> hor;
	in.ignore();
	in >> min;
	in.ignore();
	in >> seg;
	Hora hora(hor, min, seg);
	return hora;
}

Pelicula Pelicula::operator>>(istream & in){
	Pelicula p;
	Hora h;
	p.inicio = h.operator>>(cin);
	p.dur = h.operator>>(cin);
	p.fin = p.inicio.operator+(p.dur);
	std::getline(std::cin,p.nom);
	return p;
}

const void Pelicula::display(ostream & out){
	operator<<(this->fin, cout);
	out << this->nom << endl;
}

 bool Pelicula::operator<(const Pelicula &other) {
	if (this->fin.operator<(other.fin)) return true;
	else if (this->fin.operator==(other.fin)) {
		if (this->nom <= other.nom) return true;
		else return false;
	}
	else return false;
}