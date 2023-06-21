#include <iostream>
#include <fstream>
#include<unordered_map>
#include <string>

using namespace std;

class Aprobados {
private:
	unordered_map<string, int> alumnos;

public:
	 Aprobados(){
	 }
	 void registrar_alumno(string name, string result) {
		 if (alumnos.count(name) >= 1) {
			 if (result == "CORRECTO") alumnos[name] += 1;
			 else alumnos[name] -= 1;
		 }
		 else {
			 if (result == "CORRECTO") alumnos.insert({ name, 1 });
			 else alumnos.insert({ name,-1 });
		 }
	 }

	 void display() {
		 for (auto a = alumnos.begin(); a != alumnos.end(); a++) {
			if((*a).second != 0) cout << (*a).first << ", " << (*a).second << endl;
		 }
		 cout << "---" << endl;
	 }
};

bool tratar_caso() {
	int n;
	cin >> n;
	if(n == 0) return false;
	else {
		Aprobados ap;
		int i = 0;
		while (i < n) {
			string name, result;
			std:: getline(cin, name);
			cin >> result;
			ap.registrar_alumno(name, result);
			i++;
		}
		ap.display();
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
	// system("PAUSE");
#endif
	return 0;
}