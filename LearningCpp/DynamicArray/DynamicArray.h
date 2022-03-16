#pragma once
//#define LOGON

#ifdef LOGON
#define LOG std::cout << __PRETTY_FUNCTION__ << std::endl;
#else
#define LOG
#endif

template<typename T>
class MyVector {
public:
	class Iterator {
		T* m_parent;
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = size_t;
		using pointer = T*;
		using reference = T&;
		Iterator(T* parent)
			: m_parent{ parent } {}
		Iterator& operator++() {
			++m_parent;
			return *this;
		}
		bool operator == (const Iterator& other)const {
			return m_parent == other.m_parent;
		}
		bool operator != (const Iterator& other)const {
			return m_parent != other.m_parent;
		}
		T& operator *() {
			return *m_parent;
		}
		Iterator operator++(int) {
			Iterator newit{ m_parent };
			++m_parent;
			return newit;
		}
		Iterator& operator--() {
			--m_parent;
			return *this;
		}
		Iterator operator--(int) {
			Iterator newit{ m_parent };
			--m_parent;
			return newit;
		}
		int operator-(const Iterator &it) const {
			return m_parent - it.m_parent;
		}
		Iterator operator-=(int position) {
			m_parent -= position;
			return *this;
		}
		Iterator& operator+=(int position) {
			m_parent += position;
			return *this;
		}
	};
	class Const_Iterator {
		T* m_parent;
	public:
		Const_Iterator(T* parent)
			: m_parent{ parent } {}
		Const_Iterator& operator++() {
			++m_parent;
			return *this;
		}
		bool operator == (const Const_Iterator& other) const {
			return m_parent == other.m_parent;
		}
		bool operator != (const Const_Iterator& other) const {
			return m_parent != other.m_parent;
		}
		const T& operator *()const {
			return *m_parent;
		}
	};
	class Reverse_Iterator {
		T* m_parent;
	public:
		Reverse_Iterator(T* parent) : m_parent{ parent } {}
		Reverse_Iterator& operator++() {
			--m_parent;
			return *this;
		}
		bool operator ==(const Reverse_Iterator& other) const {
			return m_parent == other.m_parent;
		}
		bool operator !=(const Reverse_Iterator& other) const {
			return m_parent != other.m_parent;
		}
		T& operator *() {
			return *m_parent;
		}
	};
	Iterator begin() {
		return Iterator{ m_pBuffer };
	}
	Iterator end() {
		return Iterator{ m_pBuffer + m_size };
	}
	Reverse_Iterator rbegin() {
		return Reverse_Iterator{ m_pBuffer + m_size - 1 };
	}
	Reverse_Iterator rend() {
		return Reverse_Iterator{ m_pBuffer - 1 };
	}
	Const_Iterator begin() const {
		return Const_Iterator{ m_pBuffer };
	}
	Const_Iterator end() const {
		return Const_Iterator{ m_pBuffer + m_size };
	}
	Const_Iterator cbegin() {
		return Const_Iterator{ m_pBuffer };
	}
	Const_Iterator cend() {
		return Const_Iterator{ m_pBuffer + m_size };
	}
private:
	T* m_pBuffer;
	size_t m_capacity = 0;
	size_t m_size = 0;
	const size_t gfactor = 2;
	void copy(const T* source, T* destination, int size) {
		LOG;
		for (int i = 0; i < size; ++i) {
			new(destination + i) T{ source[i] };
		}
	}
	void deallocate(T* elems, int size) {
		for (int i = 0; i < size; ++i) {
			elems[i].~T();
		}
		operator delete(elems);
	}
	T* allocate(int size) {
		return static_cast<T*>(operator new(sizeof(T) * size));
	}
public:
	MyVector() {}
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
	void push_back(T&& elem);
	void push_back(const T& elem);
	bool empty() const;
	void reserve(size_t new_capacity);
	~MyVector();
	template<typename...U>
	void emplace_back(U&&... elem) {
		LOG;
		if (empty() && m_capacity == 0) {
			m_pBuffer = allocate(sizeof(T));
			new(m_pBuffer) T{ std::forward<U>(elem)... };
			m_size = 1;
			m_capacity = 1;
		}
		else {
			if (m_size == m_capacity) {
				reserve(gfactor * m_capacity);
			}

			new(m_pBuffer + m_size) T{ std::forward<U>(elem)... };
			++m_size;
		}
	}
};

template<typename T>
inline T& MyVector<T>::operator[](int idx) {
	LOG;
	return m_pBuffer[idx];
}

template<typename T>
void MyVector<T>::reserve(size_t new_capacity) {
	if (new_capacity < m_capacity) {
		return;
	}
	auto newelems = allocate(sizeof(T) * new_capacity);
	for (size_t i = 0; i < m_size; ++i) {
		new(newelems + i)T{ std::move(m_pBuffer[i]) };
	}
	deallocate(m_pBuffer, m_size);
	m_capacity = new_capacity;
	m_pBuffer = newelems;
}

template<typename T>
inline const T& MyVector<T>::operator[](int idx) const {
	LOG;
	return m_pBuffer[idx];
}

template<typename T>
inline MyVector<T>::MyVector(size_t s) : m_pBuffer{ allocate(sizeof(T) * s) }, m_capacity{ s }, m_size{ m_capacity } { LOG; }

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
	auto it = lst.begin();
	int i = 0;
	while (it != lst.end()) {
		new(m_pBuffer + i) T{ *it };
		++i;
		++it;
	}
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
	deallocate(m_pBuffer, m_size);
	m_pBuffer = allocate(sizeof(T) * v.m_capacity);
	m_capacity = v.m_capacity;
	m_size = m_capacity;
	copy(v.m_pBuffer, m_pBuffer, m_capacity);
	return *this;
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(MyVector<T>&& v) {
	LOG;
	if (this == &v) return *this;
	deallocate(m_pBuffer, m_size);
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
	deallocate(m_pBuffer, m_size);
	m_pBuffer = nullptr;
}

template<typename T>
inline bool MyVector<T>::empty() const {
	return m_size == 0;
}

template<typename T>
inline void MyVector<T>::push_back(const T& elem) {
	LOG;
	emplace_back(elem);
}

template<typename T>
inline void MyVector<T>::push_back(T&& elem) {
	LOG;
	emplace_back(std::move(elem));
}
