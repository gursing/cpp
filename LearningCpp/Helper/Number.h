#ifndef MANAGED_NUMBER_H
#define MANAGED_NUMBER_H

//#define _DOTRACE
#include "./logger.h"

#ifndef WIN32
#define TRACETHIS std::cout << __PRETTY_FUNCTION__ << '\n' ;
#endif
#define MOVE
#define COPY
class Number {
	int m_Value{} ;
public:
	Number(int,int,int,int) {
		TRACETHIS
		
	}
	
	 Number():m_Value(0) {
		TRACETHIS
	}
	Number(int x,int y) {
		TRACETHIS
		 
	 }
	 Number(int value) :m_Value{ value } {
		TRACETHIS
	}
	void Set(int value) {
		m_Value = value;
	}
	int Get()const {
		return m_Value;
	}
	/*bool operator==(const Number &obj)const {
		return m_Value == obj.m_Value;
	}*/
#ifdef COPY
	Number(const Number & obj) :m_Value{ obj.m_Value } {
		TRACETHIS

	}
	Number & operator =(const Number &obj) {
		TRACETHIS
			if (this != &obj) {
			m_Value = obj.m_Value;
		}
		return *this;
	}
#endif
#ifdef MOVE
	Number(Number && obj)noexcept  {
		TRACETHIS
		m_Value = obj.m_Value;
		obj.m_Value = 0;
	}
	Number& operator =(Number&& obj)noexcept {
		TRACETHIS
			if (this != &obj) {
				m_Value = obj.m_Value;
				obj.m_Value = 0;
			}
		return *this;
	}
#endif
	~Number() {
		TRACETHIS
	}
	friend std::ostream & operator<<(std::ostream &out, const Number &obj) {
		 return out << obj.Get() ;
	}
	bool operator <(const Number &other)const {
		return m_Value < other.m_Value;
	}
	bool operator ==(const Number & other)const {
		return m_Value == other.m_Value ;
	}
	Number  & operator+=(int x) {
		m_Value +=x ;
		return *this ;
	}
};


//#ifdef DOTRACE
//#undef DOTRACE
//#endif
#endif //MANAGED_NUMBER_H