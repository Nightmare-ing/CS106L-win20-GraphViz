/*
 * TODO: complete this file comment.
 */
#include <iostream>
#include "SimpleGraph.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono> // fancy timers

using namespace std;

void Welcome();
void openFile(ifstream &file);
int getInteger();
int getRunTime();
void initGraph(SimpleGraph &graph);
void circleNode(SimpleGraph &graph, ifstream &file);
void addEdges(SimpleGraph &graph, ifstream &file);
void updatePosi(SimpleGraph &graph);
void computeAttrDeltaPosi(SimpleGraph &graph, vector<pair<double, double>> &deltaPosiList);
void computeRepuDeltaPosi(SimpleGraph &graph, vector<pair<double, double>> &deltaPosiList);


// Main method
int main() {
    Welcome();
    /* TODO: your implementation here */
    string userInput = "yes";

    while (userInput == "yes") {
        SimpleGraph graph;
        InitGraphVisualizer(graph);

        initGraph(graph);
        int runTime = getRunTime();

        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        int milliseconds = elapsedTime.count();

        while (milliseconds < runTime) {
            updatePosi(graph);
            DrawGraph(graph);
            endTime = std::chrono::high_resolution_clock::now();
            elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
            milliseconds = elapsedTime.count();
        }

        cout << "Do you want to try another file?" << endl;
        getline(cin, userInput);
    }

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

void openFile(ifstream &file) {
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

void initGraph(SimpleGraph &graph) {
    ifstream file;
    openFile(file);
    circleNode(graph, file);
    addEdges(graph, file);
}

void circleNode(SimpleGraph &graph, ifstream &file) {
    const double KPI = 3.14159265358979323;

    int nodeNum;
    file >> nodeNum;

    for (int i = 0; i < nodeNum; ++i) {
        double positionX = cos(2 * KPI * i / nodeNum);
        double positionY = sin(2 * KPI * i / nodeNum);
        Node node;
        node.x = positionX;
        node.y = positionY;
        graph.nodes.push_back(node);
    }
}

void addEdges(SimpleGraph &graph, ifstream &file) {
    size_t nodeIndex1, nodeIndex2;
    while (file >> nodeIndex1 >> nodeIndex2) {
        Edge edge;
        edge.start = nodeIndex1;
        edge.end = nodeIndex2;
        graph.edges.push_back(edge);
    }
}

void updatePosi(SimpleGraph &graph) {
    int nodesNum = graph.nodes.size();
    auto nodesAttrDeltaPosi = vector(nodesNum, make_pair(0.0, 0.0));
    auto nodesRepulDeltaPosi = vector(nodesNum, make_pair(0.0, 0.0));
    computeAttrDeltaPosi(graph, nodesAttrDeltaPosi);
    computeRepuDeltaPosi(graph, nodesRepulDeltaPosi);

    for (int i = 0; i < nodesNum; ++i) {
        auto [attrPosiX, attrPosiY] = nodesAttrDeltaPosi[i];
        auto [repelPosiX, repelPosiY] = nodesRepulDeltaPosi[i];
        graph.nodes[i].x += attrPosiX + repelPosiX;
        graph.nodes[i].y += attrPosiY + repelPosiY;
    }
}

void computeAttrDeltaPosi(SimpleGraph &graph, vector<pair<double, double>> &deltaPosiList) {
    const double KATTRACT = 0.001;
    for (auto edge : graph.edges) {
        const auto &firstNode = graph.nodes[edge.start];
        const auto &secNode = graph.nodes[edge.end];
        double attractF = KATTRACT * (pow(secNode.y - firstNode.y, 2)
                                      + pow(firstNode.x - secNode.x, 2) );
        double theta = atan2(secNode.y - firstNode.y, secNode.x - firstNode.x);

        double delta_x0 = attractF * cos(theta);
        double delta_y0 = attractF * sin(theta);
        double delta_x1 = -attractF * cos(theta);
        double delta_y1 = -attractF * sin(theta);

        deltaPosiList[edge.start].first += delta_x0;
        deltaPosiList[edge.start].second += delta_y0;
        deltaPosiList[edge.end].first += delta_x1;
        deltaPosiList[edge.end].second += delta_y1;

    }
}

void computeRepuDeltaPosi(SimpleGraph &graph, vector<pair<double, double>> &deltaPosiList) {
    const double KREPEL = 0.001;
    int nodesNum = graph.nodes.size();
    for (int i = 0; i < nodesNum; ++i) {
        for (int j = i+1; j < nodesNum; ++j) {
            auto &firstNode = graph.nodes[i];
            auto &secNode = graph.nodes[j];
            double repelF = KREPEL / sqrt(pow(secNode.y - firstNode.y, 2)
                                          + pow(secNode.x - firstNode.x, 2));
            double theta = atan2(secNode.y - firstNode.y, secNode.x - firstNode.x);

            double delta_x0 = -repelF * cos(theta);
            double delta_y0 = -repelF * sin(theta);
            double delta_x1 = repelF * cos(theta);
            double delta_y1 = repelF * sin(theta);

            deltaPosiList[i].first += delta_x0;
            deltaPosiList[i].second += delta_y0;
            deltaPosiList[j].first += delta_x1;
            deltaPosiList[j].second += delta_y1;
        }
    }
}
