#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

class Fecha {
private:
	int dia;
	int mes;
	int an;
public:
	Fecha() {}
	Fecha(int d, int m, int a) : dia(d), mes(m), an(a) {}
	void operator>>(istream& in) {
		cin >> dia;
		cin.ignore();
		cin >> mes;
		cin.ignore();
		cin >> an;
	}
	void operator<<(ostream &out) {
		if (dia < 10) out << 0;
		out << dia << "/";
		if (mes < 10) out << 0;
		out << mes << "/" << an;
	}
};

class Accidente {
public:
	int victimas;
	Fecha f;
public:
	Accidente() {}
	Accidente(int v, Fecha f) : victimas(v) {}
	bool operator>(const Accidente& other) {
		if (victimas > other.victimas) return true;
		else return false;
	}
	void operator>>(istream& in) {
		f.operator>>(in);
		cin >> victimas;
	}
	void operator<<(ostream& out) {
		f.operator<<(out); 
	}
	int getVitimas() { return victimas; }
};


bool tratar_caso() {
	int n;
	cin >> n;
	int* a; a = &n;
	if (n <= 0 || n > 250000 || a == nullptr) return false;
	stack <Accidente> s;
	stack <Accidente> sol;
	stack <Accidente> tmp;
	
	for (int i = 0; i < n; i++) {
		Accidente a;
		a.operator>>(cin);
		s.push(a);
		tmp.push(a);
	}
	
	Fecha f(0, 0, 0);
	Accidente no_hay = { -1, f };

	while (!s.empty()) {
		bool b = false;
		tmp.pop();
		while (!b && !tmp.empty()) {
			if (tmp.top().operator>(s.top())) {
				b = true;
				sol.push(tmp.top());
			}
			tmp.pop();
		}
		if (!b)sol.push(no_hay);
		s.pop();
		tmp = s;
	}

	while (!sol.empty()) {
		if (sol.top().getVitimas() == -1) cout << "NO HAY";
		else sol.top().operator<<(cout);
		cout << endl;
		sol.pop();
	}

	cout << "---" << endl;
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	tratar_caso();


#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//Descomentar si se trabaja en Windows
	system("PAUSE");
#endif
	return 0;
}
