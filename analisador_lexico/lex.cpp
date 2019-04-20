#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <set>
#include <iterator>
#include <fstream>
#include <vector>

#include "lex.hpp"

using namespace std;

vector <token> lexicalAnalysis(vector <char> entry) {
	// Machine Variables
	string state = "q0", chain = "";	
	int line, column = line = 0;
	int bLine, bColumn; //before line and column

	int ptrChar = 0;
	vector <token> *result = new vector <token>;

	while (ptrChar < entry.size()){
		if (entry[ptrChar] == 13) {
			bLine = line;
			bColumn = column;
			line++;
			column = 0;
		}

		state = machine(state, entry[ptrChar], chain, line, column, result);

		//if (isFinal(entry[ptrChar]))
		//	ptrChar--;

		if (state == "q0") {
			chain = "";
			chain += entry[ptrChar];
			entry[ptrChar] = 0;
			if (chain == ";") {
				state = machine(state, entry[ptrChar], chain, line, column, result);
			}
			chain = "";
		}
		
		if (state == "qErr")
			state = "";
		if (entry[ptrChar] != 0)
			chain = chain + entry[ptrChar];
		
		ptrChar++;
	}
	// Virtual EOF
	state = machine(state, 0, chain, bLine, bColumn, result);

	return *result;
}

string machine (string state, char c, string chain, int line, int column, vector<token> *ptrResult) {
	
	if (state == "q0") {
		if (isLetter(c)) {
			return "q1";
		} else if (isSpecial(c) or c == 0) {
			ptrResult->push_back(newToken(tokenRecognizer(chain), chain, line, column));
			return "q0";
		}
	} else if (state == "q1") {
		if (isLetter(c) or isDigit(c)) {
			return "q1";
		} else if (isFinal(c)) {
			ptrResult->push_back(newToken(tokenRecognizer(chain), chain, line, column));
			return "q0";
		} else {
			cout << "ERRO <l: " << line << ", c: " << column << ">: caracter nao esperado no contexto" << endl;
			return "q0";
		}
	}

	return "q0";
}

token newToken (int id, string content, int line, int column) {
	token tk;
	tk.id = id;
	tk.content = content;
	tk.line = line;
	tk.column = column;
	return tk;
}

int tokenRecognizer(string chain) {
	
	map <string, int> mapToken;

	mapToken["while"] = 1;
	mapToken["void"] = 2;
	mapToken["string"] = 3;
	mapToken["return"] = 4;
	mapToken["main"] = 11;
	mapToken["integer"] = 13;
	mapToken["inicio"] = 15;
	mapToken["if"] = 16;
	mapToken[""] = 17;
	mapToken["for"] = 18;
	mapToken["float"] = 19;
	mapToken["fim"] = 20;
	mapToken["else"] = 21;
	mapToken["double"] = 22;
	mapToken["do"] = 23;
	mapToken["cout"] = 24;
	mapToken["cin"] = 25;
	mapToken["char"] = 26;
	mapToken["callfuncao"] = 27;
	mapToken[">>"] = 28;
	mapToken[">="] = 29;
	mapToken[">"] = 30;
	mapToken["=="] =31;
	mapToken[ "="] = 32;
	mapToken["<="] = 33;
	mapToken["<<"] = 34;
	mapToken["<"] = 35;
	mapToken["++"] = 36;
	mapToken["+"] = 37;
	mapToken["}"] = 38;
	mapToken["{"] = 39;
	mapToken[";"] = 40;
	mapToken[":"] = 41;
	mapToken["/"] = 42;
	mapToken[","] = 43;
	mapToken["*"] = 44;
	mapToken[")"] = 45;
	mapToken["("] = 46;
	mapToken["!="] = 48;
	mapToken["--"] = 49;
	mapToken["-"] = 50;

	if (mapToken[chain])
		return mapToken[chain];
	return 7; // default "nomevariavel"
}


bool isLetter(char c){
	if((c >= 65 and c <= 90) or (c >= 97 and c <= 122)) 
		return 1;
	else 
		return 0;
}
bool isDigit(char c){
	if((c >= 48 and c <= 57)) 
		return 1;
	else 
		return 0;
}

bool isFinal(char c){
	if(c == 32  or c == 59 or c == 13 or c == 0) 
		return 1;
	else 
		return 0;
}

bool isSpecial(char c){
	if(c == 123  or c == 125 or c == 58 or c == 44 or c == 40 or c == 41 or c == 42)  
		return 1;
	else 
		return 0;
}

bool isOther(char c){
	if (isLetter(c) or isDigit(c) or isFinal(c) or isSpecial(c)) 
		return 0;
	else 
		return 1;
}