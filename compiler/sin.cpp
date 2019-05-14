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
	//cout << parseTable[make_pair(1, 2)] << endl;
	map <int, pair<int, vector<int>> > rules = createRules();
	cout << rules[1].second[3] << endl;
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
	parseTable[make_pair(52,47)] = 3;
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
	parseTable[make_pair(57,47)] = 10;
	parseTable[make_pair(59,7)] = 12;
	parseTable[make_pair(60,2)] = 15;
	parseTable[make_pair(60,3)] = 18;
	parseTable[make_pair(60,13)] = 14;
	parseTable[make_pair(60,19)] = 17;
	parseTable[make_pair(60,26)] = 16;
	parseTable[make_pair(61,39)] = 26;
	parseTable[make_pair(61,46)] = 27;
	parseTable[make_pair(62,3)] = 24;
	parseTable[make_pair(62,5)] = 20;
	parseTable[make_pair(62,6)] = 21;
	parseTable[make_pair(62,8)] = 23;
	parseTable[make_pair(62,9)] = 22;
	parseTable[make_pair(62,45)] = 25;
	parseTable[make_pair(63,3)] = 28;
	parseTable[make_pair(63,13)] = 28;
	parseTable[make_pair(63,19)] = 28;
	parseTable[make_pair(63,26)] = 28;
	parseTable[make_pair(64,40)] = 29;
	parseTable[make_pair(64,45)] = 30;
	parseTable[make_pair(65,1)] = 52;
	parseTable[make_pair(65,5)] = 37;
	parseTable[make_pair(65,6)] = 37;
	parseTable[make_pair(65,7)] = 37;
	parseTable[make_pair(65,8)] = 37;
	parseTable[make_pair(65,10)] = 37;
	parseTable[make_pair(65,16)] = 49;
	parseTable[make_pair(65,18)] = 64;
	parseTable[make_pair(65,23)] = 67;
	parseTable[make_pair(65,24)] = 69;
	parseTable[make_pair(65,25)] = 68;
	parseTable[make_pair(65,27)] = 39;
	parseTable[make_pair(65,40)] = 38;
	parseTable[make_pair(65,46)] = 37;
	parseTable[make_pair(66,20)] = 33;
	parseTable[make_pair(66,38)] = 33;
	parseTable[make_pair(67,5)] = 75;
	parseTable[make_pair(67,6)] = 75;
	parseTable[make_pair(67,7)] = 75;
	parseTable[make_pair(67,8)] = 75;
	parseTable[make_pair(67,10)] = 75;
	parseTable[make_pair(67,27)] = 76;
	parseTable[make_pair(67,46)] = 75;
	parseTable[make_pair(68,32)] = 40;
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
	parseTable[make_pair(71,34)] = 57;
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
	parseTable[make_pair(75,34)] = 72;
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
	parseTable[make_pair(80,32)] = 79;
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
	parseTable[make_pair(82,32)] = 81;
	parseTable[make_pair(82,37)] = 81;
	parseTable[make_pair(82,40)] = 81;
	parseTable[make_pair(82,42)] = 83;
	parseTable[make_pair(82,44)] = 82;
	parseTable[make_pair(82,45)] = 81;
	parseTable[make_pair(82,50)] = 81;
	return parseTable;
}

