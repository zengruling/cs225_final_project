#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

/**
* Object class representing the central graph data structure.
* Additionally contains BFS algorithm implementation.
*/
class Graph {
public:
	/**
	* struct representing a graph vertex.
	*/
	struct Vertex {
		int id_;
		string name_;
		size_t size_;

		Vertex(int id, string name, size_t size)
			: id_(id), name_(name), size_(size)
		{
		}
	};

	/**
	* struct represeting a graph edge.
	*/
	struct Edge {
		float weight_;
		pair<int, int> endpoints_;

		Edge(int from, int to, float weight)
			: weight_(weight), endpoints_(from, to)
		{
		}
	};

	Graph();

	void addVertex(int id, string name, size_t size);
	void addEdge(int point1, int point2, float weight);

	
	size_t getSize();
	vector<Vertex> getAdjacentVertices(int vertex);
	vector<Edge> getAdjacentEdges(int vertex);
	vector<Vertex> getAllVertices();
	vector<Edge> getAllEdges();

	std::vector<std::vector<int>> BFS(int vertex);
	void relevance(int vertex);
	Vertex IDXtoVertex(int IDX);
	Vertex IDtoVertex(int ID);
private:
	vector<Vertex> vertices_;
	vector<vector<float>> weights_;
};