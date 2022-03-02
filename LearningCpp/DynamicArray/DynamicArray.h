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
	T* m_pBuffer;
	size_t m_capacity = 0;
	size_t m_size = 0;
	const size_t gfactor = 2;
	void copy(const T* source, T* destination, int size) {
		LOG
			for (int i = 0; i < size; ++i) destination[i] = source[i];
	}
public:
	MyVector(){}
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
	void push_back(const T &elem);
	bool empty() const;
	~MyVector();
};

template<typename T>
inline T& MyVector<T>::operator[](int idx) {
	LOG;
	return m_pBuffer[idx];
}

template<typename T>
inline const T& MyVector<T>::operator[](int idx) const {
	LOG;
	return m_pBuffer[idx];
}

template<typename T>
inline MyVector<T>::MyVector(size_t s) : m_pBuffer{ new T[s] }, m_capacity{ s }, m_size{ m_capacity } { LOG }

template<typename T>
inline MyVector<T>::MyVector(MyVector&& v) {
	LOG;
	m_capacity = v.m_capacity;
	m_pBuffer = v.m_pBuffer;
	m_size = m_capacity;
	v.m_capacity = 0;
	v.m_pBuffer = nullptr;
}

template<typename T>
inline MyVector<T>::MyVector(std::initializer_list<T> lst) : MyVector(lst.size()) {
	LOG;
	std::copy(lst.begin(), lst.end(), m_pBuffer);
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
	delete[] m_pBuffer;
	m_pBuffer = new T[v.m_capacity];
	m_capacity = v.m_capacity;
	m_size = m_capacity;
	copy(v.m_pBuffer, m_pBuffer, m_capacity);
	return *this;
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(MyVector<T>&& v) {
	LOG;
	if (this == &v) return *this;
	delete[] m_pBuffer;
	m_capacity = v.m_capacity;
	m_pBuffer = v.m_pBuffer;
	m_size = m_capacity;

	v.m_capacity = 0;
	v.m_pBuffer = nullptr;
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
	delete[] m_pBuffer;
	m_pBuffer = nullptr;
}

template<typename T>
inline bool MyVector<T>::empty() const {
	return m_size == 0;
}

template<typename T>
inline void MyVector<T>::push_back(const T &elem) {
	LOG;
	if(empty()) {
		m_pBuffer = new T[1]{ elem };
		m_size = 1;
		m_capacity = 1;
	}
	else {
		if (m_size == m_capacity) {
			int newsz = gfactor * m_capacity;
			auto newelems = new T[newsz];
			copy(m_pBuffer, newelems, m_size);

			delete[] m_pBuffer;
			m_capacity = newsz;
			m_pBuffer = newelems;
		}

		m_pBuffer[m_size++] = elem;
	}
}
