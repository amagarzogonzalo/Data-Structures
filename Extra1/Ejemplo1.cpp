/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */


 /*@ <answer> */
 /*
  * No olvides indicar el nombre!
  *
  * Nombre: Alejandro Magarzo Gonzalo
  */
  /*@ </answer> */


#include <iostream>
#include <fstream>
#include <cassert>


// ----------------------------------------------------------------------
// Clase ListLinkedDouble
// ----------------------------------------------------------------------

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
		assert(it.head == head);
		Node *new_node = new Node{ elem, it.current, it.current->prev };
		it.current->prev->next = new_node;
		it.current->prev = new_node;
		num_elems++;
		return iterator(head, new_node);
	}

	iterator erase(const_iterator it) {
		assert(it.head == head && it.current != head);
		Node *target = it.current;
		it.current->prev->next = it.current->next;
		it.current->next->prev = it.current->prev;
		iterator result(head, it.current->next);
		delete target;
		num_elems--;
		return result;
	}


	// Esta es la nueva operación
	// Se implementa más abajo, fuera de la clase.
	void aux_cero(ListLinkedDouble &other);
	void aux_uno(ListLinkedDouble &other);
	void aux_dos(ListLinkedDouble &other);
	void aux_tres(ListLinkedDouble &other);
	void aux_cuatro(ListLinkedDouble &other);
	void aux_cinco(ListLinkedDouble &other);
	void aux_seis(ListLinkedDouble &other);
	void aux_siete(ListLinkedDouble &other);
	void aux_ocho(ListLinkedDouble &other);
	void aux_nueve(ListLinkedDouble &other);
	void aux_diez(ListLinkedDouble &other);
	void aux_once(ListLinkedDouble &other);





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


// Sobrecarga del operador << para imprimir listas

template <typename T>
std::ostream & operator<<(std::ostream &out, const ListLinkedDouble<T> &l) {
	l.display(out);
	return out;
}


// ----------------------------------------------------------------------
// Realiza el ejercicio indicado a continuación
// 
// Puedes utilizar funciones y métodos auxiliares, si lo deseas, pero
// su implementación ha de estar entre las etiquetas <answer> y </answer>
// ----------------------------------------------------------------------
/*@ <answer> */


using namespace std;

// 0 - Añadir alternativamente de uno en uno elementos de other en list
template <typename T>
void ListLinkedDouble<T>::aux_cero(ListLinkedDouble &other) {
	Node* current = head->next;
	Node* add = other.head->next;
	while (add != other.head) {
		Node* tmp = current->next;
		Node* nadd = add->next;
		other.head->next = nadd;
		nadd->prev = other.head;

		current->next = add;
		add->prev = current;
		add->next = tmp;
		tmp->prev = add;

		current = tmp;
		add = nadd;
		if (current == head) {
			current = current->prev;

			current->next = nadd;
			nadd->prev = current;
			head->prev = other.head->prev;
			other.head->prev->next = head;

			other.head->next = other.head;
			other.head->prev = other.head;
			add = other.head;
		}
	}
	num_elems += other.num_elems;
	other.num_elems = 0;
}

// 1 - Duplicar list
template <typename T>
void ListLinkedDouble<T>::aux_uno(ListLinkedDouble &other) {
	Node* current = head->next;
	while (current != head) {
		Node* next = current->next;
		Node* d = new Node{ current->value, next, current };
		current->next = d;
		next->prev = d;
		current = next;
	}
	num_elems = num_elems * 2;
}

// 2 - Invertir list
template <typename T>
void ListLinkedDouble<T>::aux_dos(ListLinkedDouble &other) {
	if (head->next != nullptr) {
		Node* a = head;
		Node* b = a->next;
		while (b != head) {
			Node* tmp = b->next;
			b->next = a;
			a->prev = b;
			a = b;
			b = tmp;
		}
		head->next = a;
		a->prev = head;
	}
}

// 3 - Insertar desde posición una other en list
template <typename T>
void ListLinkedDouble<T>::aux_tres(ListLinkedDouble &other) {
	if (!other.empty()) {
		int pos = 2, i = 1;
		bool inserted = false;
		Node* current = head->next;
		while (!inserted) {
			if (pos == i || current == head) {
				inserted = true;
				if (current == head) current = head->prev;
				Node* a = other.head->next;
				Node* b = other.head->prev;
				Node* next = current->next;
				current->next = a;
				a->prev = current;
				b->next = next;
				next->prev = b;

				other.head->next = other.head;
				other.head->prev = other.head;
			}
			else {
				current = current->next;
				i++;
			}
		}
		num_elems += other.num_elems;
		other.num_elems = 0;
	}

}

// 4 - Intercambiar de dos en dos una lista
template <typename T>
void ListLinkedDouble<T>::aux_cuatro(ListLinkedDouble &other) {
	if (head->next != nullptr) {
		Node* a = head->next;
		Node* b = a->next;
		while (a != head && b != head) {
			Node* tmp1 = b->next;
			Node* tmp2 = tmp1->next;
			Node* preva = a->prev;
			Node* nextb = b->next;
			b->prev = preva;
			preva->next = b;
			b->next = a;
			a->prev = b;
			a->next = nextb;
			nextb->prev = a;
			a = tmp1;
			b = tmp2;
		}
	}
}

