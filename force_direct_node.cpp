#include "force_direct_node.h"

FDNode::FDNode(string name, int x, int y, float force_x, float force_y, float size) : name_(name), pos_x_(x), pos_y_(y), force_x_(force_x), force_y_(force_y), size_(size) {
}

pair<int, int> FDNode::getPos() {
	return pair<int, int>(pos_x_, pos_y_);
}

float FDNode::updatePos(float speed) {
	float x_change = speed * force_x_ / size_;
	float y_change = speed * force_y_ / size_;
	pos_x_ += x_change;
	pos_y_ += y_change;
	return sqrt((x_change * x_change) + (y_change * y_change));
}

void FDNode::addForce(float force_x, float force_y) {
	force_x_ += force_x;
	force_y_ += force_y;
}

void FDNode::setForce(float force_x, float force_y) {
	force_x_ = force_x;
	force_y_ = force_y;
}

string FDNode::getName() {
	return name_;
}

float FDNode::getSize() {
	return size_;
}