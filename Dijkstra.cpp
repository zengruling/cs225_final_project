#include"Dijkstra.h"
#include "graph.h"
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <string>
#include <utility>
#include <limits>
#include <map>

Dijkstra::Dijkstra(Graph graph, Graph::Vertex start, Graph::Vertex end): end_(end),start_(start),graph(graph){
    //this->end_ = end;
    priority.push_back(start);
    for (Graph::Vertex v : graph.getAllVertices()){
        //distance[v] = std::numeric_limits<int>::max();
        distance[v.id_] = 999;
        visited[v.id_] = false;
    }
    distance[start.id_] = 0;
}

std::map<int,float> Dijkstra::getDist(){
    //for (auto it = distance.begin(); it != distance.end(); ++it){
    //    std::cout<<graph.IDtoVertex(it->first).name_<<" => "<<it->second<<std::endl;
    //}
    std::cout << "The closer to 0 the inverse distance, the more connections between the two genres." << endl;
    std::cout<<"The inversed distance from "<<start_.name_<<" to "<<end_.name_<<" is: "<<distance[end_.id_]<<"."<<std::endl;
    if (distance[end_.id_] < 0.1){
        std::cout<<"The two genres are closely related."<<std::endl;
    }
    else if (distance[end_.id_] > 0.1 && distance[end_.id_] < 0.2){
        std::cout<<"The two genres are somewhat related."<<std::endl;
    }
    else{
        std::cout<<"The two genres are not particularly related."<<std::endl;
    }
    return distance;
}

unsigned Dijkstra::findShortest(vector<Graph::Vertex> curr){
    //if (curr.empty()) return std::pair<Graph::Vertex,int>
    unsigned idx = 0;
    for(unsigned i = 0; i < curr.size(); i++){
        if (distance[curr[i].id_] < distance[curr[idx].id_]){
            idx = i;
        }
    }
    return idx;
}

void Dijkstra::process(){
    //unsigned currIdx = findShortest(priority);
    //Graph::Vertex currNode = priority[0];
    //unsigned currIdx = 0;
    unsigned currIdx = findShortest(priority);
    Graph::Vertex currNode = priority[currIdx];

        
    while(currNode.id_ != end_.id_){
        
        //printPri();
        //std::cout<<"now at node: "<<currNode.name_<<std::endl;;
        
        //unsigned currIdx = findShortest(priority);
        //Graph::Vertex currNode = priority[currIdx];

        vector<Graph::Edge> adjacentEdges = graph.getAdjacentEdges(currNode.id_);
        for (Graph::Edge e : adjacentEdges){

            int otherIDX = e.endpoints_.second;
            Graph::Vertex other = graph.IDXtoVertex(otherIDX);
            if (other.id_ == currNode.id_){                       //initialize other Vertex 
                otherIDX = e.endpoints_.first;
                other = graph.IDXtoVertex(otherIDX);
            } 
            int otherID = other.id_;
            

            float newDist = 1/e.weight_ + distance[currNode.id_];   //update distance
            if (newDist < distance[otherID]){
                distance[otherID] = newDist;
            }

            if (!visited[otherID]){
                priority.push_back(other);                      //put neighbors into priority 
            }
        }
            visited[currNode.id_] = true;
            if (!priority.empty()) priority.erase(priority.begin() + currIdx);
            else{
                std::cout<<"dijkstra error"<<std::endl;
                break;
            }
        currIdx = findShortest(priority);
        currNode = priority[currIdx];
        //std::cout<<currNode.id_<<" ? "<<end_.id_<<std::endl;
    }

    vector<Graph::Edge> adjacentEdges = graph.getAdjacentEdges(currNode.id_);
    for (Graph::Edge e : adjacentEdges){

        int otherIDX = e.endpoints_.second;
        Graph::Vertex other = graph.IDXtoVertex(otherIDX);
        if (other.id_ == currNode.id_){                       //initialize other Vertex 
            otherIDX = e.endpoints_.first;
            other = graph.IDXtoVertex(otherIDX);
        } 
        int otherID = other.id_;

        float newDist = 1/e.weight_ + distance[currNode.id_];   //update distance
        if (newDist < distance[otherID]){
            distance[otherID] = newDist;
        }

        if (!visited[otherID]){
            priority.push_back(other);                      //put neighbors into priority 
        }
    }

}

void Dijkstra::printPri(){
    std::cout<<"Priority contain node: "<<std::endl;
    for (auto it = priority.begin(); it != priority.end(); ++it){
        std::cout<<it->name_<<" with distance : "<<distance[it->id_]<<std::endl;
    }
}
