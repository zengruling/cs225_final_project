#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../read_data.h"
#include "../draw_graph.h"
#include "../force_direct_graph.h"
#include "../Dijkstra.h"
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <string>
#include <utility>
#include <map>
using namespace std;

////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("test_graph"){
    Graph graph;
    graph.addVertex(0, "zero", 1);
    graph.addVertex(1, "one", 1);
    graph.addVertex(2, "two", 2);
    graph.addVertex(3, "three", 3);
    graph.addVertex(4, "four", 4);
    graph.addVertex(5, "five", 5);
    graph.addVertex(6, "six", 6);
    graph.addVertex(7, "seven", 7);
    graph.addEdge(0, 1, 0.5);
    graph.addEdge(0, 3, 0.5);
    graph.addEdge(0, 4, 0.5);
    graph.addEdge(1, 2, 0.5);
    graph.addEdge(2, 4, 0.5);
    graph.addEdge(2, 5, 0.5);
    graph.addEdge(3, 7, 0.5);
    graph.addEdge(4, 7, 0.5);
    graph.addEdge(5, 6, 0.5);
    graph.addEdge(6, 7, 0.5);

    REQUIRE(graph.getSize() == 8);
    REQUIRE(graph.getAdjacentVertices(2).size() == 3);
    REQUIRE(graph.getAdjacentEdges(2).size() == 3);
    REQUIRE(graph.getAllEdges().size() == 10);
}

TEST_CASE("test_read") {
    DataReader reader("tests/genres.txt", "tests/small.tsv");
    Graph graph = reader.getGraph();

    REQUIRE(graph.getAdjacentVertices(11).size() == 1);
    REQUIRE(graph.getAdjacentEdges(11).size() == 1);
    REQUIRE(graph.getAllEdges().size() == 7);
}

TEST_CASE("test_graph_2"){
    Graph graph;
    graph.addVertex(0, "zero", 1);
    graph.addVertex(1, "one", 1);
    graph.addVertex(2, "two", 2);
    graph.addVertex(3, "three", 3);
    graph.addVertex(4, "four", 4);
    graph.addVertex(5, "five", 5);
    graph.addVertex(6, "six", 6);
    graph.addVertex(7, "seven", 7);
    graph.addEdge(0, 1, 0.5);
    graph.addEdge(0, 2, 0.5);
    graph.addEdge(0, 3, 0.5);
    graph.addEdge(1, 3, 0.5);
    graph.addEdge(1, 5, 0.5);
    graph.addEdge(3, 7, 0.5);
    graph.addEdge(4, 6, 0.5);

    REQUIRE(graph.getSize() == 8);
    REQUIRE(graph.getAdjacentVertices(1).size() == 3);
    REQUIRE(graph.getAdjacentEdges(1).size() == 3);
    REQUIRE(graph.getAdjacentVertices(3).size() == 3);
    REQUIRE(graph.getAdjacentEdges(3).size() == 3);
    REQUIRE(graph.getAllEdges().size() == 7);
}

TEST_CASE("BFS_simple"){
    Graph graph;
    graph.addVertex(0, "zero", 1);
    graph.addVertex(1, "one", 1);
    graph.addVertex(2, "two", 2);
    graph.addVertex(3, "three", 3);
    graph.addVertex(4, "four", 4);
    graph.addVertex(5, "five", 5);
    graph.addVertex(6, "six", 6);
    graph.addVertex(7, "seven", 7);
    graph.addEdge(0, 3, 0.5);
    graph.addEdge(1, 2, 0.5);
    graph.addEdge(1, 5, 0.5);
    graph.addEdge(1, 6, 0.5);
    graph.addEdge(2, 4, 0.5);
    graph.addEdge(3, 5, 0.5);
    graph.addEdge(3, 7, 0.5);
    graph.addEdge(4, 7, 0.5);

    REQUIRE(graph.getSize() == 8);
    REQUIRE(graph.getAdjacentVertices(1).size() == 3);
    REQUIRE(graph.getAdjacentEdges(1).size() == 3);
    REQUIRE(graph.getAdjacentVertices(3).size() == 3);
    REQUIRE(graph.getAdjacentEdges(3).size() == 3);
    REQUIRE(graph.getAllEdges().size() == 8);

    REQUIRE(graph.BFS(1)[0][0] == 1);
}

TEST_CASE("BFS_revelance"){
    Graph graph;
    graph.addVertex(0, "zero", 1);
    graph.addVertex(1, "one", 1);
    graph.addVertex(2, "two", 2);
    graph.addVertex(3, "three", 3);
    graph.addVertex(4, "four", 4);
    graph.addVertex(5, "five", 5);
    graph.addVertex(6, "six", 6);
    graph.addVertex(7, "seven", 7);
    graph.addEdge(1, 2, 17);
    graph.addEdge(1, 5, 5);
    graph.addEdge(1, 6, 50);
    graph.addEdge(2, 4, 21);
    graph.addEdge(2, 5, 42);
    graph.addEdge(3, 5, 3);
    graph.addEdge(4, 7, 8);
    graph.addEdge(5, 6, 63);
    graph.addEdge(5, 7, 79);

    REQUIRE(graph.getSize() == 8);
    REQUIRE(graph.getAdjacentVertices(1).size() == 3);
    REQUIRE(graph.getAdjacentEdges(1).size() == 3);
    REQUIRE(graph.getAdjacentVertices(2).size() == 3);
    REQUIRE(graph.getAdjacentEdges(2).size() == 3);
    REQUIRE(graph.getAllEdges().size() == 9);

    REQUIRE(graph.BFS(1)[0][0] == 1);
    REQUIRE(graph.BFS(1)[1][0] == 2);
    REQUIRE(graph.BFS(1)[1][2] == 6);
    REQUIRE(graph.BFS(1)[2][0] == 4);
}

