/*
	File name: sin.hpp
	Data: 2019, April.
	Project description: Building a Compiler for DEC7565 at Computer Engineering. 
	File description: syntactic analyzer functions definition. 
	Authors: Gabriel Estevam de Oliveira (15104138)
			 Vinícius Rodrigues Zanon (15102833)
*/

#include <string>
#include <utility> // include pair
#include "lex.hpp"

using namespace std;

// Functions Definitions
void syntacticAnalysis(vector <token> entry); // execute the syntactic analysis
map < pair<int, int>, int> initParseTable(); // init parsing table
map < int, pair<int, vector<int>> > createRules(); // build the table rules
void printToken (vector<token> entry, int ptrToken, vector <int> execStack); // print tokens
void printStack (vector<int> execStack); // print stack