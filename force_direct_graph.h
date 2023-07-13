#pragma once

#include "force_direct_node.h"
#include "graph.h"
#include "draw_graph.h"

#include <math.h>
#include <random>

/**
* Object class handling graph structure visualization physics and file creation.
*/
class FDGraph {
public:
	FDGraph(size_t width, size_t height, Graph graph);
	void applyForce();
	void draw(int index, DrawGraph draw);
	void makeAnimation(string filename);

private:
	const float gravity_ = 1;
	const float coulomb_ = 3000;
	const float hook_ = 0.5;
	const float threshold_ = 1;
	const int frames_ = 100;
	const float speed_ = 1;

	const float max_size_ = 500;
	const float min_size_ = 100;
	const float max_length_ = 300;
	const float min_length_ = 100;

	size_t width_;
	size_t height_;
	vector<FDNode> nodes_;
	Graph graph_;
	vector<Graph::Edge> edges_;

	bool exists(const string& path);
};