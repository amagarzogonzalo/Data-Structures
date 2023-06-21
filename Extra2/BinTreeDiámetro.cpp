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
int camino(const BinTree<T> &b, int &maximo) {
	if (b.root.left().empty() && root.right().empty()) {
		return 1;
	}
	else {
		int izquierda = 0;
		int derecha = 0;
		if (!b.root.left().empty()) izquierda = camino(root.left(), maximo);
		if (!b.root.right().empty()) derecha = camino(root.right(), maximo);
		int conjunto = izquierda + derecha + 1;
		if (conjunto > maximo) maximo = conjunto;
		if (izquierda > derecha) {
			return izquierda + 1;
		}
		else {
			return derecha + 1;
		}
	}
}
}

template <typename T>
int caminoaux(const BinTree<T> &b) {
	int maximo;
	return camino(b, c);

}
void tratar_caso() {
	BinTree<int> b = leer_arbol();
	cout << caminoaux(b) << endl;
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