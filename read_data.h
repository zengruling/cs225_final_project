#pragma once

#include <vector>
#include "graph.h"

using namespace std;

/**
* Object class that reads the dataset into a Graph object.
*/
class DataReader {
public:
	DataReader(string genreFilename, string dataFilename);
	Graph getGraph();
	vector<string> getGenres();
private:
	vector<string> genres_;
	Graph genre_graph_;
	int getGenreIndex(string genre);
};