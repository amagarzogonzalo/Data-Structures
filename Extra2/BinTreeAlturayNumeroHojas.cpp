#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <algorithm>

template<class T>
class BinTree {
public:

	BinTree() : root_node(nullptr) { }

	BinTree(const T &elem) : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) { }

	BinTree(const BinTree &left, const T &elem, const BinTree &right)
		:root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) { }


	bool empty() const {
		return root_node == nullptr;
	}

	const T & root() const {
		assert(root_node != nullptr);
		return root_node->elem;
	}

	BinTree left() const {
		assert(root_node != nullptr);
		BinTree result;
		result.root_node = root_node->left;
		return result;
	}

	BinTree right() const {
		assert(root_node != nullptr);
		BinTree result;
		result.root_node = root_node->right;
		return result;
	}

	void display(std::ostream &out) const {
		display_node(root_node, out);
	}

private:
	struct TreeNode;
	using NodePointer = std::shared_ptr<TreeNode>;

	struct TreeNode {
		TreeNode(const NodePointer &left, const T &elem, const NodePointer &right) : elem(elem), left(left), right(right) { }

		T elem;
		NodePointer left, right;
	};

	NodePointer root_node;

	static void display_node(const NodePointer &root, std::ostream &out) {
		if (root == nullptr) {
			out << ".";
		}
		else {
			out << "(";
			display_node(root->left, out);
			out << " " << root->elem << " ";
			display_node(root->right, out);
			out << ")";
		}
	}

};

template<typename T>
std::ostream & operator<<(std::ostream &out, const BinTree<T> &tree) {
	tree.display(out);
	return out;
}

template<typename T>
BinTree<T> read_tree(std::istream &in) {
	char c;
	in >> c;
	if (c == '.') {
		return BinTree<T>();
	}
	else {
		assert(c == '(');
		BinTree<T> left = read_tree<T>(in);
		T elem;
		in >> elem;
		BinTree<T> right = read_tree<T>(in);
		in >> c;
		assert(c == ')');
		BinTree<T> result(left, elem, right);
		return result;
	}
}

using namespace std;

BinTree<int> leer_arbol() {
	char c;
	std::cin >> c;
	assert(c == '*' || c == '.');
	if (c == '*') {
		BinTree<int> iz = leer_arbol();
		BinTree<int> dr = leer_arbol();
		return { iz, 0, dr };
	}
	else {
		return {};
	}
}

template <typename T>
int altura(const BinTree<T> &b, int &num, int &hojas) {
	if (b.empty()) return 0;
	else {
		int ai = altura(b.left(), num, hojas);
		int ad = altura(b.right(), num, hojas);
		num++;
		int a = ad;
		if (ai > ad) a = ai;
		if (b.left().empty() && b.right().empty()) hojas++;
		return (a + 1);
	}

}

void tratar_caso() {
	BinTree<int> b = leer_arbol();
	int hojas = 0, num = 0, a;
	a = altura(b, num, hojas);
	cout << num << " " << hojas << " " << a << endl;

}



int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int n; cin >> n;
	for (int i = 0; i < n; i++) tratar_caso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}