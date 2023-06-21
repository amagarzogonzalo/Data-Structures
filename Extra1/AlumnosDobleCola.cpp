#include <iostream>
#include <fstream>
#include <list>

using namespace std;

int resolver(std::list<int> d, int s) {
	int sol, cont = 1;
	bool b = false;
	auto it = d.begin();
	while (!b) {
		int a = *it;
		if (cont == (s + 1)) {
			cont = 1;
			auto i = it;
			i++;
			d.erase(it);
			if (i == d.end()) it = d.begin();
			else it = i;
			if (d.size() == 1) {
				b = true;
				sol = *it;
			}
		}
		else {
			it++;
			if (it == d.end()) it = d.begin();
			cont++;
		}
	}
	return sol;
}

bool tratar_caso() {
	int n, s;
	cin >> n >> s;
	if (n == 0 && s == 0) return false;
	else {
		std::list <int> d;
		for (int i = 1; i < n + 1; i++)
			d.push_back(i);
		cout << resolver(d, s) << endl;
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
	system("PAUSE");
#endif

	return 0;
}