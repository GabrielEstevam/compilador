/*
	File name: sin.cpp
	Data: 2019, April.
	Project description: Building a Compiler for DEC7565 at Computer Engineering. 
	File description: syntactic analyzer functions implementation. 
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

#include "sin.hpp"

using namespace std;

void syntacticAnalysis(vector <token> entry) {

	map < pair<int, int>, int> parseTable = initParseTable();
	map <int, pair<int, vector<int>> > rules = createRules();
	vector <int> execStack;
	int ptrEntry = 0;
	int ptrStack = 0;
	int i, Mx;

	// Syntactic Analyzer Algorithm
	execStack.push_back(51);
	printStack(execStack);
	while(!execStack.empty() and ptrEntry < entry.size()) {
		if (entry[ptrEntry].id == execStack.back()) {
			execStack.pop_back();
			printToken(entry, ptrEntry, execStack);
			ptrEntry++;
		} else {
			Mx = parseTable[make_pair(execStack.back(), entry[ptrEntry].id)];
			if (Mx != 0) {
				execStack.pop_back();
				for (i = rules[Mx].second.size()-1; i >= 0; i--)
					execStack.push_back(rules[Mx].second[i]);
				printStack(execStack);
			} else {
				cout << "\033[1;31m" << "\nErro Sintatico." << "\033[0m" << " Linha: " << entry[ptrEntry].line << endl;
				cout << "Nao esperado: " << entry[ptrEntry].content << endl;
				cout << "ID do token esperado: " << execStack.back() << endl;
				break;
			}
		}
	}
}

map < pair<int, int>, int> initParseTable() {
	map < pair<int, int>, int> parseTable;
	parseTable[make_pair(51,2)] = 1;
	parseTable[make_pair(52,2)] = 3;
	parseTable[make_pair(52,3)] = 3;
	parseTable[make_pair(52,7)] = 2;
	parseTable[make_pair(52,13)] = 3;
	parseTable[make_pair(52,15)] = 3;
	parseTable[make_pair(52,19)] = 3;
	parseTable[make_pair(52,26)] = 3;
	parseTable[make_pair(53,2)] = 13;
	parseTable[make_pair(53,3)] = 13;
	parseTable[make_pair(53,13)] = 13;
	parseTable[make_pair(53,15)] = 19;
	parseTable[make_pair(53,19)] = 13;
	parseTable[make_pair(53,26)] = 13;
	parseTable[make_pair(54,15)] = 31;
	parseTable[make_pair(55,41)] = 4;
	parseTable[make_pair(55,43)] = 5;
	parseTable[make_pair(56,3)] = 8;
	parseTable[make_pair(56,13)] = 6;
	parseTable[make_pair(56,19)] = 7;
	parseTable[make_pair(56,26)] = 9;
	parseTable[make_pair(57,2)] = 10;
	parseTable[make_pair(57,3)] = 10;
	parseTable[make_pair(57,7)] = 11;
	parseTable[make_pair(57,13)] = 10;
	parseTable[make_pair(57,15)] = 10;
	parseTable[make_pair(57,19)] = 10;
	parseTable[make_pair(57,26)] = 10;
	parseTable[make_pair(59,7)] = 12;
	parseTable[make_pair(60,2)] = 15;
	parseTable[make_pair(60,3)] = 18;
	parseTable[make_pair(60,13)] = 14;
	parseTable[make_pair(60,19)] = 17;
	parseTable[make_pair(60,26)] = 16;
	parseTable[make_pair(61,39)] = 26;
	parseTable[make_pair(61,46)] = 27;
	parseTable[make_pair(62,5)] = 20;
	parseTable[make_pair(62,6)] = 21;
	parseTable[make_pair(62,8)] = 23;
	parseTable[make_pair(62,9)] = 22;
	parseTable[make_pair(62,10)] = 24;
	parseTable[make_pair(62,45)] = 25;
	parseTable[make_pair(63,3)] = 28;
	parseTable[make_pair(63,13)] = 28;
	parseTable[make_pair(63,19)] = 28;
	parseTable[make_pair(63,26)] = 28;
	parseTable[make_pair(64,40)] = 29;
	parseTable[make_pair(64,45)] = 30;
	parseTable[make_pair(65,1)] = 52;
	parseTable[make_pair(65,7)] = 34;
	parseTable[make_pair(65,8)] = 36;
	parseTable[make_pair(65,10)] = 35;
	parseTable[make_pair(65,16)] = 49;
	parseTable[make_pair(65,18)] = 64;
	parseTable[make_pair(65,23)] = 67;
	parseTable[make_pair(65,24)] = 69;
	parseTable[make_pair(65,25)] = 68;
	parseTable[make_pair(65,27)] = 39;
	parseTable[make_pair(65,40)] = 38;
	parseTable[make_pair(66,1)] = 33;
	parseTable[make_pair(66,7)] = 33;
	parseTable[make_pair(66,8)] = 33;
	parseTable[make_pair(66,10)] = 33;
	parseTable[make_pair(66,16)] = 33;
	parseTable[make_pair(66,18)] = 33;
	parseTable[make_pair(66,20)] = 32;
	parseTable[make_pair(66,23)] = 33;
	parseTable[make_pair(66,24)] = 33;
	parseTable[make_pair(66,25)] = 33;
	parseTable[make_pair(66,27)] = 33;
	parseTable[make_pair(66,38)] = 32;
	parseTable[make_pair(66,40)] = 33;
	parseTable[make_pair(67,5)] = 75;
	parseTable[make_pair(67,6)] = 75;
	parseTable[make_pair(67,7)] = 75;
	parseTable[make_pair(67,8)] = 75;
	parseTable[make_pair(67,10)] = 75;
	parseTable[make_pair(67,27)] = 76;
	parseTable[make_pair(67,46)] = 75;
	parseTable[make_pair(68,40)] = 40;
	parseTable[make_pair(68,45)] = 40;
	parseTable[make_pair(68,46)] = 41;
	parseTable[make_pair(69,5)] = 44;
	parseTable[make_pair(69,6)] = 46;
	parseTable[make_pair(69,7)] = 48;
	parseTable[make_pair(69,8)] = 47;
	parseTable[make_pair(69,10)] = 45;
	parseTable[make_pair(70,43)] = 43;
	parseTable[make_pair(70,45)] = 42;
	parseTable[make_pair(71,29)] = 56;
	parseTable[make_pair(71,30)] = 55;
	parseTable[make_pair(71,31)] = 53;
	parseTable[make_pair(71,33)] = 58;
	parseTable[make_pair(71,35)] = 57;
	parseTable[make_pair(71,48)] = 54;
	parseTable[make_pair(72,21)] = 50;
	parseTable[make_pair(72,40)] = 51;
	parseTable[make_pair(73,5)] = 59;
	parseTable[make_pair(73,6)] = 60;
	parseTable[make_pair(73,7)] = 63;
	parseTable[make_pair(73,8)] = 62;
	parseTable[make_pair(73,10)] = 61;
	parseTable[make_pair(74,36)] = 65;
	parseTable[make_pair(74,49)] = 66;
	parseTable[make_pair(75,34)] = 90;
	parseTable[make_pair(75,40)] = 70;
	parseTable[make_pair(76,34)] = 73;
	parseTable[make_pair(76,40)] = 73;
	parseTable[make_pair(76,43)] = 74;
	parseTable[make_pair(79,5)] = 80;
	parseTable[make_pair(79,6)] = 80;
	parseTable[make_pair(79,7)] = 80;
	parseTable[make_pair(79,8)] = 80;
	parseTable[make_pair(79,10)] = 80;
	parseTable[make_pair(79,46)] = 80;
	parseTable[make_pair(80,37)] = 77;
	parseTable[make_pair(80,40)] = 79;
	parseTable[make_pair(80,45)] = 79;
	parseTable[make_pair(80,50)] = 78;
	parseTable[make_pair(81,5)] = 84;
	parseTable[make_pair(81,6)] = 85;
	parseTable[make_pair(81,7)] = 86;
	parseTable[make_pair(81,8)] = 88;
	parseTable[make_pair(81,10)] = 87;
	parseTable[make_pair(81,46)] = 89;
	parseTable[make_pair(82,37)] = 81;
	parseTable[make_pair(82,40)] = 81;
	parseTable[make_pair(82,42)] = 83;
	parseTable[make_pair(82,44)] = 82;
	parseTable[make_pair(82,45)] = 81;
	parseTable[make_pair(82,50)] = 81;
	parseTable[make_pair(83,7)] = 71;
	parseTable[make_pair(83,12)] = 72;
	return parseTable;
}

map < int, pair<int, vector<int>> > createRules() {
	map <int, pair<int, vector<int>> > rules;
	rules[1] = make_pair(41, vector<int> {2, 11, 39, 52, 53, 54, 38});
	rules[2] = make_pair(52, vector<int> {7, 55, 41, 56, 40, 57});
	rules[3] = make_pair(52, vector<int> {});
	rules[4] = make_pair(55, vector<int> {});
	rules[5] = make_pair(55, vector<int> {43, 7, 55});
	rules[6] = make_pair(56, vector<int> {13});
	rules[7] = make_pair(56, vector<int> {19});
	rules[8] = make_pair(56, vector<int> {3});
	rules[9] = make_pair(56, vector<int> {26});
	rules[10] = make_pair(57, vector<int> {});
	rules[11] = make_pair(57, vector<int> {59, 41, 56, 40, 57});
	rules[12] = make_pair(59, vector<int> {7, 55});
	rules[13] = make_pair(53, vector<int> {60, 7, 61, 39, 52, 53, 54, 4, 46, 62, 45, 38, 53});
	rules[14] = make_pair(60, vector<int> {13});
	rules[15] = make_pair(60, vector<int> {2});
	rules[16] = make_pair(60, vector<int> {26});
	rules[17] = make_pair(60, vector<int> {19});
	rules[18] = make_pair(60, vector<int> {3});
	rules[19] = make_pair(53, vector<int> {});
	rules[20] = make_pair(62, vector<int> {5});
	rules[21] = make_pair(62, vector<int> {6});
	rules[22] = make_pair(62, vector<int> {9});
	rules[23] = make_pair(62, vector<int> {8});
	rules[24] = make_pair(62, vector<int> {10});
	rules[25] = make_pair(62, vector<int> {});
	rules[26] = make_pair(61, vector<int> {});
	rules[27] = make_pair(61, vector<int> {46, 63, 45});
	rules[28] = make_pair(63, vector<int> {56, 64});
	rules[29] = make_pair(64, vector<int> {40, 56, 64});
	rules[30] = make_pair(64, vector<int> {});
	rules[31] = make_pair(54, vector<int> {15, 65, 40, 66, 20});
	rules[32] = make_pair(66, vector<int> {});
	rules[33] = make_pair(66, vector<int> {65, 40, 66});
	rules[34] = make_pair(65, vector<int> {7, 32, 67});
	rules[35] = make_pair(65, vector<int> {10, 32, 67});
	rules[36] = make_pair(65, vector<int> {8, 32, 67});
	rules[37] = make_pair(65, vector<int> {67, 32, 67});
	rules[38] = make_pair(65, vector<int> {});
	rules[39] = make_pair(65, vector<int> {27, 7, 68});
	rules[40] = make_pair(68, vector<int> {});
	rules[41] = make_pair(68, vector<int> {46, 69, 70, 45});
	rules[42] = make_pair(70, vector<int> {});
	rules[43] = make_pair(70, vector<int> {43, 69, 70});
	rules[44] = make_pair(69, vector<int> {5});
	rules[45] = make_pair(69, vector<int> {10});
	rules[46] = make_pair(69, vector<int> {6});
	rules[47] = make_pair(69, vector<int> {8});
	rules[48] = make_pair(69, vector<int> {7});
	rules[49] = make_pair(65, vector<int> {16, 46, 7, 71, 45, 39, 65, 40, 66, 38, 72});
	rules[50] = make_pair(72, vector<int> {21, 39, 65, 40, 66, 38});
	rules[51] = make_pair(72, vector<int> {});
	rules[52] = make_pair(65, vector<int> {1, 46, 7, 71, 45, 39, 65, 40, 66, 38});
	rules[53] = make_pair(71, vector<int> {31, 73});
	rules[54] = make_pair(71, vector<int> {48, 73});
	rules[55] = make_pair(71, vector<int> {30, 73});
	rules[56] = make_pair(71, vector<int> {29, 73});
	rules[57] = make_pair(71, vector<int> {35, 73});
	rules[58] = make_pair(71, vector<int> {33, 73});
	rules[59] = make_pair(73, vector<int> {5});
	rules[60] = make_pair(73, vector<int> {6});
	rules[61] = make_pair(73, vector<int> {10});
	rules[62] = make_pair(73, vector<int> {8});
	rules[63] = make_pair(73, vector<int> {7});
	rules[64] = make_pair(65, vector<int> {18, 46, 7, 32, 73, 40, 7, 71, 40, 74, 45, 39, 65, 40, 66, 38});
	rules[65] = make_pair(74, vector<int> {36, 5});
	rules[66] = make_pair(74, vector<int> {49, 5});
	rules[67] = make_pair(65, vector<int> {23, 39, 65, 40, 66, 38, 1, 46, 7, 71, 45});
	rules[68] = make_pair(65, vector<int> {25, 28, 7});
	rules[69] = make_pair(65, vector<int> {24, 34, 12, 75});
	rules[70] = make_pair(75, vector<int> {});
	rules[90] = make_pair(75, vector<int> {34, 83}); // append
	rules[71] = make_pair(83, vector<int> {7, 76, 75}); // modify
	rules[72] = make_pair(83, vector<int> {12, 75}); // modify
	rules[73] = make_pair(76, vector<int> {});
	rules[74] = make_pair(76, vector<int> {43, 7, 76});
	rules[75] = make_pair(67, vector<int> {79, 80});
	rules[76] = make_pair(67, vector<int> {27, 7, 68});
	rules[77] = make_pair(80, vector<int> {37, 79, 80});
	rules[78] = make_pair(80, vector<int> {50, 79, 80});
	rules[79] = make_pair(80, vector<int> {});
	rules[80] = make_pair(79, vector<int> {81, 82});
	rules[81] = make_pair(82, vector<int> {});
	rules[82] = make_pair(82, vector<int> {44, 81, 82});
	rules[83] = make_pair(82, vector<int> {42, 81, 82});
	rules[84] = make_pair(81, vector<int> {5});
	rules[85] = make_pair(81, vector<int> {6});
	rules[86] = make_pair(81, vector<int> {7});
	rules[87] = make_pair(81, vector<int> {10});
	rules[88] = make_pair(81, vector<int> {8});
	rules[89] = make_pair(81, vector<int> {46, 67, 45});
	return rules;
}

void printToken(vector <token> entry, int ptrEntry, vector <int> execStack) {
	int i;
	cout << "\n == Token Processado == " << endl;
	cout << "  ID: " << entry[ptrEntry].id << endl;
	cout << "  Token: " << entry[ptrEntry].content << endl;
	cout << "  Linha: " << entry[ptrEntry].line << endl;
	cout << "  Pilha: {$";
	for (i = 0; i < execStack.size(); i++)
		cout << ", " << execStack[i];
	cout << "}" << endl;
}

void printStack(vector <int> execStack) {
	int i;
	cout << "\n == Acao-Regra == " << endl;
	cout << "  Pilha: {$";
	for (i = 0; i < execStack.size(); i++)
		cout << ", " << execStack[i];
	cout << "}" << endl;	
}