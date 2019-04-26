#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <iterator>

using namespace std;

void exampleDict ();

int main(int argc, char *argv[]) {
	

    return 0;
}

void exampleDict () {
    // To create a dict for string to int
    map <string, int> dict;
    // To insert/update in dict directly
    dict["ha"] = 1;
    dict["he"] = 2;
    dict["hi"] = 3;
    // To query the dict size
    cout << dict.size() << endl;
    // To query in dict directly
    cout << dict["ha"] << endl;
    // To search in dict indirectly
    map <string, int>::iterator it = dict.begin();
    while(it != dict.end()){
        cout << "<" << it->first << ", " << it->second << ">" << endl; 
        it++;
    }
}