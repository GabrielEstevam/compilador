/*
	File name: lex.cpp
	Data: 2019, April.
	Project description: Building a Compiler for DEC7565 at Computer Engineering. 
	File description: lexical analyzer functions implementation. 
	Authors: Gabriel Estevam de Oliveira (15104138)
			 Vinícius Rodrigues Zanon (15102833)
*/

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

#define space 32
#define dot_comma 59
#define break_line 13

using namespace std;

vector <token> lexicalAnalysis(vector <char> entry) {
	// Machine Variables
	string state = "q0", chain = "";	
	int line = 1, column = 0;
	bool flag = false;

	int ptrChar = 0;
	vector <token> *result = new vector <token>;

	for (int ptrChar = 0; ptrChar < entry.size(); ptrChar++) {
		if ((entry[ptrChar] == dot_comma or entry[ptrChar] == ',' or entry[ptrChar] == ':') and chain.size() != 0)
			flag = true;
		
		state = machine(state, entry[ptrChar], chain, line, column, result);
		if (state == "q0") {
			if (chain.size() == 0)
				flag = false;
			else
				chain = "";
		} else {
			if (entry[ptrChar] != '\'' and entry[ptrChar] != '"' and entry[ptrChar] != '~' and entry[ptrChar] != EOF and entry[ptrChar] != break_line and entry[ptrChar] != dot_comma and entry[ptrChar] != ',')
				chain += entry[ptrChar];
		}

		if (flag)
			state = machine(state, entry[ptrChar], "", line, column, result);
		flag = false;
		
		if (entry[ptrChar] == break_line) {
			line++;
			column = 0;
		} else {
			column++;
		}
	}
	
	return *result;
}

