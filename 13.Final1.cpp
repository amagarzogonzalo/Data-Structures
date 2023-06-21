/*
 * ---------------------------------------------------
 *     ESTRUCTURAS DE DATOS - PRIMER EXAMEN
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Solo se corregirá el código contenido entre
  * las etiquetas <answer> y </answer>. Toda modificación fuera
  * de esas etiquetas no será corregida.
  */

  /*@ <answer>
   *
   * Nombre y apellidos: Alejandro Magarzo Gonzalo
   *
   *@ </answer> */

   /*
	* Implementa las operaciones pedidas en el ejercicio al final de
	* este fichero, entre las etiquetas.
	*/


#include <iostream>
#include <fstream>
#include <cassert>

	/* --------------------------------------------------------------------
	 * Clase ListLinkedDouble
	 * --------------------------------------------------------------------
	 * Implementa el TAD lista mediante una lista doblemente enlazada
	 * circular con nodo fantasma
	 * --------------------------------------------------------------------
	 */

template <typename T>
class ListLinkedDouble {
private:
	struct Node {
		T value;
		Node *next;
		Node *prev;
	};

public:
	ListLinkedDouble() : num_elems(0) {
		head = new Node;
		head->next = head;
		head->prev = head;
	}

	ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
		copy_nodes_from(other);
		num_elems = other.num_elems;
	}

	~ListLinkedDouble() {
		delete_nodes();
	}

	void push_front(const T &elem) {
		insert(cbegin(), elem);
	}

	void push_back(const T &elem) {
		insert(cend(), elem);
	}

	void pop_front() {
		erase(cbegin());
	}

	void pop_back() {
		assert(num_elems > 0);
		Node *target = head->prev;
		target->prev->next = head;
		head->prev = target->prev;
		delete target;
		num_elems--;
	}

	int size() const {
		return num_elems;
	}

	bool empty() const {
		return num_elems == 0;
	};

	const T & front() const {
		assert(num_elems > 0);
		return head->next->value;
	}

	T & front() {
		assert(num_elems > 0);
		return head->next->value;
	}

	const T & back() const {
		assert(num_elems > 0);
		return head->prev->value;
	}

	T & back() {
		assert(num_elems > 0);
		return head->prev->value;
	}

	const T & operator[](int index) const {
		assert(0 <= index && index < num_elems);
		Node *result_node = nth_node(index);
		return result_node->value;
	}

	T & operator[](int index) {
		assert(0 <= index && index < num_elems);
		Node *result_node = nth_node(index);
		return result_node->value;
	}

	ListLinkedDouble & operator=(const ListLinkedDouble &other) {
		if (this != &other) {
			delete_nodes();
			head = new Node;
			head->next = head->prev = head;
			copy_nodes_from(other);
			num_elems = other.num_elems;
		}
		return *this;
	}

	void display(std::ostream &out) const;

	void display() const {
		display(std::cout);
	}

	template <typename U>
	class gen_iterator {
	public:
		gen_iterator & operator++() {
			assert(current != head);
			current = current->next;
			return *this;
		}

		gen_iterator operator++(int) {
			assert(current != head);
			gen_iterator antes = *this;
			current = current->next;
			return antes;
		}

		U & operator*() const {
			assert(current != head);
			return current->value;
		}

		bool operator==(const gen_iterator &other) const {
			return (head == other.head) && (current == other.current);
		}

		bool operator!=(const gen_iterator &other) const {
			return !(*this == other);
		}

		friend class ListLinkedDouble;

	private:
		gen_iterator(Node *head, Node *current) : head(head), current(current) { }
		Node *head;
		Node *current;
	};

	using iterator = gen_iterator<T>;
	using const_iterator = gen_iterator<const T>;

	iterator begin() {
		return iterator(head, head->next);
	}

	iterator end() {
		return iterator(head, head);
	}

	const_iterator begin() const {
		return const_iterator(head, head->next);
	}

	const_iterator end() const {
		return const_iterator(head, head);
	}

	const_iterator cbegin() const {
		return const_iterator(head, head->next);
	}

	const_iterator cend() const {
		return const_iterator(head, head);
	}

	iterator insert(const_iterator it, const T &elem) {
		// Comprobamos que el iterador pertenece a la misma
		// lista en la que realizamos la inserción.
		assert(it.head == head);
		Node *new_node = new Node{ elem, it.current, it.current->prev };
		it.current->prev->next = new_node;
		it.current->prev = new_node;
		num_elems++;
		return iterator(head, new_node);
	}

	iterator erase(const_iterator it) {
		// Comprobamos que el iterador pertenece a la misma
		// lista en la que realizamos la inserción, y que no
		// estamos en el último elemento.
		assert(it.head == head && it.current != head);
		Node *target = it.current;
		it.current->prev->next = it.current->next;
		it.current->next->prev = it.current->prev;
		iterator result(head, it.current->next);
		delete target;
		num_elems--;
		return result;
	}

	void fill_gaps(int pos_begin, int pos_end);

