#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <vector>

using namespace std;

// Template class for a generic Graph
template <typename T>
class Graph {
protected:
    struct Edge {
        T target;
        double weight;
    };

    struct AdjacencyNode {
        T vertex;
        vector<Edge> neighbors;
    };

    vector<AdjacencyNode> adjList;

    // Helper method to find the index of a vertex
    int getVertexIndex(const T& vertex) const {
        for (size_t i = 0; i < adjList.size(); ++i) {
            if (adjList[i].vertex == vertex) {
                return i;
            }
        }
        return -1;
    }

public:
    void addVertex(const T& vertex) {
        if (getVertexIndex(vertex) == -1) {
            AdjacencyNode newNode;
            newNode.vertex = vertex;
            adjList.push_back(newNode);
        }
    }

    void addEdge(const T& source, const T& target, double weight, bool isBidirectional = false) {
        addVertex(source);
        addVertex(target);

        int sourceIdx = getVertexIndex(source);
        int targetIdx = getVertexIndex(target);

        if (sourceIdx != -1) {
            Edge e1;
            e1.target = target;
            e1.weight = weight;
            adjList[sourceIdx].neighbors.push_back(e1);
        }

        if (isBidirectional && targetIdx != -1) {
            Edge e2;
            e2.target = source;
            e2.weight = weight;
            adjList[targetIdx].neighbors.push_back(e2);
        }
    }

    vector<Edge> getNeighbors(const T& vertex) const {
        int idx = getVertexIndex(vertex);
        if (idx != -1) {
            return adjList[idx].neighbors;
        }
        return vector<Edge>();
    }

    bool hasVertex(const T& vertex) const {
        return getVertexIndex(vertex) != -1;
    }
};

// Data structure to hold song details
struct Song {
    string id;
    string title;
    string artist;
    string genre;
};

#endif // MAIN_H