// 5 - Añadir alternativamente elementos de other en list al principio o al final
template <typename T>
void ListLinkedDouble<T>::aux_cinco(ListLinkedDouble &other) {
	if (!other.empty()) {
		int cont = 0;
		Node* add = other.head->next;
		while (add != other.head) {
			Node* o = add->next;
			o->prev = other.head;
			other.head->next = o;
			
			if ((cont % 2) == 0) {
				Node* tmp = head->next;
				tmp->prev = add;
				head->next = add;
				add->next = tmp;
				add->prev = head;
			}
			else {
				Node* tmp = head->prev;
				head->prev = add;
				tmp->next = add;
				add->prev = tmp;
				add->next = head;

			}
			add = o;
			cont++;
		}
		num_elems += other.num_elems;
		other.num_elems = 0;
	}
}

// 6 - Borrar uno de cada dos en una list
template <typename T>
void ListLinkedDouble<T>::aux_seis(ListLinkedDouble &other) {
	if (head->next != nullptr) {
		int cont = 1;
		Node* current = head->next;
		while (current != head) {
			if ((cont % 2) == 0) {
				num_elems--;
				Node* prev = current->prev;
				Node* next = current->next;
				prev->next = next;
				next->prev = next;
			}
			current = current->next;
			cont++;
		}
	}
}

// 7 - List creciente, elimina elementos si son menores
template <typename T>
void ListLinkedDouble<T>::aux_siete(ListLinkedDouble &other) {
	Node* current = head->next;
	while (current->next != head) {
		if (current->next->value < current->value) {
			num_elems--;
			Node* tmp = current->next->next;
			tmp->prev = current;
			current->next = tmp;
		}
		else current = current->next;
	}
}

// 8 - Mezclar dos listas ordenadas, ordenadamente
template <typename T>
void ListLinkedDouble<T>::aux_ocho(ListLinkedDouble &other) {
	if (empty()) {
		head->next = other.head->next;
		other.head->next->prev = head;
		head->prev = other.head->prev;
		other.head->prev->next = head;
		other.head->next = other.head;
		other.head->prev = other.head;
	}
	else {
		Node* current = head->next;
		Node* o = other.head->next;
		while (o != other.head) {
			Node* no = o->next;
			if (o->value <= head->next->value) {
				Node* c = head->next;
				head->next = o;
				o->prev = head;
				c->prev = o;
				o->next = c;
				other.head->next = no;
				no->prev = other.head;
				o = no;
			}
			else if (o->value >= current->value && o->value <= current->next->value) {
				Node* tmp = current->next;
				current->next = o;
				o->prev = current;
				o->next = tmp;
				tmp->prev = o;
				other.head->next = no;
				no->prev = other.head;
				o = no;
			}
			else {
				current = current->next;
				if (current == head) {
					current = current->prev;
					current->next = o;
					o->prev = current;
					Node* tmp = other.head->prev;
					head->prev = tmp;
					tmp->next = head;
					other.head->next = other.head;
					other.head->prev = other.head;
					o = other.head;
				}
			}
			num_elems += other.num_elems;
			other.num_elems = 0;
		}
	}
}

// 9 - Particion lista por pivote
template <typename T>
void ListLinkedDouble<T>::aux_nueve(ListLinkedDouble &other) {
	int p = 6;
	Node* current = head->next;
	Node* end = head->prev;
	bool f = false;
	while (current != end) {
		if (current->value > p) {
			Node* a = current->prev;
			Node* b = current->next;
			a->next = b;
			b->prev = a;

			Node* last = head->prev;
			last->next = current;
			current->prev = last;
			head->prev = current;
			current->next = head;
			if (!f) {
				end = current;
				f = true;
			}
			current = b;
		}
		else current = current->next;
	}
}

//	10 - Concatenar dos listas
template <typename T>
void ListLinkedDouble<T>::aux_diez(ListLinkedDouble &other) {
	if (!empty()) {
		if (!other.empty()) {
			Node* last = head->prev;
			Node *l = other.head->prev;
			last->next = other.head->next;
			other.head->next->prev = last;
			head->prev = l;
			l->next = head;
			num_elems += other.num_elems;
			other.num_elems = 0;
		}
	}
	else {
		head->next = other.head->next;
		other.head->next->prev = head;
		other.head->prev->next = head;
		head->prev = other.head->prev;
		num_elems += other.num_elems;
		other.num_elems = 0;
	}
	other.head->next = other.head;
	other.head->prev = other.head;
}

// 11 - Devolver la mitad hasta un punto de List
template <typename T>
void ListLinkedDouble<T>::aux_once(ListLinkedDouble &other) {
	int s = 2;
	int i = 1;
	Node* current = head->next;
	while (i < s) {
		current = current->next;
		i++;
	}
	head->prev = current;
	current->next = head;
}

/*@ </answer> */
// ----------------------------------------------------------------------


void tratar_caso() {
	ListLinkedDouble<int> list, other;
	int n, m, a;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a;
		list.push_back(a);
	}
	cin >> m;
	for (int j = 0; j < m; j++) {
		cin >> a;
		other.push_back(a);
	}
	list.aux_nueve(other);
	cout << list << endl;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int num_casos;
	std::cin >> num_casos;

	for (int i = 0; i < num_casos; i++) {
		tratar_caso();
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}