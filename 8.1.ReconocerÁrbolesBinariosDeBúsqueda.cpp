/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no ser� corregida.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  /*@ <answer> */

  /*
   * Comienza poniendo el nombre de los/as componentes del grupo:
   *
   * Estudiante 1: Alejandro Magarzo Gonzalo
   * Estudiante 2: Pablo Gonz�lez Corredor
   */

   /*@ </answer> */


#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <vector>

/*
  Implementaci�n de la clase BinTree para representar �rboles binarios.
 */

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
	// Las definiciones de TreeNode y NodePointer dependen recursivamente
	// la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
	// para que el compilador sepa, cuando analice la definici�n de NodePointer,
	// que TreeNode va a ser definida m�s adelante.

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

/*
 * Operador << para mostrar un �rbol por pantalla. No es necesario hacer esto
 * en la pr�ctica, pero os lo dejo por si quer�is depurar.
 */
template<typename T>
std::ostream & operator<<(std::ostream &out, const BinTree<T> &tree) {
	tree.display(out);
	return out;
}


/*
 * Funci�n para leer un �rbol binario de la entrada. El formato es el siguiente:
 *
 *  �rbol vac�o: .
 *  �rbol no vac�o: (i x r)  donde i es la representaci�n del hijo izquierdo
 *                                 x es la ra�z
 *                                 r es la representaci�n del hijo derecho
 */
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

// ===============================================================================================
/*@ <answer> */
template <typename T>
bool binary_search_tree_aux(const BinTree<T> &tree, vector <T> padresMayores, vector <T> padresMenores) {
	if (tree.empty()) {
		return true;
	}
	else {
		for (int i = 0; i < padresMenores.size(); i++) 
			if (tree.root() <= padresMenores.at(i)) return false;
			
		for (int i = 0; i < padresMayores.size(); i++) 
			if (tree.root() >= padresMayores.at(i)) return false;
		
		bool abbI, abbD;
		padresMayores.push_back(tree.root());
		abbI = binary_search_tree_aux(tree.left(), padresMayores, padresMenores);
		if (abbI) {
			padresMayores.pop_back();
			padresMenores.push_back(tree.root());
			abbD = binary_search_tree_aux(tree.right(), padresMayores, padresMenores);
			if (abbD) return true;
			else return false;
		}
		else return false;
	}
} 

// Realmente el coste a analizar es el de la funci�n binary_search_tree_aux ya que el de binary search es depende de la funci�n auxiliar.
// El �rden de binary_search_aux es O(n), siendo n el n�mero de nodos del �rbol, es decir tiene un coste lineal respecto a n si el �rbol no est� equilibrado,
// si est� equilibrado entonces el orden es O(log n). Esta funci�n debe comprobar todos los
// nodos del �rbol para verificar que cumplan las condiciones propias de un ABB y si se cumple en todos los nodos se trata de un �rbol de B�squeda Binaria.

template <typename T>
bool binary_search_tree(const BinTree<T> &tree) {
	if (tree.empty()) return true;
	else {
		std:: vector<T> padresMenores, padresMayores;
		return binary_search_tree_aux(tree, padresMayores, padresMenores);
	}
}

/*@ </answer> */
// ===============================================================================================


void tratar_caso() {
	BinTree<int> tree = read_tree<int>(cin);
	cout << (binary_search_tree(tree) ? "SI" : "NO") << "\n";
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int num_casos;
	cin >> num_casos;

	while (num_casos > 0) { tratar_caso(); num_casos--; }

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}
