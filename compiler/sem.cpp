/*
	File name: sin.cpp
	Data: 2019, June.
	Project description: Building a Compiler for DEC7565 at Computer Engineering. 
	File description: semantics analyzer functions implementation. 
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

#include "sem.hpp"

using namespace std;

vector <tableLine> symbolsTable;
vector <string> stack_level;
int current_function = 0;
int count_param = 0;
int type = 0;

bool applyRule(int rule, string param, int line) {
	switch (rule){
		case 1:
			return rule1();
		case 2:
			return rule2(param);
		case 3:
			return rule3(param, line);
		case 4:
			return rule4();
		case 5:
			return rule5();
		case 6: 
			return rule6();
		case 7:
			return rule7();
		case 8:
			return rule8(param, line);
		case 9:
			return rule9();
		case 10:
			return rule10();
		case 11:
			return rule11();
		case 12:
			return rule12();
		case 13:
			return rule13();
		case 14:
			return rule14();
		case 15:
			return rule15(line);
		case 16:
			return rule16(line);
		case 17:
			return rule17(param, line);
		case 18:
			return rule18(line);
		case 19:
			return rule19(line);
		case 20:
			return rule20(line);
		case 21:
			return rule21(param, line);
		case 22:
			return rule22();
		case 23:
			return rule23();
		case 24:
			return rule24();
		case 25:
			return rule25(param, line);
		case 26:
			return rule26(param, line);
		case 27:
			return rule27(param, line);
		case 28:
			return rule28(line);
		case 29:
			return rule29(line);
		case 30:
			return rule30(param, line);
		case 31:
			return rule31(line);
		case 32:
			return rule32(line);
		case 33:
			return rule33(param, line);
		case 34:
			return rule34();
		case 35:
			return rule35(line);
		case 36:
			return rule36();
		case 37:
			return rule37(line);
		default:
			return 1;
	}
}

void printEntireTable () {
	cout << "\n == Symbols Table (Level, Name, Category, Type) ==" << endl;
	for (int i = 0; i < symbolsTable.size(); i++)
		cout << i <<": " << symbolsTable[i].level << " " << symbolsTable[i].name << " " << symbolsTable[i].category << " " << symbolsTable[i].type << endl;
}

bool insertInTable (string level, string name, int category, int type) {
	tableLine row;
	row.level = level;
	row.name = name;
	row.category = category;
	row.type = type;
	
	symbolsTable.push_back(row);
	cout << "\n == Inserting in Symbols Table ==" << endl;
	cout << "Level, Name, Category, Type: " << row.level << " " << row.name << " " << row.category << " " << row.type << endl;
	return 1;
}

bool pushTypeFunctionParam (int index, int type) {
	symbolsTable[index].param_type.push_back(type);
	cout << "\n == Inserting (Param Function) in Symbols Table ==" << endl;
	cout << "Level, Function, Type: " << symbolsTable[index].level << " " << symbolsTable[index].name << " " << type << endl;
	return 1;
}

bool insertInStackLevel(string level){
	stack_level.push_back(level);
	cout<<"Inserting in stack_level: "<< level<< endl;
	return 1;
}

bool queryInTopStackLevel(string level){
	cout<<"Searching in stack_level: "<< level<< endl;
	if(stack_level.back() == level)
		return 1;
	return 0;
}

bool removeInStackLevel(){
	if(stack_level.size() > 0){
		cout<<"Removing of stack_level: "<< stack_level.back()<< endl;
		stack_level.pop_back();
		return 1;
	} 
	return 0;
}

bool rule1() {
	return insertInStackLevel("main");	
}

bool rule2(string param) {
	return insertInTable(stack_level.back(), param, VARIABLE, NULL_TYPE);
}

bool rule3(string param, int line){
	for (int i = 0; i < symbolsTable.size(); i++){
		if (symbolsTable[i].level == stack_level.back() and symbolsTable[i].name == param and symbolsTable[i].category == VARIABLE){
			cout << "\033[1;31m" << "\nErro Semantico. Variável \'" <<param<< "\' já declarada! Linha: " << line << "\033[0m" << endl;
			return 0;
		}
	}
	return insertInTable(stack_level.back(), param, VARIABLE, NULL_TYPE);
}

bool rule4(){
	if (symbolsTable[symbolsTable.size()-1].category == FUNCTION) {
		pushTypeFunctionParam(symbolsTable.size()-1, INTEGER);
		return 1;
	}
	for (int i = symbolsTable.size()-1; i >= 0 ; i--){
		if(symbolsTable[i].type != NULL_TYPE or symbolsTable[i].category != VARIABLE)
			break;
		symbolsTable[i].type = INTEGER;
	}
	return 1;	
}

bool rule5(){
	if (symbolsTable[symbolsTable.size()-1].category == FUNCTION) {
		pushTypeFunctionParam(symbolsTable.size()-1, FLOAT);
		return 1;
	}
	for (int i = symbolsTable.size()-1; i >= 0 ; i--){
		if(symbolsTable[i].type != NULL_TYPE or symbolsTable[i].category != VARIABLE)
			break;
		symbolsTable[i].type = FLOAT;
	}
	return 1;	
}

bool rule6(){
	if (symbolsTable[symbolsTable.size()-1].category == FUNCTION) {
		pushTypeFunctionParam(symbolsTable.size()-1, STRING);
		return 1;
	}
	for (int i = symbolsTable.size()-1; i >= 0 ; i--){
		if(symbolsTable[i].type != NULL_TYPE or symbolsTable[i].category != VARIABLE)
			break;
		symbolsTable[i].type = STRING;
	}
	return 1;	
}

bool rule7(){
	if (symbolsTable[symbolsTable.size()-1].category == FUNCTION) {
		pushTypeFunctionParam(symbolsTable.size()-1, CHAR);
		return 1;
	}
	for (int i = symbolsTable.size()-1; i >= 0 ; i--){
		if(symbolsTable[i].type != NULL_TYPE or symbolsTable[i].category != VARIABLE)
			break;
		symbolsTable[i].type = CHAR;
	}
	return 1;	
}

bool rule8(string param, int line){
	symbolsTable[symbolsTable.size()-1].name = param;
	insertInStackLevel(param);
	for (int i = 0; i < symbolsTable.size()-1; i++){
		if (symbolsTable[i].level == symbolsTable[symbolsTable.size()-1].level and symbolsTable[i].name == symbolsTable[symbolsTable.size()-1].name and symbolsTable[i].category == FUNCTION and symbolsTable[i].type == symbolsTable[symbolsTable.size()-1].type){
			cout << "\033[1;31m" << "\nErro Semantico. Função \'" <<param<< "\' já declarada! Linha: " << line << "\033[0m" << endl;
			return 0;
		}
	}
	return 1;
}

bool rule9(){
	return removeInStackLevel();
}

bool rule10(){
	return insertInTable(stack_level.back(), "", FUNCTION, INTEGER);
}

bool rule11(){
	return insertInTable(stack_level.back(), "", FUNCTION, VOID);
}

bool rule12(){
	return insertInTable(stack_level.back(), "", FUNCTION, CHAR);
}

bool rule13(){
	return insertInTable(stack_level.back(), "", FUNCTION, FLOAT);
}

bool rule14(){
	return insertInTable(stack_level.back(), "", FUNCTION, STRING);
}

bool rule15(int line){
	int index;
	for (int i = 0; i < symbolsTable.size(); i++) {
		if (symbolsTable[i].name == stack_level.back() and symbolsTable[i].category == FUNCTION) {
			index = i;
			break;
		}
	}
	if (symbolsTable[index].type == INTEGER) 
		return 1;
	cout << "\033[1;31m" << "\nErro Semantico. Tipo de retorno incoerente! Linha: " << line << "\033[0m" << endl;
	return 0;
}

bool rule16(int line){
	int index;
	for (int i = 0; i < symbolsTable.size(); i++) {
		if (symbolsTable[i].name == stack_level.back() and symbolsTable[i].category == FUNCTION) {
			index = i;
			break;
		}
	}
	if (symbolsTable[index].type == FLOAT) 
		return 1;
	cout << "\033[1;31m" << "\nErro Semantico. Tipo de retorno incoerente! Linha: " << line << "\033[0m" << endl;
	return 0;
}

bool rule17(string param, int line){
	int index_variable = -1, index_function;
	for (int i = 0; i < symbolsTable.size(); i++){
		if (symbolsTable[i].level == stack_level.back() and symbolsTable[i].name == param and symbolsTable[i].category == VARIABLE){
			index_variable = i;
			break;
		}
	}
	if (index_variable == -1) {
		cout << "\033[1;31m" << "\nErro Semantico. Variável \'" <<param<< "\' não declarada! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	for (int i = 0; i < symbolsTable.size(); i++) {
		if (symbolsTable[i].name == stack_level.back() and symbolsTable[i].category == FUNCTION) {
			index_function = i;
			break;
		}
	}
	if (symbolsTable[index_function].type == symbolsTable[index_variable].type) 
		return 1;
	cout << "\033[1;31m" << "\nErro Semantico. Tipo de retorno incoerente! Linha: " << line << "\033[0m" << endl;
	return 0;
}

bool rule18(int line){
	int index;
	for (int i = 0; i < symbolsTable.size(); i++) {
		if (symbolsTable[i].name == stack_level.back() and symbolsTable[i].category == FUNCTION) {
			index = i;
			break;
		}
	}
	if (symbolsTable[index].type == CHAR) 
		return 1;
	cout << "\033[1;31m" << "\nErro Semantico. Tipo de retorno incoerente! Linha: " << line << "\033[0m" << endl;
	return 0;
}

bool rule19(int line){
	int index;
	for (int i = 0; i < symbolsTable.size(); i++) {
		if (symbolsTable[i].name == stack_level.back() and symbolsTable[i].category == FUNCTION) {
			index = i;
			break;
		}
	}
	if (symbolsTable[index].type == STRING) 
		return 1;
	cout << "\033[1;31m" << "\nErro Semantico. Tipo de retorno incoerente! Linha: " << line << "\033[0m" << endl;
	return 0;
}

bool rule20(int line){
	int index;
	for (int i = 0; i < symbolsTable.size(); i++) {
		if (symbolsTable[i].name == stack_level.back() and symbolsTable[i].category == FUNCTION) {
			index = i;
			break;
		}
	}
	if (symbolsTable[index].type == VOID) 
		return 1;
	cout << "\033[1;31m" << "\nErro Semantico. Tipo de retorno incoerente! Linha: " << line << "\033[0m" << endl;
	return 0;
}

bool rule21(string param, int line){
	int index_variable = -1, index_function;
	for (int i = 0; i < symbolsTable.size(); i++){
		if (symbolsTable[i].level == stack_level.back() and symbolsTable[i].name == param and symbolsTable[i].category == VARIABLE){
			index_variable = i;
			break;
		}
	}
	if (index_variable == -1) {
		cout << "\033[1;31m" << "\nErro Semantico. Variável \'" <<param<< "\' não declarada! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	type = symbolsTable[index_variable].type;
	return 0;
}

bool rule22() {
	type = STRING;
	return 0;
}

bool rule23() {
	type = CHAR;
	return 0;
}

bool rule24() {
	type = VOID;
	return 0;
}

bool rule25(string param, int line){
	int index_function = -1;
	for (int i = 0; i < symbolsTable.size(); i++){
		if (symbolsTable[i].level == stack_level.back() and symbolsTable[i].name == param and symbolsTable[i].category == FUNCTION)
			index_function = i;
	}
	if (index_function == -1) {
		cout << "\033[1;31m" << "\nErro Semantico. Função \'" <<param<< "\' não declarada! Linha: " << line << "\033[0m" << endl;
		return 0;
	} 
	current_function = index_function;
	if (symbolsTable[index_function].type != VOID) {
		cout << "\033[1;31m" << "\nErro Semantico. Tipo de retorno incoerente! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}

bool rule26(string param, int line){
	int index_variable = -1;
	for (int i = 0; i < symbolsTable.size(); i++){
		if (symbolsTable[i].level == stack_level.back() and symbolsTable[i].name == param and symbolsTable[i].category == VARIABLE){
			index_variable = i;
			break;
		}
	}
	if (index_variable == -1) {
		cout << "\033[1;31m" << "\nErro Semantico. Variável \'" <<param<< "\' não declarada! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}

bool rule27(string param, int line){
	int index_function = -1;
	for (int i = 0; i < symbolsTable.size(); i++){
		if (symbolsTable[i].level == stack_level.back() and symbolsTable[i].name == param and symbolsTable[i].category == FUNCTION)
			index_function = i;
	}
	if (index_function == -1) {
		cout << "\033[1;31m" << "\nErro Semantico. Função \'" <<param<< "\' não declarada! Linha: " << line << "\033[0m" << endl;
		return 0;
	} 
	current_function = index_function;
	if (symbolsTable[index_function].type != type) {
		cout << "\033[1;31m" << "\nErro Semantico. Tipo de retorno incoerente! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}

bool rule28(int line) {
	if (type != INTEGER) {
		cout << "\033[1;31m" << "\nErro Semantico. Tipo incoerente com expressão! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}

bool rule29(int line) {
	if (type != FLOAT) {
		cout << "\033[1;31m" << "\nErro Semantico. Tipo incoerente com expressão! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}

bool rule30(string param, int line){
	int index_variable = -1;
	for (int i = 0; i < symbolsTable.size(); i++){
		if (symbolsTable[i].level == stack_level.back() and symbolsTable[i].name == param and symbolsTable[i].category == VARIABLE){
			index_variable = i;
			break;
		}
	}
	if (index_variable == -1) {
		cout << "\033[1;31m" << "\nErro Semantico. Variável \'" <<param<< "\' não declarada! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	if (type != symbolsTable[index_variable].type) {
		cout << "\033[1;31m" << "\nErro Semantico. Tipo incoerente com expressão! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}

bool rule31(int line) {
	if (type != STRING) {
		cout << "\033[1;31m" << "\nErro Semantico. Tipo incoerente com expressão! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}

bool rule32(int line) {
	if (type != CHAR) {
		cout << "\033[1;31m" << "\nErro Semantico. Tipo incoerente com expressão! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}

bool rule33(string param, int line){
	int index_variable = -1;
	for (int i = 0; i < symbolsTable.size(); i++){
		if (symbolsTable[i].level == stack_level.back() and symbolsTable[i].name == param and symbolsTable[i].category == VARIABLE){
			index_variable = i;
			break;
		}
	}
	if (index_variable == -1) {
		cout << "\033[1;31m" << "\nErro Semantico. Variável \'" <<param<< "\' não declarada! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	type = symbolsTable[index_variable].type;
	return 1;
}

bool rule34() {
	count_param = 0;
	return 1;
}

bool rule35(int line) {
	if (count_param + 1 != symbolsTable[current_function].param_type.size()) {
		cout << "\033[1;31m" << "\nErro Semantico. Numero de parametros inconsistente com \'" << symbolsTable[current_function].name << "\'! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}

bool rule36() {
	count_param++;
	return 1;
}

bool rule37(int line) {
	if (symbolsTable[current_function].param_type.size() != 0) {
		cout << "\033[1;31m" << "\nErro Semantico. Numero de parametros inconsistente com \'" << symbolsTable[current_function].name << "\'! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}

bool rule38(int line) {
	if (symbolsTable[current_function].param_type.size() < count_param) {
		cout << "\033[1;31m" << "\nErro Semantico. Numero de parametros inconsistente com \'" << symbolsTable[current_function].name << "\'! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	if (symbolsTable[current_function].param_type[count_param] != INTEGER) {
		cout << "\033[1;31m" << "\nErro Semantico. Tipo do parametro inconsistente com \'" << symbolsTable[current_function].name << "\'! Linha: " << line << "\033[0m" << endl;
		return 0;
	}
	return 1;
}