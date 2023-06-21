// Pablo González Corredor y Alejandro Magarzo Gonzalo

#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>

using namespace std;


const int GRADO_MAX = 5000;

class Polinomio {
public:
	Polinomio();
	void anyadir_monomio(int coef, int exp);
	long evaluar(int valor);
private:
	int coeficientes[GRADO_MAX];
};



int main() {
	int n, valor;
	cin >> n;
	while (n != 0) {
		cin >> valor;
		int i = 0;
		Polinomio p;
		while (i < n) {
			int coef, exp;
			cin >> coef;
			cin >> exp;
			p.anyadir_monomio(coef, exp);
			i++;
		}
		cout << p.evaluar(valor) << endl;
		cin >> n;
	}

	return 0;
}

Polinomio::Polinomio() {
	for (int i = 0; i < GRADO_MAX; i++) {
		coeficientes[i] = 0;
	}
	// Coste: Inicializa todas las posiciones del array a 0 y por tanto es coste n, tamaño del arrray, que es GRADO_MAX, y por tanto 
	// es de coste lineal (O(n)).
}

void Polinomio::anyadir_monomio(int coef, int exp) {
	if (coeficientes[exp] != 0) coeficientes[exp] = coeficientes[exp] + coef;
	else coeficientes[exp] = coef;
	// Coste: Añade un monomio al polinomio y es de coste constante, no hay ninguna iteración. Es coste constante que se representa (O(1)).
}



long Polinomio::evaluar(int valor) {
	long sol = 0;
	long potencia = 1;
	for (int i = 0; i < GRADO_MAX; i++) {
		sol = sol + (coeficientes[i] * potencia);
		potencia = potencia * valor;

	}
	return sol;
	// Coste: Dado un valor calcula el resultado del polinomio y por tanto recorrerá todas las posiciones del array de tamaño n, GRADO_MAX,
	// y por ello el coste es lineal (O(n)).
}