#include "force_direct_graph.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string>


FDGraph::FDGraph(size_t width, size_t height, Graph graph) : width_(width), height_(height), graph_(graph) {
	vector<Graph::Vertex> vertices = graph.getAllVertices();

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist_x(0, width - 1);
	std::uniform_int_distribution<std::mt19937::result_type> dist_y(0, height - 1);

	float min_size = -1;
	float max_size = -1;
	for (Graph::Vertex current : vertices) {
		if (min_size < 0) {
			min_size = current.size_;
		}
		else {
			min_size = min(min_size, (float) current.size_);
		}
		max_size = max(max_size, (float) current.size_);
	}

	for (Graph::Vertex current : vertices) {
		FDNode node(current.name_, dist_x(rng), dist_y(rng), 0, 0, min_size_ + (current.size_ - min_size) * (max_size_ - min_size_) / (max_size - min_size));
		nodes_.push_back(node);
	}

	float min_length = -1;
	float max_length = -1;
	for (Graph::Edge current : graph_.getAllEdges()) {
		if (min_length < 0) {
			min_length = current.weight_;
		}
		else {
			min_length = min(min_length, current.weight_);
		}
		max_length = max(max_length, current.weight_);
	}

	for (Graph::Edge current : graph_.getAllEdges()) {
		Graph::Edge edge(current.endpoints_.first, current.endpoints_.second, min_length_ + (current.weight_ - min_length) * (max_length_ - min_length_) / (max_length - min_length));
		edges_.push_back(edge);
	}
}

void FDGraph::applyForce() {
	for (FDNode& node : nodes_) {
		float force_x = -1 * gravity_ * (node.getPos().first - ((int) width_ / 2));
		float force_y = -1 * gravity_ * (node.getPos().second - ((int) height_ / 2));
		node.setForce(force_x, force_y);
	}

	for (size_t i = 0; i < nodes_.size() - 1; i++) {
		for (size_t j = i + 1; j < nodes_.size(); j++) {
			int diff_x = nodes_[j].getPos().first - nodes_[i].getPos().first;
			int diff_y = nodes_[j].getPos().second - nodes_[i].getPos().second;
			float force_x = coulomb_ * diff_x / (diff_x * diff_x + diff_y * diff_y);
			float force_y = coulomb_ * diff_y / (diff_x * diff_x + diff_y * diff_y);
			nodes_[j].addForce(force_x, force_y);
			nodes_[i].addForce(-1 * force_x, -1 * force_y);
		}
	}

	for (Graph::Edge edge : edges_) {
		int index1 = edge.endpoints_.first;
		int index2 = edge.endpoints_.second;
		FDNode node1 = nodes_[index1];
		FDNode node2 = nodes_[index2];
		int diff_x = node2.getPos().first - node1.getPos().first;
		int diff_y = node2.getPos().second - node1.getPos().second;
		float dist = sqrt(diff_x * diff_x + diff_y * diff_y);
		float displace = dist - edge.weight_;
		float force_x = hook_ * diff_x * displace / dist;
		float force_y = hook_ * diff_y * displace / dist;
		node2.addForce(-1 * force_x, -1 * force_y);
		node1.addForce(force_x, force_y);
	}
}

void FDGraph::draw(int index, DrawGraph drawer) {
	PNG img(width_, height_);
	for (FDNode node : nodes_) {
		drawer.drawText(&img, node.getPos().first, node.getPos().second, node.getName());
		drawer.drawVertex(&img, node.getPos().first, node.getPos().second, sqrt(node.getSize()));
	}
	for (Graph::Edge edge : edges_) {
		int index1 = edge.endpoints_.first;
		int index2 = edge.endpoints_.second;
		FDNode node1 = nodes_[index1];
		FDNode node2 = nodes_[index2];
		drawer.drawEdge(&img, node1.getPos().first, node1.getPos().second, node2.getPos().first, node2.getPos().second);
	}
	img.writeToFile("frames/graph" + std::to_string(index) + ".png");
}

void FDGraph::makeAnimation(string filename) {
	float current = 5;
	int count = 0;
	if (!exists("frames/")) {
		mkdir("frames", 0700);
	}
	system("rm -f frames/*.png");
	HSLAPixel red(0, 1, 0.5, 1);
	HSLAPixel blue(240, 1, 0.5, 1);
	DrawGraph drawer(15, 18, 12, 16, "data/font_courier_new_12.png", red, blue);
	while (current > threshold_ && count < frames_) {
		applyForce();
		current = 0;
		for (FDNode& node : nodes_) {
			current += node.updatePos(speed_);
		}
		draw(count, drawer);
		count++;
		current /= nodes_.size();
	}
	system(("convert frames/graph*.png " + filename).c_str());
}

bool FDGraph::exists(const string& path) {
	// Code taken from the Animation class included in mp_traversals.
	struct stat st;
	if (stat(path.c_str(), &st) != 0) {
		return false;
	}
	if ((st.st_mode & S_IRUSR) == 0) {
		return false;
	}
	if (path[path.length() - 1] != '/') {
		return S_ISREG(st.st_mode);
	}
	if ((st.st_mode & S_IXUSR) == 0) {
		return false;
	}
		
	return S_ISDIR(st.st_mode);
}