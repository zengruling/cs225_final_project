#include "read_data.h"

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <math.h>

using namespace std;

DataReader::DataReader(string genreFilename, string dataFilename)
{
    ifstream genreFile(genreFilename);
    string genre;
    string delimiter = "\t";
    if (genreFile.is_open()) {
        while (getline(genreFile, genre)) {
            if (!genre.empty() && genre[genre.size() - 1] == '\r') {
                genre.erase(genre.size() - 1);
            }
            genres_.push_back(genre);
        }
    }

    vector<int> songs_count(genres_.size());
    vector<vector<int>> connections(genres_.size(), vector<int>(genres_.size()));
    ifstream trainFile(dataFilename);
    string line;
    size_t connection_count = 0;
    if (trainFile.is_open()) {
        getline(trainFile, line);
        while(getline(trainFile, line)) {
            size_t pos = 0;
            string token;
            vector<string> music_genres;
            size_t count = 0;
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                count++;
                if (count > 2 && token.length() > 0 && token.find("---") == string::npos) {
                    music_genres.push_back(token);
                }
                line.erase(0, pos + delimiter.length());
            }
            for (size_t k = 0; k < music_genres.size(); k++) {
                int index = getGenreIndex(music_genres[k]);
                songs_count[index]++;
            }
            if (music_genres.size() > 1) {
                for (size_t i = 0; i < music_genres.size() - 1; i++) {
                    for (size_t j = i + 1; j < music_genres.size(); j++) {
                        int index1 = getGenreIndex(music_genres[i]);
                        int index2 = getGenreIndex(music_genres[j]);
                        connection_count++;
                        if (index1 > index2) {
                            connections[index2][index1]++;
                        }
                        else {
                            connections[index1][index2]++;
                        }
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < genres_.size(); i++) {
        genre_graph_.addVertex(i, genres_[i], songs_count[i]);
    }

    for (size_t i = 0; i < connections.size(); i++) {
        vector<int> connection = connections[i];
        for (size_t j = 0; j < connection.size(); j++) {
            if (connection[j] > 0) {
                float weight = log(((float) connection_count) / connection[j]);
                genre_graph_.addEdge(i, j, weight);
            }
        }
    }
}

int DataReader::getGenreIndex(string genre) {
    for (size_t i = 0; i < genres_.size(); i++) {
        if (genres_[i] == genre) {
            return i;
        }
    }
    return -1;
}

Graph DataReader::getGraph() {
    return genre_graph_;
}

vector<string> DataReader::getGenres() {
    return genres_;
}