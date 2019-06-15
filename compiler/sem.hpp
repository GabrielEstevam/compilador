/*
	File name: sem.hpp
	Data: 2019, June.
	Project description: Building a Compiler for DEC7565 at Computer Engineering. 
	File description: semantics analyzer functions definition. 
	Authors: Gabriel Estevam de Oliveira (15104138)
			 Vinícius Rodrigues Zanon (15102833)
*/

#include <string>

using namespace std;

// Define categories
#define NULL_CATEGORY -1
#define VARIABLE 0
#define FUNCTION 1

// Define types
#define NULL_TYPE -1
#define VOID 0
#define INTEGER 1
#define FLOAT 2
#define CHAR 3
#define STRING 4

// Define structures
struct tableLine {
	string level;
	string name;
	int category;
	int type;
};

/* Only Public Function*/
bool applyRule(int rule, string param); /* Return: 0 - Error Semantics, 1 - Non Error */

/* Private Function definitions*/
// auxiliar functions for table
void printEntireTable();
bool insertInTable(string level, string name, int category, int type);
bool queryInTable(string level, string name, int category, int type);
bool revomeInTable();

// auxiliar functions for stacklevel
bool insertInStackLevel(string level);
bool queryInTopStackLevel(string level);
bool removeInStackLevel();

// semantics rules
bool rule1();
bool rule2(string param);
bool rule3(string param);
bool rule4();
bool rule5();
bool rule6();
bool rule7();
bool rule8(string param); // olhar
bool rule9();
bool rule10();
bool rule11();
bool rule12();
bool rule13();
bool rule14();
/* End private functions definitions*/