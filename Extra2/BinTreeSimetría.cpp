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
bool sim(const BinTree<T>& b) {
	if (b.empty()) {
		return true;
	}
	else {
		if (b.left().empty() && b.right().empty());
		else if (!b.left().empty() && !b.right().empty()) {
			if ((b.left().left().empty() && b.right().right().empty()) || (!b.left().left().empty() && b.right().right().empty()));
			else return false;
			if ((b.left().right().empty() && b.right().left().empty()) || (!b.left().right().empty() && b.right().left().empty()));
			else return false;
		}
		bool simI = sim(b.left());
		bool simD = sim(b.right());
		return (simI && simD);
	}
}

template <typename T>
bool sim_aux(const BinTree<T> &b) {
	return sim(b);
}

void tratar_caso() {
	BinTree<int> b = leer_arbol();
	bool s = sim_aux(b);
	if (s) cout << "SI" << endl;
	else cout << "NO" << endl;
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