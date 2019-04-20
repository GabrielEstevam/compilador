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

int main(int argc, char *argv[]) {
	
	if (argc != 2) {
		cout << "Argumento Invalido!" << endl;
		return 0;
	}
	string file = argv[1];

	cout << "File: " << file << endl; 

	// Files Variables
	vector <char> entry = readFile(file);

	vector <token> tk = lexicalAnalysis(entry);

	for (int i = 0; i < tk.size(); i++)
		cout << "<" << tk[i].id << ", " << tk[i].content << ">" << endl;

	return 0;
}