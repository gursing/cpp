#pragma once
#include <cassert>
#include <cstddef>

template<typename T>
class DList {
	struct Node {
		T m_Data{};
		Node* m_pNext{};
		Node* m_pPrev{};

		Node(T data, Node* pNext = nullptr, Node* pPrev = nullptr)
			: m_Data{ data },
			m_pNext{ pNext },
			m_pPrev{pPrev} {
		}
	};

	Node* m_pHead{};
	std::size_t m_Length{};
public:
	DList() = default;
	DList(std::initializer_list<T> elements) {
		for (auto e : elements) {
			push_front(e);
		}
	}
	DList(size_t size) {
		for (size_t i = 0; i < size; ++i) {
			push_front({});
		}
	}
	std::size_t length()const { return m_Length; }
	bool empty() const { return m_Length == 0;}
	void push_front(const T& value) {
		if (empty()) {
			m_pHead = new Node{ value };
		}
		else {
			auto temp = new Node{ value, m_pHead };
			m_pHead->m_pPrev = temp;
			m_pHead = temp;
		}

		++m_Length;
	}
	~DList() {
		for (auto temp = m_pHead; m_pHead != nullptr; temp = m_pHead) {
			m_pHead = m_pHead->m_pNext;
			delete temp;
		}
	}
	const T& GetAt(std::size_t index) const {
		assert(index < m_Length);
		int i{};
		auto temp = m_pHead;
		for (; temp != nullptr; temp = temp->m_pNext, ++i) {
			if (i == index) {
				break;
			}
		}
		return temp->m_Data;
	}
	const Node* GetHead() const { return m_pHead;}

#pragma region Iterators
	class Iterator {
		friend class DList<T>;
		Node* m_pHead{};
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = size_t;
		using pointer = T*;
		using reference = T&;
		Iterator(Node* pHead)
			: m_pHead{ pHead } {}
		Iterator& operator++() {
			m_pHead = m_pHead->m_pNext;
			return *this;
		}
		bool operator == (const Iterator& other)const {
			return m_pHead == other.m_pHead;
		}
		bool operator != (const Iterator& other)const {
			return m_pHead != other.m_pHead;
		}
		T& operator *() {
			return m_pHead->m_Data;
		}
	};
	class Const_Iterator {
		Node* m_pHead{};
	public:
		Const_Iterator(Node* pHead) : m_pHead{ pHead } {}
		Const_Iterator& operator++() {
			m_pHead = m_pHead->m_pNext;
			return *this;
		}
		bool operator == (const Const_Iterator& other)const {
			return m_pHead == other.m_pHead;
		}
		bool operator != (const Const_Iterator& other)const {
			return m_pHead != other.m_pHead;
		}
		const T& operator *()const {
			return m_pHead->m_Data;
		}
	};
	Iterator begin() {
		return Iterator{ m_pHead };
	}
	Iterator end() {
		return Iterator{ nullptr };
	}
	Const_Iterator begin()const {
		return Const_Iterator{ m_pHead };
	}
	Const_Iterator end()const {
		return Const_Iterator{ nullptr };
	}
	Const_Iterator cbegin() {
		return Const_Iterator{ m_pHead };
	}
	Const_Iterator cend() {
		return Const_Iterator{ nullptr };
	}
#pragma endregion
};