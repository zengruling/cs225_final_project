#pragma once

#include "cs225/PNG.h"
#include <math.h>

using namespace std;
using namespace cs225;

/**
* Object class handling drawing specific elements of the graph structure visualization. 
* Drawing vertices, drawing edges, drawing text, etc.
*/
class DrawGraph {
public:
	DrawGraph(int rect_width, int rect_height, int font_width, int font_height, string font_file, HSLAPixel vertex_color, HSLAPixel edge_color);
	void drawText(PNG* png, int x, int y, string txt);
	void drawEdge(PNG* png, int start_x, int start_y, int end_x, int end_y);
	void drawVertex(PNG* png, int center_x, int center_y, double radius);
	
private:
	PNG font_;
	HSLAPixel vertex_color_;
	HSLAPixel edge_color_;
	int font_width_;
	int font_height_;
	int rect_height_;
	int rect_width_;
	void drawChar(PNG* png, int x, int y, char ch);
	void copyPixel(int x0, int y0, PNG* png, int x1, int y1);
	void drawPixel(int x, int y, PNG* png, HSLAPixel color);
};