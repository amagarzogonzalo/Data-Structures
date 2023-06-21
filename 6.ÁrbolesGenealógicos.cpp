/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 * Indica el nombre y apellidos de los componentes del
 * grupo:
 *
 * Nombre 1: Pablo González Corredor
 * Nombre 2: Alejandro Magarzo Gonzalo
 * ---------------------------------------------------
 */



#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cassert>

class Date {
public:
	Date() : day(10), month(10), year(2000) {}
	Date(int day, int month, int year) :day(day), month(month), year(year) {}

	bool operator<(const Date &other) const;
	bool operator<=(const Date &other) const;
	
	void read(std::istream &in);

private:
	int day;
	int month;
	int year;
};

std::istream & operator>>(std::istream &in, Date &f) {
	f.read(in);
	return in;
}

class FamilyTree {
public:
	FamilyTree() {
		root = nullptr;
	}
	~FamilyTree() {
		int n = root->children.size();
		delete_with_children(root, n);
		delete root;
	}
	void read(std::istream &in);
	bool nonsense();

private:
	struct FamilyTreeNode {
		Date date;
		std::vector<FamilyTreeNode *> children;
	};

	FamilyTreeNode *root;
	void helpRead(std::istream &in, int h, FamilyTreeNode* father);
	bool helpNonsense(FamilyTreeNode* father, int size, bool& ok);
	void delete_with_children(FamilyTreeNode *node, int n) {
		int i = 0;
		while (i < n) {
			FamilyTreeNode* son = node->children.at(i);
			int size_son = son->children.size();
			if (size_son > 0)delete_with_children(son, size_son);
			i++;
		}
	}
};

std::istream & operator>>(std::istream &in, FamilyTree &f) {
	f.read(in);
	return in;
}

using namespace std;

void tratar_caso() {
	FamilyTree f;
	f.read(cin);
	if(f.nonsense()) cout << "SI" << endl;
	else cout << "NO" << endl;
}

int main() {
	
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int num_casos;
	cin >> num_casos;
	for (int i = 0; i < num_casos; i++) {
		tratar_caso();
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//Descomentar si se trabaja en Windows
	system("PAUSE");
#endif
	return 0;
}

bool Date::operator<(const Date & other) const{
	if (this->year < other.year) return true;
	else if (this->year == other.year) {
		if (this->month < other.month) return true;
		else if (this->month == other.month) {
			if (this->day < other.day) return true;
			else return false;
		}
		else return false;
	}
	else return false;
}

bool Date::operator<=(const Date & other) const{
	return ((this->day == other.day && this->month == other.month && this->year == other.year) || this->operator<(other));

}

void Date::read(std::istream & in){
	char a;
	in >> a;
	this->day = a - '0';
	while (a != '/') {
		in >> a;
		if (a != '/') {
			int b = a - '0';
			this->day = (this->day * 10) + b;
		}
	}
	in >> a;
	this->month = a - '0';
	while (a != '/') {
		in >> a;
		if (a != '/') {
			int b = a - '0';
			this->month = (this->month * 10) + b;
		}
	}
	this->year = 0;
	for(int i = 3; i >= 0; i--) {
		in >> a;
		int b = a - '0'; 
		this->year = this->year + (b* pow(10, i));
	}
}

void FamilyTree::read(std::istream & in){
	Date d;
	std::vector<FamilyTreeNode *> c;
	d.read(in);
	FamilyTreeNode *root_node = new FamilyTreeNode{ d, c };
	this->root = root_node;
	int h; in >> h;
	helpRead(in, h, root_node);
}

void FamilyTree::helpRead(std::istream & in, int h, FamilyTreeNode* father) {
	for (int i = 0; i < h; i++) {
		Date date;
		date.read(in);
		std::vector<FamilyTreeNode *> child;
		FamilyTreeNode *node = new FamilyTreeNode{ date, child };
		int h2; in >> h2;
		if (h2 > 0) helpRead(in, h2, node);
		father->children.push_back(node);
	}
}

bool FamilyTree::nonsense(){
	if (root == nullptr) return true;
	else {
		bool ok = false;
		FamilyTreeNode *roott = root;
		int n = roott->children.size();
		ok = helpNonsense(roott, n, ok);
		return ok;
	}
}

bool FamilyTree::helpNonsense(FamilyTreeNode* father, int size, bool& ok){
	int i = 0, n = size;
	while (!ok && i < n) {
		FamilyTreeNode* son = father->children.at(i);
		int size_son = son->children.size();
		if (!father->date.operator<(son->date)) {
			ok = true;
		}
		if (size_son > 0) ok = helpNonsense(son, size_son,ok);
		i++;
	}
	return ok;
}
// Realmente el coste del algoritmo de nonsense es constante pero con la llamada y las instrucciones de helpNonsense aumenta considerablemente.
// HelpNonsense se realiza n veces por m veces, siendo n los hijos de root y m los hijos de n y así recursivamente hasta llegar al final del árbol.
// Por tanto en el caso peor tendrá un orden cuadrático O(n*m).