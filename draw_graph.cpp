#include "draw_graph.h"

DrawGraph::DrawGraph(int rect_width, int rect_height, int font_width, int font_height, string font_file, HSLAPixel vertex_color, HSLAPixel edge_color) {
	rect_width_ = rect_width;
	rect_height_ = rect_height;
	font_width_ = font_width;
	font_height_ = font_height;
	
	font_.readFromFile(font_file);
	vertex_color_ = HSLAPixel(vertex_color.h, vertex_color.s, vertex_color.l, vertex_color.a);
	edge_color_ = HSLAPixel(edge_color.h, edge_color.s, edge_color.l, edge_color.a);
}

void DrawGraph::drawText(PNG* png, int x, int y, string txt) {
	int x_center = x - (txt.length() * font_width_) / 2;
	int y_center = y - (font_height_ / 2);
	for (unsigned int i = 0; i < txt.length(); i++) {
		drawChar(png, x_center + i * font_width_, y_center, txt.at(i));
	}
}

void DrawGraph::drawEdge(PNG* png, int start_x, int start_y, int end_x, int end_y) {
	if (start_x == end_x && start_y == end_y) {
		drawPixel(start_x, start_y, png, edge_color_);
		return;
	}
	if (abs(end_x - start_x) > abs(end_y - start_y)) {
		int start = start_x;
		int end = end_x;
		int y0 = start_y;
		int y1 = end_y;
		if (end < start) {
			start = end_x;
			end = start_x;
			y0 = end_y;
			y1 = start_y;
		}
		for (int i = start; i <= end; i++) {
			int y = y0 + (i - start) * (y1 - y0) / (end - start);
			drawPixel(i, y, png, edge_color_);
		}
	}
	else {
		int start = start_y;
		int end = end_y;
		int x0 = start_x;
		int x1 = end_x;
		if (end < start) {
			start = end_y;
			end = start_y;
			x0 = end_x;
			x1 = start_x;
		}
		for (int i = start; i <= end; i++) {
			int x = x0 + (i - start) * (x1 - x0) / (end - start);
			drawPixel(x, i, png, edge_color_);
		}
	}
}

void DrawGraph::drawVertex(PNG* png, int center_x, int center_y, double radius) {
	int start = center_x - radius;
	int end = center_x + radius;
	for (int i = start; i <= end; i++) {
		int dy = sqrt(radius * radius - (i - center_x) * (i - center_x));
		drawPixel(i, center_y + dy, png, vertex_color_);
		drawPixel(i, center_y - dy, png, vertex_color_);
	}
	start = center_y - radius;
	end = center_y + radius;
	for (int i = start; i <= end; i++) {
		int dx = sqrt(radius * radius - (i - center_y) * (i - center_y));
		drawPixel(center_x + dx, i, png, vertex_color_);
		drawPixel(center_x - dx, i, png, vertex_color_);
	}
}

void DrawGraph::drawChar(PNG* png, int x, int y, char ch) {
	int font_x = ((ch - 32) % 16) * rect_width_;
	int font_y = ((ch - 32) / 16) * rect_height_;
	for (int i = 0; i < font_width_; i++) {
		for (int j = 0; j < font_height_; j++) {
			copyPixel(font_x + i, font_y + j, png, x + i, y + j);
		}
	}
}

void DrawGraph::copyPixel(int x0, int y0, PNG* png, int x1, int y1) {
	if (x1 < 0 || y1 < 0 || x1 >= (int)png->width() || y1 >= (int)png->height()) {
		return;
	}
	HSLAPixel& pixel = png->getPixel(x1, y1);
	HSLAPixel& font_pixel = font_.getPixel(x0, y0);
	pixel.h = font_pixel.h;
	pixel.s = font_pixel.s;
	pixel.l = font_pixel.l;
	pixel.a = font_pixel.a;
}

void DrawGraph::drawPixel(int x, int y, PNG* png, HSLAPixel color) {
	if (x < 0 || y < 0 || x >= (int) png->width() || y >= (int) png->height()) {
		return;
	}
	HSLAPixel& pixel = png->getPixel(x, y);
	pixel.h = color.h;
	pixel.s = color.s;
	pixel.l = color.l;
	pixel.a = color.a;
}