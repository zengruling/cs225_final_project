#include "graph.h"

Graph::Graph() {

}

void Graph::addVertex(int id, string name, size_t size) {
    Vertex v(id, name, size);
    vertices_.push_back(v);
    for (size_t i = 0; i < vertices_.size() - 1; i++) {
        weights_[i].push_back(0.0);
    }
    weights_.push_back(vector<float>(vertices_.size()));
}

void Graph::addEdge(int point1, int point2, float weight) {
    if (point1 > point2) {
        weights_[point2][point1] = weight;
    }
    else {
        weights_[point1][point2] = weight;
    }
}

size_t Graph::getSize() {
	return vertices_.size();
}

vector<Graph::Vertex> Graph::getAdjacentVertices(int vertex) {
    vector<float> weights = weights_[vertex];
    vector<Graph::Vertex> vertices;
    for (size_t i = vertex + 1; i < vertices_.size(); i++) {
        if (weights[i] > 0) {
            vertices.push_back(vertices_[i]);
        }
    }
    for (int i = 0; i < vertex; i++) {
        if (weights_[i][vertex] > 0) {
            vertices.push_back(vertices_[i]);
        }
    }

    return vertices;
}

vector<Graph::Edge> Graph::getAdjacentEdges(int vertex) {
    vector<float> weights = weights_[vertex];
    vector<Graph::Edge> edges;
    for (size_t i = vertex + 1; i < vertices_.size(); i++) {
        if (weights[i] > 0) {
            Graph::Edge edge(vertex, i, weights[i]);
            edges.push_back(edge);
        }
    }
    for (int i = 0; i < vertex; i++) {
        if (weights_[i][vertex] > 0) {
            Graph::Edge edge(i, vertex, weights_[i][vertex]);
            edges.push_back(edge);
        }
    }
    return edges;
}

vector<Graph::Vertex> Graph::getAllVertices() {
    return vertices_;
}

vector<Graph::Edge> Graph::getAllEdges() {
    vector<Graph::Edge> edges;
    for (size_t i = 0; i < vertices_.size() - 1; i++) {
        vector<float> weights = weights_[i];
        for (size_t j = i + 1; j < vertices_.size(); j++) {
            if (weights[j] > 0) {
                Graph::Edge edge(i, j, weights[j]);
                edges.push_back(edge);
            }
        }
    }
    return edges;
}

std::vector<std::vector<int>> Graph::BFS(int vertex) {
    std::queue<int> q;
    std::vector<bool> visited;
	
    //output with level order for a specific vertex.
    std::vector<std::vector<int>> relevance;

    size_t size = vertex;
    //check for invalid input
    if (size < 0 || size >= vertices_.size()) {
        return relevance;
    }

    for (size_t i = 0; i < vertices_.size(); ++i) {
        visited.push_back(false);
    }
    visited[vertex] = true;
    q.push(vertex);
	
    //set base level(0) to itself 
    std::vector<int> base = {vertex};
    relevance.push_back(base);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        std::vector<int> level;
        for (Vertex w : getAdjacentVertices(v)) {
            if (visited[w.id_] == false) {
		//stores vertices in the same level
                level.push_back(w.id_);
		    
                q.push(w.id_);
                visited[w.id_] = true;
            }
        }
	    
	//check for empty levels
        if (level.size() != 0) {
            relevance.push_back(level);
        }
    }
    return relevance;
}

void Graph::relevance(int vertex) {
    std::vector<std::vector<int>> levels = BFS(vertex);
    for (size_t i = 0; i < levels.size(); i++) {
        std::cout << "Relevance level " << i << ": ";
        for (size_t j = 0; j < levels[i].size(); j++) {
            //a better format, looks nicer
            if (j == levels[i].size() - 1) {
                std:: cout << IDtoVertex(levels[i][j]).name_;
            } else {
                std:: cout << IDtoVertex(levels[i][j]).name_ << ", ";
            }
        }
        std::cout << std::endl;
    }
}

Graph::Vertex Graph::IDXtoVertex(int IDX){
    //for (auto it = vertices_.begin(); it != vertices_.end(); ++it){
    //    if (it->id_ == ID) return (*it);
    //}
    if (IDX < (int)vertices_.size()) return vertices_[IDX];
    else return Vertex(999,"error",999);
}

Graph::Vertex Graph::IDtoVertex(int ID){
    for (auto it = vertices_.begin(); it != vertices_.end(); ++it){
        if (it->id_ == ID) return (*it);
    }
    //if (IDX < (int)vertices_.size()) return vertices_[IDX];
    return Vertex(999,"error",999);
}
