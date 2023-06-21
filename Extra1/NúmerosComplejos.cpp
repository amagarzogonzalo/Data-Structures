#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class Complejo {
private: 
	float real;
	float imaginario;

public:
	Complejo() {}
	Complejo(float r, float i) : real(r), imaginario(i) {}
	Complejo operator+(Complejo &other) {
		return Complejo{ this->real + other.real ,  this->imaginario + other.imaginario };
	}
	Complejo operator*(Complejo &other) {
		return Complejo{ (this->real * other.real) - (this->imaginario * other.imaginario) ,  (this->real * other.imaginario) + (this->imaginario * other.real) };
	}
	int modulo() {
		return sqrt((this->real*this->real) + (this->imaginario*this->imaginario));
	}
};



void tratar_caso() {
	float r, i;
	int n;
	cin >> r; cin >> i;
	cin >> n;
	Complejo c = { r,i };
	Complejo anterior = c;
	bool ok = true;
	for (int i = 1; i < n && ok; i++) {
		Complejo result = anterior.operator*(anterior);
		result = result.operator+(c);
		anterior = result;
		if (result.modulo() > 2) ok = false;

	}

	if (ok) cout << "SI" << endl;
	else cout << "NO" << endl;
}



int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int num_casos; cin >> num_casos;
	while (num_casos > 0) {
		tratar_caso();
		num_casos--;
	}


#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//Descomentar si se trabaja en Windows
	system("PAUSE");
#endif
	return 0;
}