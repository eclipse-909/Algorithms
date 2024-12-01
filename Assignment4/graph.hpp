#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <algorithm>

using std::vector;
using std::unordered_map;
using std::pair;
using std::queue;
using std::unordered_set;

//Vertex for Graph with Linked Objects
struct Vertex {
	int id;
	//pointer to adjacent vertex and weight
	vector<pair<Vertex*, int>> neighbors;
	int distance;
	int predecessor;

	explicit Vertex(const int id) : id(id), neighbors(vector<pair<Vertex*, int>>()), distance(INT_MAX), predecessor(-1) {}
};

//Directed, Weighted graph with Linked Objects
struct Graph {
	vector<Vertex> vertices;
	//Maps vertex ID -> index within vertices vector
	unordered_map<int, int> id_lookup;

	void add_vertex(const int id) {
		id_lookup[id] = static_cast<int>(id_lookup.size());
		Vertex v = Vertex(id);
		vertices.emplace_back(v);
	}

	void add_edge(const int id0, const int id1, const int weight) {
		pair<Vertex*, int> pair(&vertices[id_lookup[id1]], weight);
		vertices[id_lookup[id0]].neighbors.emplace_back(pair);
	}

	void bellman_ford(const int srcID) {
	    // Initialize source vertex distance
	    Vertex* srcVertex = &vertices[id_lookup[srcID]];
	    srcVertex->distance = 0;

	    // Relax edges |V| - 1 times
	    const int V = static_cast<int>(vertices.size());
	    for (int i = 0; i < V - 1; ++i) {
	        for (Vertex& vertex : vertices) {
	            for (const pair<Vertex*, int>& neighbor : vertex.neighbors) {
					// Relaxation step
	                if (const int weight = neighbor.second; vertex.distance != INT_MAX && vertex.distance + weight < neighbor.first->distance) {
	                    neighbor.first->distance = vertex.distance + weight;
	                    neighbor.first->predecessor = vertex.id;
	                }
	            }
	        }
	    }

	    // Check for negative-weight cycles
	    for (const Vertex& vertex : vertices) {
	        for (const pair<Vertex*, int>& neighbor : vertex.neighbors) {
				if (const int weight = neighbor.second; vertex.distance != INT_MAX && vertex.distance + weight < neighbor.first->distance) {
					fprintf(stderr, "Graph contains a negative-weight cycle");
					return;
	            }
	        }
	    }

	    // Print shortest paths
		for (const Vertex& vertex : vertices) {
			if (vertex.id == srcID) {
				// Skip the source vertex
				continue;
			}
			if (vertex.distance == INT_MAX) {
				printf("%d --> %d cost is ∞; path: none\n", srcID, vertex.id);
				continue;
			}
			// Reconstruct the path
			vector<int> path;
			for (int at = vertex.id; at != -1; at = vertices[id_lookup[at]].predecessor) {
				path.push_back(at);
			}
			std::reverse(path.begin(), path.end());

			// Print the result
			printf("%d --> %d cost is %d; path: ", srcID, vertex.id, vertex.distance);
			for (size_t i = 0; i < path.size(); ++i) {
				printf("%d", path[i]);
				if (i < path.size() - 1) {
					printf(" --> ");
				}
			}
			printf("\n");
		}
	}
};

#endif //GRAPH_HPP