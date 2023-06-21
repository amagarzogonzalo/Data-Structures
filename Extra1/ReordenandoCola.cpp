#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;




bool tratar_caso() {
	int n;
	cin >> n;
	if (n == 0) return false;
	else {
		std::queue <int> c;
		std::stack <int> aux;
		int a; 
		for (int i = 0; i < n; i++) {
			cin >> a;
			if (a < 0) aux.push(a);
			else c.push(a);
		}
		while (!aux.empty()) {
			cout << aux.top() << " ";
			aux.pop();
		}
		while (!c.empty()) {
			cout << c.front() << " ";
			c.pop();
		}
		cout << endl;
	
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
