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
	map <int, rule > rules = createRules();
	vector <pair <int, int>> execStack;
	int ptrEntry = 0;
	int ptrStack = 0;
	int i, Mx;

	// Syntactic Analyzer Algorithm
	execStack.push_back(make_pair(51, 1));
	//printStack(execStack);
	while(!execStack.empty() and ptrEntry < entry.size()) {
		if (entry[ptrEntry].id == execStack.back().first) {
			if (execStack.back().second != 0) {
				// regra semantica do token
				applyRule(execStack.back().second, entry[ptrEntry].content, entry[ptrEntry].line);
			}
			execStack.pop_back();
			
			//printToken(entry, ptrEntry, execStack);
			ptrEntry++;
		} else {
			Mx = parseTable[make_pair(execStack.back().first, entry[ptrEntry].id)];
			if (Mx != 0) {
				if (rules[Mx].header.second != 0) {
					// regra semantica da cabeca
					applyRule(rules[Mx].header.second, entry[ptrEntry].content, entry[ptrEntry].line);
				}
				execStack.pop_back();
				for (i = rules[Mx].body.size()-1; i >= 0; i--)
					execStack.push_back(rules[Mx].body[i]);
				//printStack(execStack);
			} else {
				cout << "\033[1;31m" << "\nErro Sintatico." << "\033[0m" << " Linha: " << entry[ptrEntry].line << endl;
				cout << "Nao esperado: " << entry[ptrEntry].content << endl;
				cout << "ID do token esperado: " << execStack.back().first << endl;
				break;
			}
		}
	}
	printEntireTable();
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

