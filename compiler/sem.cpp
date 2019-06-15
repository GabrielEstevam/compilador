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
int type = 0;

bool applyRule(int rule, string param) {
	switch (rule){
		case 1:
			return rule1();
		case 2:
			return rule2(param);
		case 3:
			return rule3(param);
		case 4:
			return rule4();
		case 5:
			return rule5();
		case 6: 
			return rule6();
		case 7:
			return rule7();
		case 8:
			return rule8(param);
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

bool queryInTable(string level, string name, int category, int type) {
	
}

bool revomeInTable() {

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

bool rule3(string param){
	for (int i = 0; i < symbolsTable.size(); i++){
		if (symbolsTable[i].level == stack_level.back() and symbolsTable[i].name == param and symbolsTable[i].category == VARIABLE){
			cout << "\033[1;31m" << "\nErro Semantico. Variável "<<param<< " já declarada!" << "\033[0m" << endl;
			return 0;
		}
	}
	return insertInTable(stack_level.back(), param, VARIABLE, NULL_TYPE);
}

bool rule4(){
	for (int i = symbolsTable.size()-1; i >= 0 ; i--){
		if(symbolsTable[i].type != NULL_TYPE)
			break;
		symbolsTable[i].type = INTEGER;
	}
	return 1;	
}

bool rule5(){
	for (int i = symbolsTable.size()-1; i >= 0 ; i--){
		if(symbolsTable[i].type != NULL_TYPE)
			break;
		symbolsTable[i].type = FLOAT;
	}
	return 1;	
}

bool rule6(){
	for (int i = symbolsTable.size()-1; i >= 0 ; i--){
		if(symbolsTable[i].type != NULL_TYPE)
			break;
		symbolsTable[i].type = STRING;
	}
	return 1;	
}

bool rule7(){
	for (int i = symbolsTable.size()-1; i >= 0 ; i--){
		if(symbolsTable[i].type != NULL_TYPE)
			break;
		symbolsTable[i].type = CHAR;
	}
	return 1;	
}

bool rule8(string param){
	symbolsTable[symbolsTable.size()-1].name = param;
	insertInStackLevel(param);
	for (int i = 0; i < symbolsTable.size()-1; i++){
		cout <<"level["<<i+1<<"]: "<<symbolsTable[i].level<< "  ;  "<< symbolsTable[symbolsTable.size()-1].level <<endl;
		if (symbolsTable[i].level == symbolsTable[symbolsTable.size()-1].level and symbolsTable[i].name == symbolsTable[symbolsTable.size()-1].name and symbolsTable[i].category == FUNCTION and symbolsTable[i].type == symbolsTable[symbolsTable.size()-1].type){
			cout << "\033[1;31m" << "\nErro Semantico. Função "<<param<< " já declarada!" << "\033[0m" << endl;
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