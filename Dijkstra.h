#include "graph.h"
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <string>
#include <utility>
#include <map>

class Dijkstra{

    public:
    Dijkstra(Graph graph, Graph::Vertex start, Graph::Vertex end);  
    void process();
    std::map<int,float> getDist();
    void printPri();

    private:
    std::map<int,float> distance;
    std::map<int,bool> visited;
    vector<Graph::Vertex> priority;
    Graph::Vertex end_;
    Graph::Vertex start_;
    unsigned findShortest(vector<Graph::Vertex> curr);
    Graph graph;
};