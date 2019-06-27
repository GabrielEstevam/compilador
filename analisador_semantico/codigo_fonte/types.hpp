/*
	File name: types.hpp
	Data: 2019, April.
	Project description: Building a Compiler for DEC7565 at Computer Engineering. 
	File description: structures types definition. 
	Authors: Gabriel Estevam de Oliveira (15104138)
			 Vinícius Rodrigues Zanon (15102833)
*/

#include <string>

using namespace std;

#ifndef token
struct token {
	int id, line, column;
	string content;
};
#endif

