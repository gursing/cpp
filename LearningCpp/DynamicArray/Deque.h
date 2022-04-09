#pragma once

template<typename T>
class Deque {
private:
	struct Node {
		T element{};
		Node* prev = nullptr;
		Node* next = nullptr;
	public:
		Node(const T& e, Node* p = nullptr, Node* n = nullptr) : element{ e }, prev{ p }, next{ n }{};
	};
	size_t count;
	Node* head;
	Node* tail;
	void assign(Deque &tmp) {
		std::swap(count, tmp.count);
		std::swap(head, tmp.head);
		std::swap(tail, tmp.tail);
	}
public:
	Deque();
	Deque(const Deque& d);
	Deque(Deque&& d);
	Deque& operator=(const Deque& d);
	Deque& operator=(Deque&& d);
	~Deque();

	const T& front() const;
	const T& back() const;
	bool empty() const;
	size_t size() const;

	void push_front(const T& t);
	void push_back(const T& t);

	void pop_front();
	void pop_back();

	void clear();
};

template<typename T>
Deque<T>::Deque() :count(0), head{ nullptr }, tail{ nullptr }{};

template<typename T>
Deque<T>::Deque(const Deque& d) : count{d.count}, head{nullptr}, tail{nullptr}{
	for (const Node* ptr = d.head; ptr != nullptr; ++ptr) {
		Node* nptr = new Node(ptr->element);
		if (empty()) head = tail = nptr;
		else {
			tail->next = nptr;
			nptr->prev = tail;
			tail = nptr;
		}
	}
}

template<typename T>
Deque<T>::Deque(Deque&& d) : count{ d.count }, head{ d.head }, tail{ d.tail } {
	d.count = 0;
	d.head = nullptr;
	d.tail = nullptr;
}


template<typename T> 
Deque<T>& Deque<T>::operator=(const Deque& d) {
	if (this == &d) return *this;
	Deque tmp(d);
	assign(tmp);
	return *this;
}

template<typename T>
Deque<T>& Deque<T>::operator=(Deque&& d) {
	if (this == &d) return *this;
	assign(d);
	return *this;
}

template<typename T>
Deque<T>::~Deque() {
	while (head) {
		Node* ptr = head;
		head = head->next;
		delete ptr;
	}

	head = nullptr;
	tail = nullptr;
	count = 0;
}

template<typename T>
void Deque<T>::push_front(const T& tp) {
	Node* nptr = new Node(tp);
	++count;
	if (empty()) head = tail = nptr;
	else {
		nptr->next = head;
		head->prev = nptr;
		head = nptr;
	}
}

template<typename T>
void Deque<T>::push_back(const T& tp) {
	Node* nptr = new Node(tp);
	++count;
	if (empty()) head = tail = nptr;
	else {
		tail->next = nptr;
		nptr->prev = tail;
		tail = nptr;
	}
}

template<typename T>
void Deque<T>::pop_front() {
	if (empty()) throw std::out_of_range("can't pop from empty deque");
	if (head == tail) {
		delete head;
		count = 0;
		head = tail = nullptr;
		return;
	}

	Node* ptr = head;
	head = head->next;
	delete ptr;
	--count;
}

template<typename T>
void Deque<T>::pop_back() {
	if (empty()) throw std::out_of_range("can't pop from empty deque");
	if (head == tail) {
		delete head;
		count = 0;
		head = tail = nullptr;
		return;
	}

	Node* ptr = tail;
	tail = tail->prev;
	tail->next = nullptr;
	delete ptr;
	--count;
}

template<typename T>
bool Deque<T>::empty() const {
	return head == nullptr;
}


template<typename T>
const T& Deque<T>::front() const {
	if(empty()) throw std::out_of_range("empty deque");
	return head->element;
}

template<typename T>
const T& Deque<T>::back() const {
	if(empty())  throw std::out_of_range("empty deque");
	return tail->element;
}

template<typename T>
size_t Deque<T>::size() const {
	return count;
}

template<typename T>
void Deque<T>::clear() {
	while (count) pop_back();
}