private:
	Node *head;
	int num_elems;

	Node *nth_node(int n) const;
	void delete_nodes();
	void copy_nodes_from(const ListLinkedDouble &other);
};



template <typename T>
typename ListLinkedDouble<T>::Node * ListLinkedDouble<T>::nth_node(int n) const {
	int current_index = 0;
	Node *current = head->next;

	while (current_index < n && current != head) {
		current_index++;
		current = current->next;
	}

	return current;
}

template <typename T>
void ListLinkedDouble<T>::delete_nodes() {
	Node *current = head->next;
	while (current != head) {
		Node *target = current;
		current = current->next;
		delete target;
	}

	delete head;
}

template <typename T>
void ListLinkedDouble<T>::copy_nodes_from(const ListLinkedDouble &other) {
	Node *current_other = other.head->next;
	Node *last = head;

	while (current_other != other.head) {
		Node *new_node = new Node{ current_other->value, head, last };
		last->next = new_node;
		last = new_node;
		current_other = current_other->next;
	}
	head->prev = last;
}

template <typename T>
void ListLinkedDouble<T>::display(std::ostream &out) const {
	out << "[";
	if (head->next != head) {
		out << head->next->value;
		Node *current = head->next->next;
		while (current != head) {
			out << ", " << current->value;
			current = current->next;
		}
	}
	out << "]";
}

template <typename T>
std::ostream & operator<<(std::ostream &out, const ListLinkedDouble<T> &l) {
	l.display(out);
	return out;
}


/* --------------------------------------------------------------------
 * Implementa el método pedido aquí
 * --------------------------------------------------------------------
 *
 * Puedes añadir los métodos privados auxiliares que quieras. Para eso
 * puedes declararlos en la clase, pero has de implementarlos aquí, entre
 * las etiquetas <answer> y </answer>.
 *
 *@ <answer>
 */


template <typename T>
void ListLinkedDouble<T>::fill_gaps(int pos_begin, int pos_end) {
	Node* current = head->next;
	Node* end = current;
	int i = 0;
	while (i < pos_begin) {
		current = current->next;
		i++;
	}
	end = current;
	while (i < pos_end) {
		end = end->next;
		i++;
	}
	Node* a = current;
	while (a != end) {
		if ((a->value + 1) == (a->next->value)) {
			a = a->next;
		}
		else if ((a->value - 1) == (a->next->value)) {
			a = a->next;
		}
		else {
			if (a->value > a->next->value) {
				Node* next = a->next;
				int v = a->value, n = a->next->value;
				while (v > (n+1)) {
					Node* nuevo = new Node{(a->value- 1), a->next, a};
					Node* tmp = a->next;
					tmp->prev = nuevo;
					a->next = nuevo;
					v--;
					a = nuevo;
				}
				a = next;
			}
			else if (a->value < a->next->value) {
				Node* next = a->next;
				int v = a->value, n = a->next->value;
				while (v < (n - 1)) {
					Node* nuevo = new Node{ (a->value + 1), a->next, a };
					Node* tmp = a->next;
					tmp->prev = nuevo;
					a->next = nuevo;
					v++;
					a = nuevo;
				}
				a = next;
			}
		}
	}
}


using namespace std;


// Función para tratar cada uno de los casos de prueba
void tratar_caso() {
	ListLinkedDouble<int> list;
	int n, posb, pose, a;
	cin >> n >> posb >> pose;
	for (int i = 0; i < n; i++) {
		cin >> a;
		list.push_back(a);
	}
	list.fill_gaps(posb, pose);
	cout << list <<  endl;
}

/*@ </answer> */


int main() {
	int num_casos;
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	std::cin >> num_casos;

	while (num_casos > 0) {
		tratar_caso();
		num_casos--;
	}


#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Comentar si no se trabaja en Visual Studio
	system("PAUSE");
#endif

	return 0;
}

// SALT: 15964255754551423466808414121079018634427852280719