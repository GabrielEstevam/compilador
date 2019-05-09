/*
	File name: lex.hpp
	Data: 2019, April.
	Project description: Building a Compiler for DEC7565 at Computer Engineering. 
	File description: lexical analyzer functions definition. 
	Authors: Gabriel Estevam de Oliveira (15104138)
			 Vinícius Rodrigues Zanon (15102833)
*/

#include <string>
#include "types.hpp"

using namespace std;

// Functions Definitions
vector <token> lexicalAnalysis(vector <char> entry); // execute the lexical analysis
string machine (string state, char c, string chain, int line, int column, vector<token> *ptrResult); // process caracter and return the next state
token newToken (int id, string content, int line, int column); // build a new token
int tokenRecognizer(string chain); // Return token Id
bool isLetter(char c); // a..z, A..Z
bool isDigit(char c);  // 0..9
bool isFinal(char c); // space \n ; EOF
bool isSpecial(char c); // { } : , ( ) *