TEST_CASE("BFS_small"){
    DataReader reader("tests/genres.txt", "tests/small.tsv");
    Graph graph = reader.getGraph();
    std::vector<std::vector<int>> vec = graph.BFS(19);
    REQUIRE(vec[1].size() == 2);
}

TEST_CASE("BFS_small_2"){
    DataReader reader("tests/genres.txt", "tests/small.tsv");
    Graph graph = reader.getGraph();
    std::vector<std::vector<int>> vec = graph.BFS(25);
    REQUIRE(vec[1].size() == 2);
    
}

TEST_CASE("BFS_whole"){
    DataReader reader("tests/genres.txt", "data/train.tsv");
    Graph graph = reader.getGraph();
    std::vector<std::vector<int>> vec = graph.BFS(25);
    graph.relevance(25);
}

TEST_CASE("BFS_edge"){
    DataReader reader("tests/genres.txt", "data/train.tsv");
    Graph graph = reader.getGraph();
    std::vector<std::vector<int>> vec = graph.BFS(-1);
    std::vector<std::vector<int>> vec2 = graph.BFS(40);
    REQUIRE(vec.size() == 0);
    REQUIRE(vec2.size() == 0);
}

TEST_CASE("test_draw") {
    PNG graph(300, 200);
    HSLAPixel red(0, 1, 0.5, 1);
    HSLAPixel blue(240, 1, 0.5, 1);
    DrawGraph draw(15, 18, 12, 16, "data/font_courier_new_12.png", red, blue);
    draw.drawText(&graph, 150, 100, "Test1ng");
    draw.drawEdge(&graph, 50, 50, 250, 175);
    draw.drawVertex(&graph, 50, 50, 50);
    draw.drawEdge(&graph, 50, 50, 50, 175);
    draw.drawVertex(&graph, 150, 100, 40.0);
    graph.writeToFile("test_draw.png");
}

TEST_CASE("test_force_direct") {
    Graph graph;
    graph.addVertex(0, "zero", 1);
    graph.addVertex(1, "one", 3);
    graph.addVertex(2, "two", 4);
    graph.addVertex(3, "three", 5);
    graph.addVertex(4, "four", 2);
    graph.addVertex(5, "five", 5);
    graph.addVertex(6, "six", 3);
    graph.addVertex(7, "seven", 1);
    graph.addEdge(0, 1, 1.5);
    graph.addEdge(0, 3, 0.5);
    graph.addEdge(0, 4, 1.0);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 4, 2.5);
    graph.addEdge(2, 5, 2);
    graph.addEdge(3, 7, 1);
    graph.addEdge(4, 7, 3);
    graph.addEdge(5, 6, 2.8);
    graph.addEdge(6, 7, 1.7);

    FDGraph force_graph(600, 600, graph);
    force_graph.makeAnimation("test.gif");
}

TEST_CASE("test_Dijkstra_easy"){
    Graph graph;
    graph.addVertex(0, "zero", 0);
    graph.addVertex(1, "one", 1);
    graph.addVertex(2, "two", 2);
    graph.addVertex(3, "three", 3);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 10);
    graph.addEdge(2, 3, 1);
    graph.addEdge(0, 1, 1);
    Graph::Vertex begin(0, "zero", 0);
    Graph::Vertex end(2, "two", 2);
    Dijkstra d(graph,begin,end);
    //auto e = graph.getAdjacentEdges(1);
    //for (auto it = e.begin(); it != e.end(); ++it){
    //    std::cout<<"from : "<<it->endpoints_.first<<" to : "<<it->endpoints_.second<<" has distance: "<<it->weight_<<std::endl;
    //}
    //d.process();
    //d.process();
    d.process();
    //d.getDist();
}

TEST_CASE("test_Dijkstra_database"){
    DataReader reader("tests/genres.txt", "data/train.tsv");
    Graph graph = reader.getGraph();
    auto e = graph.getAllEdges();
    //for (auto it = e.begin(); it != e.end(); ++it){
    //   std::cout<<"from : "<<it->endpoints_.first<<" to : "<<it->endpoints_.second<<" has distance: "<<it->weight_<<std::endl;
    //}

    Graph::Vertex begin(0, "zero", 0);
    Graph::Vertex end(15, "two", 20);
    Dijkstra d(graph,begin,end);
    d.process();
    d.getDist();
}