string machine (string state, char c, string chain, int line, int column, vector<token> *ptrResult) {
	
	if (state == "q0") {
		if (isLetter(c)) {
			return "q1";
		} else if(isDigit(c)){
			return "q2";
		} else if (c == '=') {
			return "q3";
		} else if (c == '!') {
			return "q4";
		} else if (c == '>') {
			return "q5";
		} else if (c == '<') {
			return "q6";
		} else if (c == '+') {
			return "q7";
		} else if (c == '-') {
			return "q8";
		} else if (c == '\'') {
			return "q9";
		} else if (c == '"') {
			return "qA";
		} else if (c == '~') {
			return "qB";
		} else if (c == '/') {
			return "qC";
		} else if (isSpecial(c) or c == ';') {
			ptrResult->push_back(newToken(tokenRecognizer(chain = c), chain = c, line, column));
			return "q0";
		} else if (isFinal(c) and c != ';') {
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: caracter nao esperado" << "\033[0m" << endl;
			return "q0";
		}

	} else if (state == "q1") {
		if (isLetter(c) or isDigit(c)) {
			return "q1";
		} else if (isFinal(c) or c == ',' or c == ':') {
			if (chain.size() <= 64)
				ptrResult->push_back(newToken(tokenRecognizer(chain), chain, line, column));
			else
				cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: tamanho excedido para cadeia de caracteres" << "\033[0m" << endl;
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: declaracao de palavra reservada ou identificador" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q2") {
		if (isDigit(c)) {
			return "q2";
		} else if (c == '.') {
			return "q21";
		} else if (isFinal(c)) {
			if (chain.size() <= 4)
				ptrResult->push_back(newToken(5, chain, line, column));
			else
				cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: tamanho excedido para integer" << "\033[0m" << endl;
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: declaracao de inteiro" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q21") {
		if (isDigit(c)) {
			return "q22";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: declaracao de float, no minimo um digito apos a virgula" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q22") {
		if (isDigit(c)) {
			return "q22";
		} else if (isFinal(c)) {
			if (chain.size() <= 9)
				ptrResult->push_back(newToken(6, chain, line, column));
			else
				cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: tamanho excedido para float" << "\033[0m" << endl;
			return "q0";	
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: declaracao de float" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q3") {
		if (c == '=') {
			ptrResult->push_back(newToken(tokenRecognizer(chain + c), chain + c, line, column));
			return "q0";
		} else if (c == space) {
			ptrResult->push_back(newToken(tokenRecognizer(chain), chain, line, column));
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: operador de igualdade" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q4") {
		if (c == '=') {
			ptrResult->push_back(newToken(tokenRecognizer(chain + c), chain + c, line, column));
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: experado '='" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q5") {
		if (c == '>') {
			ptrResult->push_back(newToken(tokenRecognizer(chain + c), chain + c, line, column));
			return "q0";
		} else if (c == '=') {
			ptrResult->push_back(newToken(tokenRecognizer(chain + c), chain + c, line, column));
			return "q0";
		} else if (c == space) {
			ptrResult->push_back(newToken(tokenRecognizer(chain), chain, line, column));
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: esperado '>', '=' ou espaco" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q6") {
		if (c == '<') {
			ptrResult->push_back(newToken(tokenRecognizer(chain + c), chain + c, line, column));
			return "q0";
		} else if (c == '=') {
			ptrResult->push_back(newToken(tokenRecognizer(chain + c), chain + c, line, column));
			return "q0";
		} else if (c == space) {
			ptrResult->push_back(newToken(tokenRecognizer(chain), chain, line, column));
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: esperado '<', '=' ou espaco" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q7") {
		if (c == '+') {
			ptrResult->push_back(newToken(tokenRecognizer(chain + c), chain + c, line, column));
			return "q0";
		} else if (c == space) {
			ptrResult->push_back(newToken(tokenRecognizer(chain), chain, line, column));
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: esperado '+' ou espaco" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q8") {
		if (c == '-') {
			ptrResult->push_back(newToken(tokenRecognizer(chain + c), chain + c, line, column));
			return "q0";
		} else if (c == space) {
			ptrResult->push_back(newToken(tokenRecognizer(chain), chain, line, column));
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: esperado '-' ou espaco" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q9") {
		if (c != '\'' and c != EOF and c != break_line) {
			return "q91";
		} else if (c == '\'') {
			ptrResult->push_back(newToken(8, chain, line, column));
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: nao esperado quebra de linha ou final de arquivo em declaracao de char" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "q91") {
		if (c == '\'') {
			ptrResult->push_back(newToken(8, chain, line, column));
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: esperado aspas simples" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "qA") {
		if (c != '"') {
			return "qA1";
		} else {
			ptrResult->push_back(newToken(10, chain, line, column));
			return "q0";
		}
	} else if (state == "qA1") {
		if (c != '"' and c != break_line and c != 0) {
			return "qA1";
		} else if (c == '\"') {
			if (chain.size() <= 32)
				ptrResult->push_back(newToken(10, chain, line, column));
			else 
				cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: tamanho excedido para string" << "\033[0m" << endl;
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: nao esperado quebra de linha ou final de arquivo em declaracao de string" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "qB") {
		if (c != '~') {
			return "qB1";
		} else {
			ptrResult->push_back(newToken(12, chain, line, column));
			return "q0";
		}
	} else if (state == "qB1") {
		if (c != '~' and c != break_line and c != 0) {
			return "qB1";
		} else if (c == '~') {
			if (chain.size() <= 32)
				ptrResult->push_back(newToken(12, chain, line, column));
			else 
				cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: tamanho excedido para literal" << "\033[0m" << endl;
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: nao esperado quebra de linha ou final de arquivo em declaracao de literal" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "qC") {
		if (c == '*') {
			return "qC1";
		} else if (c == space) {
			ptrResult->push_back(newToken(tokenRecognizer(chain), chain, line, column));
			return "q0";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: esperado espaco ou '*'" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "qC1") {
		if (c != '*' and c != EOF) {
			return "qC1";
		} else if (c == '*') {
			return "qC11";
		} else {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: nao esperado fim de arquivo" << "\033[0m" << endl;
			return "q0";
		}
	} else if (state == "qC11") {
		if (c == '/') {
			return "q0";
		} else if (c == EOF) {
			cout << "\033[1;31m" << "ERRO <linha: " << line << ", coluna: " << column << ">: esperado '/'" << "\033[0m" << endl;
			return "q0";
		} else {
			return "qC1";
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
	if(c == space or c == dot_comma or c == break_line or c == EOF or c == 9) 
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