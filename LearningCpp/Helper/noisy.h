/*
	Author 	: Umar Lone
*/
#include <iostream>
#include <vector>
class Noisy {
	int m_ID = 0;
	inline static long m_create, m_param, m_assign, m_copyctor, m_dtor, m_movector, m_moveassign;
public:
	Noisy() {
		++m_create;
		//	std::cout << "d[" << id << "]";
	}
	Noisy(int id) :
			m_ID(id) {
		++m_param;
		//	std::cout << "d[" << id << "]";
	}
	Noisy(const Noisy & obj) {
		m_ID = obj.m_ID;
		++m_copyctor;
	}
	Noisy(Noisy && obj)noexcept {
		m_ID = obj.m_ID;
		++m_movector;
	}
	Noisy & operator =(const Noisy &obj) {
		m_ID = obj.m_ID;
		++m_assign;
		return *this;
	}
	Noisy & operator =(Noisy &&obj)noexcept {
		m_ID = obj.m_ID;
		++m_moveassign;
		return *this;
	}
	~Noisy() {
		++m_dtor;
	}
	int GetID() const {
		return m_ID;
	}
	void SetID(int id) {
		m_ID = id;
	}
	friend bool operator <(const Noisy &lv, const Noisy &rv) {
		return lv.m_ID < rv.m_ID;
	}
	friend bool operator >(const Noisy &lv, const Noisy &rv) {
		return lv.m_ID > rv.m_ID;
	}
	friend bool operator ==(const Noisy &lv, const Noisy &rv) {
		return lv.m_ID == rv.m_ID;
	}
	friend class Reporter;
	friend std::ostream & operator <<(std::ostream & out, const Noisy &n) {
		out << n.m_ID;
		return out;
	}
};
//long Noisy::m_assign = 0;
//long Noisy::m_copyctor = 0;
//long Noisy::m_create = 0;
//long Noisy::m_param = 0;
//long Noisy::m_dtor = 0;
//long Noisy::m_movector = 0;
//long Noisy::m_moveassign = 0;

class Reporter {
	static Reporter m_reporter;
	Reporter() {
	}
public:
	~Reporter() {
		using namespace std;

#ifdef _DOTRACE
		cout << "Noisy default ctors : " << Noisy::m_create << endl;
		cout << "Noisy parameterized ctors : " << Noisy::m_param << endl;
		cout << "Noisy copy ctors : " << Noisy::m_copyctor << endl;
		cout << "Noisy move ctors : " << Noisy::m_movector << endl;
		cout << "Noisy copy assignments : "<< Noisy::m_assign << endl;
		cout << "Noisy move assignments : "<< Noisy::m_moveassign << endl;
		cout << "Noisy dtors : "<< Noisy::m_dtor << endl <<endl ;
		cout << ">>>> TOTAL OBJECTS CREATED :" << Noisy::m_dtor << endl;
		cout << ">>>> TOTAL FUNCTIONS CALLED :" << Noisy::m_assign + Noisy::m_create
		+Noisy::m_param + Noisy::m_copyctor + Noisy::m_movector+ Noisy::m_moveassign+ Noisy::m_dtor << endl;
#endif
	}
};
inline Reporter Reporter::m_reporter;

