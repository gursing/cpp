
/*****************************************************************
Author 	: Umar Majid Lone
Date 	: 5/8/2009
Note	: Will work only on Visual Studio 2003 onwards.
		  To use on g++, substitute __FUNCSIG__ with __func__
*****************************************************************/

#ifndef LOGGER_H
#define LOGGER_H
#include "./ConsoleColors.h"

#include <iostream>
#ifdef _DOTRACE
#define TRACETHIS std::clog << \
		__FUNCSIG__ <<std::endl; 
#elif defined GREENTRACE
#define TRACETHIS Console::WriteLine(__FUNCSIG__, Color::GREEN, true) ;
#elif defined REDTRACE
#define TRACETHIS Console::WriteLine(__FUNCSIG__, Color::RED, true) ;
#elif defined BLUETRACE
#define TRACETHIS Console::WriteLine(__FUNCSIG__, Color::BLUE, true) ;
#elif defined YELLOWTRACE
#define TRACETHIS Console::WriteLine(__FUNCSIG__, Color::YELLOW, true) ;
#elif defined CYANTRACE
#define TRACETHIS Console::WriteLine(__FUNCSIG__, Color::CYAN, true) ;
#else
#define TRACETHIS
#endif

#endif