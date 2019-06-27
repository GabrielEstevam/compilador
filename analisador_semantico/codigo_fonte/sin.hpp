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
#include "sem.hpp"

using namespace std;

// Structures definitions
struct rule {
	pair <int, int> header;
	vector < pair <int, int > > body;
};

// Functions Definitions
void syntacticAnalysis(vector <token> entry); // execute the syntactic analysis
map < pair<int, int>, int> initParseTable(); // init parsing table
map < int, rule > createRules(); // build the table rules
rule newRule (pair<int, int> header, vector < pair <int, int> > body); // create new rule
void printToken (vector<token> entry, int ptrToken, vector < pair< int, int> > execStack); // print tokens
void printStack (vector< pair <int, int> > execStack); // print stack