map < int, pair<int, vector<int>> > createRules() {
	map <int, pair<int, vector<int>> > rules;
	rules[1] = make_pair(41, vector<int> {2, 11, 39, 52, 53, 54, 38});
	rules[2] = make_pair(52, vector<int> {7, 55, 41, 56, 40, 57});
	rules[3] = make_pair(52, vector<int> {});
	rules[4] = make_pair(52, vector<int> {});
	rules[5] = make_pair(52, vector<int> {});
	rules[6] = make_pair(52, vector<int> {});
	rules[7] = make_pair(52, vector<int> {});
	rules[8] = make_pair(52, vector<int> {});
	rules[9] = make_pair(52, vector<int> {});
	rules[10] = make_pair(52, vector<int> {});
	rules[11] = make_pair(52, vector<int> {});
	rules[12] = make_pair(52, vector<int> {});
	rules[13] = make_pair(52, vector<int> {});
	rules[14] = make_pair(52, vector<int> {});
	rules[15] = make_pair(52, vector<int> {});
	rules[16] = make_pair(52, vector<int> {});
	rules[17] = make_pair(52, vector<int> {});
	rules[18] = make_pair(52, vector<int> {});
	rules[19] = make_pair(52, vector<int> {});
	rules[20] = make_pair(52, vector<int> {});
	rules[21] = make_pair(52, vector<int> {});
	rules[22] = make_pair(52, vector<int> {});
	rules[23] = make_pair(52, vector<int> {});
	rules[24] = make_pair(52, vector<int> {});
	rules[25] = make_pair(52, vector<int> {});
	rules[26] = make_pair(52, vector<int> {});
	rules[27] = make_pair(52, vector<int> {});
	rules[28] = make_pair(52, vector<int> {});
	rules[29] = make_pair(52, vector<int> {});
	rules[30] = make_pair(52, vector<int> {});
	rules[31] = make_pair(52, vector<int> {});
	rules[32] = make_pair(52, vector<int> {});
	rules[33] = make_pair(52, vector<int> {});
	rules[34] = make_pair(52, vector<int> {});
	rules[35] = make_pair(52, vector<int> {});
	rules[36] = make_pair(52, vector<int> {});
	rules[37] = make_pair(52, vector<int> {});
	rules[38] = make_pair(52, vector<int> {});
	rules[39] = make_pair(52, vector<int> {});
	rules[40] = make_pair(52, vector<int> {});
	rules[41] = make_pair(52, vector<int> {});
	rules[42] = make_pair(52, vector<int> {});
	rules[43] = make_pair(52, vector<int> {});
	rules[44] = make_pair(52, vector<int> {});
	rules[45] = make_pair(52, vector<int> {});
	rules[46] = make_pair(52, vector<int> {});
	rules[47] = make_pair(52, vector<int> {});
	rules[48] = make_pair(52, vector<int> {});
	rules[49] = make_pair(52, vector<int> {});
	rules[50] = make_pair(52, vector<int> {});
	rules[51] = make_pair(52, vector<int> {});
	rules[52] = make_pair(52, vector<int> {});
	rules[53] = make_pair(52, vector<int> {});
	rules[54] = make_pair(52, vector<int> {});
	rules[55] = make_pair(52, vector<int> {});
	rules[56] = make_pair(52, vector<int> {});
	rules[57] = make_pair(52, vector<int> {});
	rules[58] = make_pair(52, vector<int> {});
	rules[59] = make_pair(52, vector<int> {});
	rules[60] = make_pair(52, vector<int> {});
	rules[61] = make_pair(52, vector<int> {});
	rules[62] = make_pair(52, vector<int> {});
	rules[63] = make_pair(52, vector<int> {});
	rules[64] = make_pair(52, vector<int> {});
	rules[65] = make_pair(52, vector<int> {});
	rules[66] = make_pair(52, vector<int> {});
	rules[67] = make_pair(52, vector<int> {});
	rules[68] = make_pair(52, vector<int> {});
	rules[69] = make_pair(52, vector<int> {});
	rules[70] = make_pair(52, vector<int> {});
	rules[71] = make_pair(52, vector<int> {});
	rules[72] = make_pair(52, vector<int> {});
	rules[73] = make_pair(52, vector<int> {});
	rules[74] = make_pair(52, vector<int> {});
	rules[75] = make_pair(52, vector<int> {});
	rules[76] = make_pair(52, vector<int> {});
	rules[77] = make_pair(52, vector<int> {});
	rules[78] = make_pair(52, vector<int> {});
	rules[79] = make_pair(52, vector<int> {});
	rules[80] = make_pair(52, vector<int> {});
	rules[81] = make_pair(52, vector<int> {});
	rules[82] = make_pair(52, vector<int> {});
	rules[83] = make_pair(52, vector<int> {});
	rules[84] = make_pair(52, vector<int> {});
	rules[85] = make_pair(52, vector<int> {});
	rules[86] = make_pair(52, vector<int> {});
	rules[87] = make_pair(52, vector<int> {});
	rules[88] = make_pair(52, vector<int> {});
	rules[89] = make_pair(52, vector<int> {});
	return rules;
}