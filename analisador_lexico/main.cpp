/*
	File name: main.cpp
	Data: 2019, April.
	Project description: Building a Compiler for DEC7565 at Computer Engineering. 
	File description: the project main file, for while just read entry file and execute the lexical analysis.
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

using namespace std;

vector <char> readFile (string file); // read file and process char by char

int main(int argc, char *argv[]) {
	
	if (argc != 2) {
		cout << "Argumento Invalido!" << endl;
		return 0;
	}
	string file = argv[1];

	cout << "File: " << file << endl; 

	// Files Variables
	vector <char> entry = readFile(file);
	entry.push_back(-1);

	vector <token> tk = lexicalAnalysis(entry);

	for (int i = 0; i < tk.size(); i++)
		cout << "<" << tk[i].id << ", " << tk[i].content << ">" << endl;

	return 0;
}

vector <char> readFile(string file) {
	ifstream ffile (file);
	char c;
	string line;
	vector <char> result;

	if (ffile.is_open()) {
		while (getline(ffile, line)) {
			for (int i = 0; i < line.size(); i++) {
				result.push_back(line[i]);
			}
		}
		ffile.close();
	}
	return result;
}