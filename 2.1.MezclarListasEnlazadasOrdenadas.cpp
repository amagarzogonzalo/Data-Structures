/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no será corregida.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  /*@ <answer>
   * Comienza poniendo el nonmbre de los/as componentes del grupo:
   *
   *  Estudiante 1: Pablo González Corredor
   *  Estudiante 2: Alejandro Magarzo Gonzalo
   *@ </answer> */

   /*
	* Implementa las operaciones pedidas en el ejercicio al final de
	* este fichero, entre las etiquetas.
	*/


#include <cassert>
#include <iostream>
#include <fstream>

class ListLinkedSingle {
private:
	struct Node {
		int value;
		Node *next;
	};

public:
	ListLinkedSingle() : head(nullptr) { }
	~ListLinkedSingle() {
		delete_list(head);
	}

	ListLinkedSingle(const ListLinkedSingle &other)
		: head(copy_nodes(other.head)) { }

	void push_front(const int &elem) {
		Node *new_node = new Node{ elem, head };
		head = new_node;
	}

	void push_back(const int &elem);

	void pop_front() {
		assert(head != nullptr);
		Node *old_head = head;
		head = head->next;
		delete old_head;
	}

	void pop_back();

	int size() const;

	bool empty() const {
		return head == nullptr;
	};

	const int & front() const {
		assert(head != nullptr);
		return head->value;
	}

	int & front() {
		assert(head != nullptr);
		return head->value;
	}

	const int & back() const {
		return last_node()->value;
	}

	int & back() {
		return last_node()->value;
	}

	const int & at(int index) const {
		Node *result_node = nth_node(index);
		assert(result_node != nullptr);
		return result_node->value;
	}

	int & at(int index) {
		Node *result_node = nth_node(index);
		assert(result_node != nullptr);
		return result_node->value;
	}

	void display(std::ostream &out) const;
	void display() const {
		display(std::cout);
	}

	void merge(ListLinkedSingle &other);

private:
	Node *head;

	void delete_list(Node *start_node);
	Node *last_node() const;
	Node *nth_node(int n) const;
	Node *copy_nodes(Node *start_node) const;

};

ListLinkedSingle::Node * ListLinkedSingle::copy_nodes(Node *start_node) const {
	if (start_node != nullptr) {
		Node *result = new Node{ start_node->value, copy_nodes(start_node->next) };
		return result;
	}
	else {
		return nullptr;
	}
}

void ListLinkedSingle::delete_list(Node *start_node) {
	if (start_node != nullptr) {
		delete_list(start_node->next);
		delete start_node;
	}
}

void ListLinkedSingle::push_back(const int &elem) {
	Node *new_node = new Node{ elem, nullptr };
	if (head == nullptr) {
		head = new_node;
	}
	else {
		last_node()->next = new_node;
	}
}

void ListLinkedSingle::pop_back() {
	assert(head != nullptr);
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
	}
	else {
		Node *previous = head;
		Node *current = head->next;

		while (current->next != nullptr) {
			previous = current;
			current = current->next;
		}

		delete current;
		previous->next = nullptr;
	}
}

int ListLinkedSingle::size() const {
	int num_nodes = 0;

	Node *current = head;
	while (current != nullptr) {
		num_nodes++;
		current = current->next;
	}

	return num_nodes;
}


ListLinkedSingle::Node * ListLinkedSingle::last_node() const {
	assert(head != nullptr);
	Node *current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	return current;
}

ListLinkedSingle::Node * ListLinkedSingle::nth_node(int n) const {
	assert(0 <= n);
	int current_index = 0;
	Node *current = head;

	while (current_index < n && current != nullptr) {
		current_index++;
		current = current->next;
	}

	return current;
}

void ListLinkedSingle::display(std::ostream &out) const {
	out << "[";
	if (head != nullptr) {
		out << head->value;
		Node *current = head->next;
		while (current != nullptr) {
			out << ", " << current->value;
			current = current->next;
		}
	}
	out << "]";
}

/* ==============================================================================================
 * Implementa aquí el método merge y la función merge_lists
 * ==============================================================================================
 *
 *@ <answer>
 */

using namespace std;

