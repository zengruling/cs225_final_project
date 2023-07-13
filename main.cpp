#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

#include "graph.h"
#include "read_data.h"
#include "draw_graph.h"
#include "force_direct_graph.h"
#include "Dijkstra.h"

using namespace std;

bool isNumber(const string& str) {
	for (char const& c : str) {
		if (std::isdigit(c) == 0) {
			return false;
		}
	}
	return true;
}

vector<string> readGenres() {
	vector<string> genres;
	ifstream genreFile("data/genres.txt");
	string genre;
	string delimiter = "\t";
	if (genreFile.is_open()) {
		/* Reads a line from `genreFile` into `genre` until the pfile ends. */
		while (getline(genreFile, genre)) {
			if (!genre.empty() && genre[genre.size() - 1] == '\r') {
				genre.erase(genre.size() - 1);
			}
			genres.push_back(genre);
		}
	}
	return genres;
}


int main(int argc, char** argv)
{
	bool visual = false;
	vector<int> arg_num;
	vector<string> genres = readGenres();

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-visual") == 0) {
			visual = true;
		}
		else if (isNumber(argv[i])) {
			arg_num.push_back(stoi(argv[i]));
		}
	}

	if (!visual && (arg_num.size() == 0 || arg_num.size() > 2)) {
		cout << "To create a graph visualization, pass argument '-visual'" << endl;
		cout << "To see genres listed by relevance to a given genre, pass the genre index ex. ./music 1" << endl;
		cout << "To see the level of relevance between two genres, pass the indices of both genres ex. ./music 1 2 (the second function and this function are incompatible.)" << endl;
		for (int j = 0; j < (int)genres.size(); j++) {
			cout << j << ": " + genres[j] << endl;
		}
		return 0;
	}

	int size = (int)genres.size();

	cout << "Creating graph..." << endl;
	DataReader reader("data/genres.txt", "data/train.tsv");
	Graph graph = reader.getGraph();
	cout << "Finished reading." << endl;

	if (visual) {
		FDGraph force_graph(1000, 1000, graph);
		force_graph.makeAnimation("graph_visual.gif");
		cout << "Graph visualization saved to graph_visual.gif." << endl;
	}

	while (arg_num.size() > 0 && arg_num.size() <= 2) {
		if (arg_num.size() == 1) {
			if (arg_num[0] < 0 || arg_num[0] >= size) {
				cout << "Please enter a valid genre index, between 0 and " << genres.size() - 1 << endl;
			}
			else {
				graph.relevance(arg_num[0]);
			}
		}
		else if (arg_num.size() == 2) {
			if (arg_num[0] < 0 || arg_num[0] >= size || arg_num[1] < 0 || arg_num[1] >= size) {
				cout << "Please enter a valid genre index, between 0 and " << genres.size() - 1 << endl;
			}
			else if (arg_num[0] == arg_num[1]) {
				cout << "Please enter two different genre indices." << endl;
			}
			else {
				cout << "Running Djikstra..." << endl;
				Dijkstra d(graph, graph.IDtoVertex(arg_num[0]), graph.IDtoVertex(arg_num[1]));
				d.process();
				d.getDist();
			}
		}
		cout << "Enter one genre index for BFS. Enter two genre indices, seperated by a space, for Dijkstra. Enter anything else to exit." << endl;
		arg_num.clear();
		string str;
		string token;
		getline(cin, str);
		stringstream ss(str);
		while (getline(ss, token, ' ')) {
			if (isNumber(token)) {
				arg_num.push_back(stoi(token));
			}
		}
	}
	
	return 0;
}