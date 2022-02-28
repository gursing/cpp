#pragma once
//#define LOGON

#ifdef LOGON
#define LOG std::cout << __PRETTY_FUNCTION__ << std::endl;
#else
#define LOG
#endif

template<typename T>
class MyVector {
private:
	T* elems;
	size_t m_capacity;
	size_t m_size = 0;
	const size_t gfactor = 2;
	void copy(const T* source, T* destination, int size) {
		LOG
			for (int i = 0; i < size; ++i) destination[i] = source[i];
	}
public:
	MyVector(size_t s);
	MyVector(MyVector&& v);
	MyVector(const MyVector& v);
	MyVector(std::initializer_list<T> lst);
	MyVector& operator=(const MyVector& v);
	MyVector& operator=(MyVector&& v);
	T& operator[](int idx);
	const T& operator[](int idx) const;
	size_t capacity() const;
	size_t size() const;
	void push_back(T elem);
	~MyVector();
};

template<typename T>
inline T& MyVector<T>::operator[](int idx) {
	LOG;
	return elems[idx];
}

template<typename T>
inline const T& MyVector<T>::operator[](int idx) const {
	LOG;
	return elems[idx];
}

template<typename T>
inline MyVector<T>::MyVector(size_t s) : elems{ new T[s] }, m_capacity{ s }, m_size{ m_capacity } { LOG }

template<typename T>
inline MyVector<T>::MyVector(MyVector&& v) {
	LOG;
	m_capacity = v.m_capacity;
	elems = v.elems;
	m_size = m_capacity;
	v.m_capacity = 0;
	v.elems = nullptr;
}

template<typename T>
inline MyVector<T>::MyVector(std::initializer_list<T> lst) : MyVector(lst.size()) {
	LOG;
	std::copy(lst.begin(), lst.end(), elems);
}

template<typename T>
inline MyVector<T>::MyVector(const MyVector& v) {
	LOG;
	copy(v);
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector<T>& v) {
	LOG;
	if (this == &v) return *this;
	delete[] elems;
	elems = new T[v.m_capacity];
	m_capacity = v.m_capacity;
	m_size = m_capacity;
	copy(v.elems, elems, m_capacity);
	return *this;
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(MyVector<T>&& v) {
	LOG;
	if (this == &v) return *this;
	delete[] elems;
	m_capacity = v.m_capacity;
	elems = v.elems;
	m_size = m_capacity;

	v.m_capacity = 0;
	v.elems = nullptr;
	return *this;
}

template<typename T>
inline size_t MyVector<T>::size() const {
	return m_size;
}

template<typename T>
inline size_t MyVector<T>::capacity() const {
	LOG;
	return m_capacity;
}

template<typename T>
inline MyVector<T>::~MyVector() {
	LOG;
	m_capacity = 0;
	delete[] elems;
	elems = nullptr;
}

template<typename T>
inline void MyVector<T>::push_back(T elem) {
	LOG;
	if (m_size == m_capacity) {
		int newsz = gfactor * m_capacity;
		auto newelems = new T[newsz];
		copy(elems, newelems, m_size);

		delete[] elems;
		m_capacity = newsz;
		elems = newelems;
	}

	elems[m_size++] = elem;
}
