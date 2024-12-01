#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using std::vector;
using std::unordered_map;
using std::pair;
using std::queue;
using std::unordered_set;

//Vertex for Graph with Linked Objects
struct Vertex {
	int id;
	//pointer to adjacent vertex and weight
	vector<pair<const Vertex*, int>> neighbors;
};

//Directed, Weighted graph with Linked Objects
struct Graph {
	vector<Vertex> vertices;
	//Maps vertex ID -> index within vertices vector
	unordered_map<int, int> id_lookup;

	void add_vertex(const int id) {
		id_lookup[id] = static_cast<int>(id_lookup.size());
		Vertex v = {id, vector<pair<const Vertex*, int>>()};
		vertices.emplace_back(v);
	}

	void add_edge(const int id0, const int id1, const int weight) {
		pair<const Vertex*, int> pair(&vertices[id_lookup[id1]], weight);
		vertices[id_lookup[id0]].neighbors.emplace_back(pair);
	}

	void bellman_ford(const int srcID) {
		const Vertex* srcVertex = &vertices[id_lookup[srcID]];
		//TODO
	}
};

#endif //GRAPH_HPP