void ListLinkedSingle::merge(ListLinkedSingle &other) {
	if (head == nullptr) { // si la lista 1 esta vaca
		head = other.head;
		other.head = nullptr;
	}
	else if (other.head == nullptr) { // si la lista 2 esta vaca
		other.head = nullptr;
	}
	else if (other.head == nullptr && head == nullptr); // si ambas listas estn vacas
	else {
		Node *currentl1 = head, *nextl1 = head->next, *currentl2 = other.head, *nextl2 = other.
			head->next;
		bool fin = false;
		while (!fin) {
			if (currentl1 == head && currentl2->value <= currentl1->value) { // si se inserta en la primera posicin, pcipio
				head = currentl2;
				currentl2->next = currentl1;
				other.head = nextl2;
				currentl2 = nextl2;
				currentl1 = head;
				if (head->next == nullptr) fin = true;
				else if (nextl2 == nullptr) fin = true;
				else {
					nextl2 = nextl2->next;
					nextl1 = head->next;
				}
			}
			else if (currentl2->value >= currentl1->value) { // si va entre dos posiciones, medio
				if (nextl1 != nullptr && currentl2->value <= nextl1->value) {
					currentl1->next = currentl2;
					currentl2->next = nextl1;
					Node *tmp = currentl2;
					other.head = nextl2;
					currentl2 = nextl2;
					if (nextl1 == nullptr || nextl2 == nullptr) fin = true;
					else {
						nextl2 = nextl2->next;
						currentl1 = tmp;
						nextl1 = tmp->next;
					}
				}
				else if (nextl1 != nullptr) {
					currentl1 = nextl1;
					nextl1 = nextl1->next;
				}
				else fin = true;
			}
			else { // si no se inserta al principio ni en posiciones medias, se obtiene el ltimo elemento de la lista 1 y en otro bucle se insertan todos los valores de l2 restantes
					if (nextl1 == nullptr) fin = true;
					else {
						currentl1 = nextl1;
						nextl1 = nextl1->next;
					}
			}
		}
		if (currentl2 != nullptr) { // aqu se insertan los valores mayores que todos los valores de la lista 1, es decir, van al final de la lista 1
			currentl1->next = currentl2;
			//currentl1 = currentl2;
			//currentl2 = currentl2->next;
		}
		other.head = nullptr;
	}
}
/* -----COSTE---------
El coste de este algoritmo depende de los datos de entrada, concretamente del tamao de las
listas l1 y l2. En el caso peor el coste del mtodo merge es lineal respecto al tamao de
la lista 1 ya que recorre todas las posiciones de la lista 1 y aade los valores de la lista 2 en su
lugar adecuado, ya sea al principio o en el medio. Los valores de la lista 2 que sean
mayores que todos los valores de la lista 1 irn al final, por lo que se ha implementado otro
iterativo para aadir respectivamente dichos valores de la lista 2 al final de la lista 1
y el coste de este bucle en el caso peor sera de orden lineal respecto al tamao de la lista 2. Siendo n1 el
tamao de l1 y n2 de l2; Es por ello que en el caso peor se recorre la lista 1 en el primer bucle y la lista 2 en el
segundo bucle y por ello el coste es O(n1 + n2) = O(max(n1,n2)) Debido a la Regla de la suma de los rdenes
de complejidad. El coste es lineal respecto al mayor tamao de la lista 1 y la lista 2.
*/

ListLinkedSingle merge_lists(const ListLinkedSingle &l1, const ListLinkedSingle &l2) {
	
}


void tratar_caso() {
	ListLinkedSingle l1, l2, lista;
	int a;
	cin >> a;
	while (a != 0) {
		l1.push_back(a);
		cin >> a; 
	}
	cin >> a;
	while (a != 0) {
		l2.push_back(a);
		cin >> a;
	}

	lista = merge_lists(l1, l2);
	lista.display();
	cout << endl;

}

int main() {
	int num_casos;
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	cin >> num_casos;

	while (num_casos > 0) {
		tratar_caso();
		num_casos--;
	}


#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Visual Studio
	system("PAUSE");
#endif

	return 0;
}

/*@ </answer> */

