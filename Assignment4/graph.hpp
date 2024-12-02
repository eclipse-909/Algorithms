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

	void reset() {
		distance = INT_MAX;
		predecessor = -1;
	}
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
		vertices[id_lookup[srcID]].distance = 0;

	    // Relax edges V - 1 times
	    for (int i = 0; i < vertices.size() - 1; i++) {
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
					for (Vertex& v : vertices) {
						v.reset();
					}
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
			for (int id = vertex.id; id != -1; id = vertices[id_lookup[id]].predecessor) {
				path.push_back(id);
			}

			// Print the result
			printf("%d --> %d cost is %d; path: ", srcID, vertex.id, vertex.distance);
			for (int i = static_cast<int>(path.size()) - 1; i >= 0; i--) {
				printf("%d", path[i]);
				if (i > 0) {
					printf(" --> ");
				}
			}
			printf("\n");
		}
		for (Vertex& v : vertices) {
			v.reset();
		}
	}
};

#endif //GRAPH_HPP