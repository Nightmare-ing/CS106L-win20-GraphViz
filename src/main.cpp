/*
 * TODO: complete this file comment.
 */
#include <iostream>
#include "SimpleGraph.h"
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

void Welcome();
void openFile(ifstream& file);
int getInteger();
int getRunTime();
void initiGraph(SimpleGraph& graph);
void circleNode(SimpleGraph &graph, ifstream &file);

// Main method
int main() {
    Welcome();
    /* TODO: your implementation here */
//    ifstream file;
//    openFile(file);
    int runTime = getRunTime();
//    ifstream file("10grid");
//    SimpleGraph graph;
//    circleNode(graph, file);
//    DrawGraph(graph);
    cout << runTime << endl;
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
    cout << "Please enter your file name: ";
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

int getRunTime() {
    cout << "How long do you want to run the program in microseconds?" << endl;
    return getInteger();
}

int getInteger() {
    string input;
    int num;
    char rest;

    while (true) {
        if (!getline(cin, input)) {
            cout << "can't read your input, please check!" << endl;
        }
        istringstream converter(input);
        if (converter >> num && !(converter >> rest)) {
            return num;
        } else {
            cout << "Invalid input!" << endl;
        }
        cout << "Retry: ";
    }
}

void initiGraph(SimpleGraph& graph) {


}

void circleNode(SimpleGraph& graph, ifstream& file) {
    const double kPi = 3.14159265358979323;

    int nodeNum;
    file >> nodeNum;

    for (int i = 0; i < nodeNum; ++i) {
        double positionX = cos(2 * kPi * i / nodeNum);
        double positionY = sin(2 * kPi * i / nodeNum);
        Node node;
        node.x = positionX;
        node.y = positionY;
        graph.nodes.push_back(node);
    }
}
