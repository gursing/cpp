#include <chrono>
#include <iostream>
template<typename T>
struct ToString {
	inline static const char *Unit = "" ;
};
template<>
struct ToString<std::chrono::nanoseconds> {
	inline static const char *Unit = "ns" ;
};
template<>
struct ToString<std::chrono::microseconds> {
	inline static const char *Unit = "us" ;
};
template<>
struct ToString<std::chrono::milliseconds> {
	inline static const char *Unit = "ms" ;
};
template<>
struct ToString<std::chrono::seconds> {
	inline static const char *Unit = "s" ;
};
#define START auto begin = std::chrono::high_resolution_clock::now()
#define END auto end = std::chrono::high_resolution_clock::now();\
	auto duration = end - begin 
#define PRINT(message, unit) std::cout \
<< message \
<<" : " \
<< std::chrono::duration_cast<unit>(duration).count() \
<< ToString<unit>::Unit \
<< std::endl 

#define NANOSEC		std::chrono::nanoseconds
#define MICROSEC	std::chrono::microseconds
#define MILLISEC	std::chrono::milliseconds
#define SECONDS		std::chrono::seconds