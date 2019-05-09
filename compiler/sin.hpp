/*
	File name: sin.hpp
	Data: 2019, April.
	Project description: Building a Compiler for DEC7565 at Computer Engineering. 
	File description: syntactic analyzer functions definition. 
	Authors: Gabriel Estevam de Oliveira (15104138)
			 Vinícius Rodrigues Zanon (15102833)
*/

#include <string>
#include "lex.hpp"

using namespace std;

// Functions Definitions
void syntacticAnalysis(vector <token> entry); // execute the syntactic analysis