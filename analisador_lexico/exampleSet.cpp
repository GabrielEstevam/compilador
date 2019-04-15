#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <set>
#include <iterator>

using namespace std;

void exampleSet ();

int main(int argc, char *argv[]) {
	

    return 0;
}

void exampleSet () {
    // To create a set for strings
    set <string> conj;
    // To insert in set
    conj.insert("ha");
    conj.insert("he");
    conj.insert("hi");
    // To search in set indirectly
    set <string>::iterator it = conj.begin();
    while(it != conj.end()){
        cout << *it << endl; 
        it++;
    }
    // To search in set directly
    bool is_in = conj.find("ho") != conj.end();
    cout << is_in << endl;
}