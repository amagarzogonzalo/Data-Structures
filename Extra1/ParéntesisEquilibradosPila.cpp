#include <iostream>
#include <stack> 
#include <string>
#include <fstream>
#include <string>

using namespace std;

bool tratar_caso() {
	string line;
	getline(cin, line);
	cout << line << endl;
	if (line.empty()) return false;
	char a;
	std::stack <char> s;
	for (int i = 0; i < line.length(); i++) {
		a = line[i];
		if (a == '(' || a == '{' || a == '[') s.push(a);
		else if (!s.empty()) {
			if (a == ')' && s.top() == '(') s.pop();
			else if (a == '}' && s.top() == '{') s.pop();
			else if (a == ']' && s.top() == '[') s.pop();
			else if (a == ')' || a == ']' || a == '}') s.push(a);
		}
		else if (a == ')' || a == ']' || a == '}') s.push(a);
	}

	if (s.empty()) cout << "SI" << endl;
	else cout << "NO" << endl;
	
	return true;
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