map < int, rule > createRules() {
	map <int, rule > rules;
	rules[1] = newRule(make_pair(51, 1), vector< pair <int, int> > {make_pair(2, 0), make_pair(11, 0), make_pair(39, 0), make_pair(52, 0), make_pair(53, 0), make_pair(54, 0), make_pair(38, 0)});
	rules[2] = newRule(make_pair(52, 0), vector< pair <int, int> > {make_pair(7, 2), make_pair(55, 0), make_pair(41, 0), make_pair(56, 0), make_pair(40, 0), make_pair(57, 0)});
	rules[3] = newRule(make_pair(52, 0), vector< pair <int, int> > {});
	rules[4] = newRule(make_pair(55, 0), vector< pair <int, int> > {});
	rules[5] = newRule(make_pair(55, 0), vector< pair <int, int> > {make_pair(43, 0), make_pair(7, 3), make_pair(55,0)});
	rules[6] = newRule(make_pair(56, 0), vector< pair <int, int> > {make_pair(13, 4)});
	rules[7] = newRule(make_pair(56, 0), vector< pair <int, int> > {make_pair(19, 5)});
	rules[8] = newRule(make_pair(56, 0), vector< pair <int, int> > {make_pair(3, 6)});
	rules[9] = newRule(make_pair(56, 0), vector< pair <int, int> > {make_pair(26, 7)});
	rules[10] = newRule(make_pair(57, 0), vector< pair <int, int> > {});
	rules[11] = newRule(make_pair(57, 0), vector< pair <int, int> > {make_pair(59, 0), make_pair(41, 0), make_pair(56, 0), make_pair(40, 0), make_pair(57, 0)});
	rules[12] = newRule(make_pair(59, 0), vector< pair <int, int> > {make_pair(7, 3), make_pair(55, 0)});
	rules[13] = newRule(make_pair(53, 0), vector< pair <int, int> > {make_pair(60, 0), make_pair(7, 8), make_pair(61, 0), make_pair(39, 0), make_pair(52, 0), make_pair(53, 0), make_pair(54, 0), make_pair(4, 0), make_pair(46, 0), make_pair(62, 0), make_pair(45, 0), make_pair(38, 9), make_pair(53, 0)});
	rules[14] = newRule(make_pair(60, 0), vector< pair <int, int> > {make_pair(13, 10)});
	rules[15] = newRule(make_pair(60, 0), vector< pair <int, int> > {make_pair(2, 11)});
	rules[16] = newRule(make_pair(60, 0), vector< pair <int, int> > {make_pair(26, 12)});
	rules[17] = newRule(make_pair(60, 0), vector< pair <int, int> > {make_pair(19, 13)});
	rules[18] = newRule(make_pair(60, 0), vector< pair <int, int> > {make_pair(3, 14)});
	rules[19] = newRule(make_pair(53, 0), vector< pair <int, int> > {});
	rules[20] = newRule(make_pair(62, 0), vector< pair <int, int> > {make_pair(5, 15)});
	rules[21] = newRule(make_pair(62, 0), vector< pair <int, int> > {make_pair(6, 16)});
	rules[22] = newRule(make_pair(62, 0), vector< pair <int, int> > {make_pair(9, 17)});
	rules[23] = newRule(make_pair(62, 0), vector< pair <int, int> > {make_pair(8, 18)});
	rules[24] = newRule(make_pair(62, 0), vector< pair <int, int> > {make_pair(10, 19)});
	rules[25] = newRule(make_pair(62, 20), vector< pair <int, int> > {});
	rules[26] = newRule(make_pair(61, 0), vector< pair <int, int> > {});
	rules[27] = newRule(make_pair(61, 0), vector< pair <int, int> > {make_pair(46, 0), make_pair(63, 0), make_pair(45, 0)});
	rules[28] = newRule(make_pair(63, 0), vector< pair <int, int> > {make_pair(56, 0), make_pair(64, 0)});
	rules[29] = newRule(make_pair(64, 0), vector< pair <int, int> > {make_pair(40, 0), make_pair(56, 0), make_pair(64, 0)});
	rules[30] = newRule(make_pair(64, 0), vector< pair <int, int> > {});
	rules[31] = newRule(make_pair(54, 0), vector< pair <int, int> > {make_pair(15, 0), make_pair(65, 0), make_pair(40, 0), make_pair(66, 0), make_pair(20, 0)});
	rules[32] = newRule(make_pair(66, 0), vector< pair <int, int> > {});
	rules[33] = newRule(make_pair(66, 0), vector< pair <int, int> > {make_pair(65, 0), make_pair(40, 0), make_pair(66, 0)});
	rules[34] = newRule(make_pair(65, 0), vector< pair <int, int> > {make_pair(7, 21), make_pair(32, 0), make_pair(67, 0)});
	rules[35] = newRule(make_pair(65, 0), vector< pair <int, int> > {make_pair(10, 22), make_pair(32, 0), make_pair(67, 0)});
	rules[36] = newRule(make_pair(65, 0), vector< pair <int, int> > {make_pair(8, 23), make_pair(32, 0), make_pair(67, 0)});
	rules[37] = newRule(make_pair(65, 0), vector< pair <int, int> > {make_pair(67, 0), make_pair(32, 0), make_pair(67, 0)});
	rules[38] = newRule(make_pair(65, 0), vector< pair <int, int> > {});
	rules[39] = newRule(make_pair(65, 24), vector< pair <int, int> > {make_pair(27, 0), make_pair(7, 25), make_pair(68, 0)});
	rules[40] = newRule(make_pair(68, 37), vector< pair <int, int> > {});
	rules[41] = newRule(make_pair(68, 0), vector< pair <int, int> > {make_pair(46, 34), make_pair(69, 0), make_pair(70, 0), make_pair(45, 35)});
	rules[42] = newRule(make_pair(70, 0), vector< pair <int, int> > {});
	rules[43] = newRule(make_pair(70, 0), vector< pair <int, int> > {make_pair(43, 36), make_pair(69, 0), make_pair(70, 0)});
	rules[44] = newRule(make_pair(69, 0), vector< pair <int, int> > {make_pair(5, 38)});
	rules[45] = newRule(make_pair(69, 0), vector< pair <int, int> > {make_pair(10, 39)});
	rules[46] = newRule(make_pair(69, 0), vector< pair <int, int> > {make_pair(6, 40)});
	rules[47] = newRule(make_pair(69, 0), vector< pair <int, int> > {make_pair(8, 41)});
	rules[48] = newRule(make_pair(69, 0), vector< pair <int, int> > {make_pair(7, 42)}); // old 26 (modify)
	rules[49] = newRule(make_pair(65, 0), vector< pair <int, int> > {make_pair(16, 0), make_pair(46, 0), make_pair(7, 33), make_pair(71, 0), make_pair(45, 0), make_pair(39, 0), make_pair(65, 0), make_pair(40, 0), make_pair(66, 0), make_pair(38, 0), make_pair(72, 0)});
	rules[50] = newRule(make_pair(72, 0), vector< pair <int, int> > {make_pair(21, 0), make_pair(39, 0), make_pair(65, 0), make_pair(40, 0), make_pair(66, 0), make_pair(38, 0)});
	rules[51] = newRule(make_pair(72, 0), vector< pair <int, int> > {});
	rules[52] = newRule(make_pair(65, 0), vector< pair <int, int> > {make_pair(1, 0), make_pair(46, 0), make_pair(7, 33), make_pair(71, 0), make_pair(45, 0), make_pair(39, 0), make_pair(65, 0), make_pair(40, 0), make_pair(66, 0), make_pair(38, 0)});
	rules[53] = newRule(make_pair(71, 0), vector< pair <int, int> > {make_pair(31, 0), make_pair(73, 0)});
	rules[54] = newRule(make_pair(71, 0), vector< pair <int, int> > {make_pair(48, 0), make_pair(73, 0)});
	rules[55] = newRule(make_pair(71, 0), vector< pair <int, int> > {make_pair(30, 0), make_pair(73, 0)});
	rules[56] = newRule(make_pair(71, 0), vector< pair <int, int> > {make_pair(29, 0), make_pair(73, 0)});
	rules[57] = newRule(make_pair(71, 0), vector< pair <int, int> > {make_pair(35, 0), make_pair(73, 0)});
	rules[58] = newRule(make_pair(71, 0), vector< pair <int, int> > {make_pair(33, 0), make_pair(73, 0)});
	rules[59] = newRule(make_pair(73, 0), vector< pair <int, int> > {make_pair(5, 28)});
	rules[60] = newRule(make_pair(73, 0), vector< pair <int, int> > {make_pair(6, 29)});
	rules[61] = newRule(make_pair(73, 0), vector< pair <int, int> > {make_pair(10, 31)});
	rules[62] = newRule(make_pair(73, 0), vector< pair <int, int> > {make_pair(8, 32)});
	rules[63] = newRule(make_pair(73, 0), vector< pair <int, int> > {make_pair(7, 30)}); // old 26 (modify)
	rules[64] = newRule(make_pair(65, 0), vector< pair <int, int> > {make_pair(18, 0), make_pair(46, 0), make_pair(7, 33), make_pair(32, 0), make_pair(73, 0), make_pair(40, 0), make_pair(7, 33), make_pair(71, 0), make_pair(40, 0), make_pair(74, 0), make_pair(45, 0), make_pair(39, 0), make_pair(65, 0), make_pair(40, 0), make_pair(66, 0), make_pair(38, 0)});
	rules[65] = newRule(make_pair(74, 0), vector< pair <int, int> > {make_pair(36, 0), make_pair(5, 0)});
	rules[66] = newRule(make_pair(74, 0), vector< pair <int, int> > {make_pair(49, 0), make_pair(5, 0)});
	rules[67] = newRule(make_pair(65, 0), vector< pair <int, int> > {make_pair(23, 0), make_pair(39, 0), make_pair(65, 0), make_pair(40, 0), make_pair(66, 0), make_pair(38, 0), make_pair(1, 0), make_pair(46, 0), make_pair(7, 33), make_pair(71, 0), make_pair(45, 0)});
	rules[68] = newRule(make_pair(65, 0), vector< pair <int, int> > {make_pair(25, 0), make_pair(28, 0), make_pair(7, 26)});
	rules[69] = newRule(make_pair(65, 0), vector< pair <int, int> > {make_pair(24, 0), make_pair(34, 0), make_pair(12, 0), make_pair(75, 0)});
	rules[70] = newRule(make_pair(75, 0), vector< pair <int, int> > {});
	rules[71] = newRule(make_pair(83, 0), vector< pair <int, int> > {make_pair(7, 26), make_pair(76, 0), make_pair(75, 0)}); // modify
	rules[72] = newRule(make_pair(83, 0), vector< pair <int, int> > {make_pair(12, 0), make_pair(75, 0)}); // modify
	rules[73] = newRule(make_pair(76, 0), vector< pair <int, int> > {});
	rules[74] = newRule(make_pair(76, 0), vector< pair <int, int> > {make_pair(43, 0), make_pair(7, 26), make_pair(76, 0)});
	rules[75] = newRule(make_pair(67, 0), vector< pair <int, int> > {make_pair(79, 0), make_pair(80, 0)});
	rules[76] = newRule(make_pair(67, 0), vector< pair <int, int> > {make_pair(27, 0), make_pair(7, 27), make_pair(68, 0)});
	rules[77] = newRule(make_pair(80, 0), vector< pair <int, int> > {make_pair(37, 0), make_pair(79, 0), make_pair(80, 0)});
	rules[78] = newRule(make_pair(80, 0), vector< pair <int, int> > {make_pair(50, 0), make_pair(79, 0), make_pair(80, 0)});
	rules[79] = newRule(make_pair(80, 0), vector< pair <int, int> > {});
	rules[80] = newRule(make_pair(79, 0), vector< pair <int, int> > {make_pair(81, 0), make_pair(82, 0)});
	rules[81] = newRule(make_pair(82, 0), vector< pair <int, int> > {});
	rules[82] = newRule(make_pair(82, 0), vector< pair <int, int> > {make_pair(44, 0), make_pair(81, 0), make_pair(82, 0)});
	rules[83] = newRule(make_pair(82, 0), vector< pair <int, int> > {make_pair(42, 0), make_pair(81, 0), make_pair(82, 0)});
	rules[84] = newRule(make_pair(81, 0), vector< pair <int, int> > {make_pair(5, 28)});
	rules[85] = newRule(make_pair(81, 0), vector< pair <int, int> > {make_pair(6, 29)});
	rules[86] = newRule(make_pair(81, 0), vector< pair <int, int> > {make_pair(7, 30)});
	rules[87] = newRule(make_pair(81, 0), vector< pair <int, int> > {make_pair(10, 31)});
	rules[88] = newRule(make_pair(81, 0), vector< pair <int, int> > {make_pair(8, 32)});
	rules[89] = newRule(make_pair(81, 0), vector< pair <int, int> > {make_pair(46, 0), make_pair(67, 0), make_pair(45, 0)});
	rules[90] = newRule(make_pair(75, 0), vector< pair <int, int> > {make_pair(34, 0), make_pair(83, 0)}); // append
	return rules;
}

rule newRule (pair<int, int> header, vector < pair <int, int> > body) {
	rule newR;
	newR.header = header;
	newR.body = body;
	return newR;
}

void printToken(vector <token> entry, int ptrEntry, vector < pair< int, int > > execStack) {
	int i;
	cout << "\n == Token Processado == " << endl;
	cout << "  ID: " << entry[ptrEntry].id << endl;
	cout << "  Token: " << entry[ptrEntry].content << endl;
	cout << "  Linha: " << entry[ptrEntry].line << endl;
	cout << "  Pilha: {$";
	for (i = 0; i < execStack.size(); i++)
		cout << ", " << execStack[i].first;
	cout << "}" << endl;
}

void printStack(vector < pair< int, int > > execStack) {
	int i;
	cout << "\n == Acao-Regra == " << endl;
	cout << "  Pilha: {$";
	for (i = 0; i < execStack.size(); i++)
		cout << ", " << execStack[i].first;
	cout << "}" << endl;	
}