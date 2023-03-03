/*
 * TODO: complete this file comment.
 */
#include <iostream>
#include "SimpleGraph.h"
#include <fstream>

using namespace std;

void Welcome();
void openFile(ifstream& file);

// Main method
int main() {
    Welcome();
    /* TODO: your implementation here */
    ifstream file;
    openFile(file);
    int a;
    file >> a;
    cout << a << endl;
    return 0;
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;
}

void openFile(ifstream& file) {
    string fileName;
    while (true) {
        if (!getline(cin, fileName)) {
            cout << "can't read the file name, please check!" << endl;
        }
        file.open(fileName);
        if (file.is_open()) {
            return;
        } else {
            cout << "can't open the file, please check!" << endl;
            file.clear(); // clear the bad bit status for fstream
        }
    }

}


