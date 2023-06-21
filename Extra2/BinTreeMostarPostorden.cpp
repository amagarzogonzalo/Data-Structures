#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <vector>
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

using namespace std;

BinTree<int> leer_arbol() {
	int n;
	std::cin >> n;
	if (n == -1) {
		return {};
	}
	else {
		BinTree<int> iz = leer_arbol();
		BinTree<int> dr = leer_arbol();
		return { iz, n, dr };
	}
}


template <typename T>
void p(const BinTree<T>& b) {

}

bool tratar_caso() {
	BinTree<int> b = leer_arbol();
	if (cin.eof() || b.empty()) return false;
	p(b);
	b.display(cout);
	cout <<b.root()<< endl;
	return true;
}



int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while(tratar_caso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}