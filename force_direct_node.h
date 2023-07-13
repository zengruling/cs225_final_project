#pragma once

#include <math.h>
#include <string>

using namespace std;

/**
* Object class representing specific elements of a graph visualization vertex.
*/
class FDNode {
public:
	FDNode(string name, int x, int y, float force_x, float force_y, float size);

	pair<int, int> getPos();
	float updatePos(float speed);

	void addForce(float force_x, float force_y);
	void setForce(float force_x, float force_y);

	string getName();
	float getSize();

private:
	string name_;
	int pos_x_;
	int pos_y_;
	float force_x_;
	float force_y_;
	float size_;
};