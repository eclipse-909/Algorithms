#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using std::vector;
using std::unordered_map;
using std::pair;
using std::queue;
using std::unordered_set;

//Base Graph
//Has specific template specializations for Matrix, AdjList, and vector<Vertex>.
//Cannot be used otherwise.
template<typename Storage>
struct Graph {
	void add_vertex(const string& id);
	void add_edge(const string& id0, const string& id1);
};

using Matrix = vector<pair<string, vector<bool>>>;

//Graph with Matrix.
//Uses a vector<bool> which uses the memory optimization with bit manipulation.
//Since it's undirected, the matrix is not square. In fact, it's a triangle. The diagram below shows a possible matrix.
//"." represents no edge, "1" represents an edge, row and column represent the vertex ID.
//   0  1  2  3  4  5  6  7
// 0 .
// 1 .  1
// 2 .  .  .
// 3 .  .  1  .
// 4 .  .  1  .  .
// 5 .  .  .  .  .  .
// 6 .  1  .  1  .  .  .
// 7 .  .  .  .  .  1  .  .
template<>
struct Graph<Matrix> {
	Matrix matrix;
	unordered_map<string, int> id_lookup;

	void add_vertex(const string& id) {
		const int index = static_cast<int>(id_lookup.size());
		id_lookup[id] = index;
		pair<string, vector<bool>> p(id, vector<bool>(matrix.size() + 1));
		matrix.emplace_back(p);
	}

	void add_edge(const string& id0, const string& id1) {
		uint8_t r = id_lookup[id0];
		uint8_t c = id_lookup[id1];
		//In an undirected graph, we only need to keep track of the edge in one spot.
		//This is done by forcing the ordering of the given vertex IDs to always be a specific way.
		//In this case, the row must not be less than the column.
		//This is why we can use the triangle shape shown in the Graph<Matrix> documentation.
		if (r < c) {
			std::swap(r, c);
		}
		matrix[r].second[c] = true;
	}

	void print() const {
		printf(" ");
		//print X-axis vertex IDs
		for (const pair<string, vector<bool>>& pair : matrix) {
			if (pair.first.length() == 1) {
				printf("  %s", pair.first.c_str());
			} else {
				printf(" %s", pair.first.c_str());
			}
		}
		printf("\n");
		//Print each row
		for (const pair<string, vector<bool>>& pair : matrix) {
			//print vertex ID
			if (pair.first.length() == 1) {
				printf(" %s ", pair.first.c_str());
			} else {
				printf("%s ", pair.first.c_str());
			}
			//Print edges
			for (const bool col : pair.second) {
				if (col) {
					printf("1  ");
				} else {
					printf(".  ");
				}
			}
			printf("\n");
		}
	}
};

using AdjList = vector<pair<string, vector<int>>>;

//Graph with Adjacency List
//This is an undirected graph, so printing the adjacency list will only show 1 edge between vertices.
//Here is an example:
// 0 |
// 1 | 1
// 2 |
// 3 | 2
// 4 | 2
// 5 |
// 6 | 1, 3
// 7 | 5
template<>
struct Graph<AdjList> {
	AdjList adj_list;
	unordered_map<string, int> id_lookup;

	void add_vertex(const string& id) {
		id_lookup[id] = static_cast<int>(id_lookup.size());
		pair<string, vector<int>> p(id, vector<int>());
		adj_list.emplace_back(p);
	}

	void add_edge(const string& id0, const string& id1) {
		int index0 = id_lookup[id0];
		int index1 = id_lookup[id1];
		//In an undirected graph, we only need to keep track of the edge in one spot.
		//This is done by forcing the ordering of the given vertex IDs to always be a specific way.
		//In this case, index0 must not be less than index1.
		//This way, the adjacency list is always indexed by the same number when given the same two vertices.
		if (index0 < index1) {
			std::swap(index0, index1);
		}
		adj_list[index0].second.emplace_back(index1);
	}

	void print() const {
		for (const pair<string, vector<int>>& row : adj_list) {
			//print vertex ID
			printf("%s |", row.first.c_str());
			//print vertex ID of adjacent vertices
			for (const int col : row.second) {
				printf(" %s,", adj_list[col].first.c_str());
			}
			printf("\n");
		}
	}
};

//Vertex for Graph with Linked Objects
struct Vertex {
	string id;
	vector<const Vertex*> neighbors;
};

//Graph with Linked Objects
template<>
struct Graph<vector<Vertex>> {
	vector<Vertex> vertices;
	unordered_map<string, int> id_lookup;

	void add_vertex(const string& id) {
		id_lookup[id] = static_cast<int>(id_lookup.size());
		Vertex v = {id, vector<const Vertex*>()};
		vertices.emplace_back(v);
	}

	void add_edge(const string& id0, const string& id1) {
		Vertex* v0 = &vertices[id_lookup[id0]];
		Vertex* v1 = &vertices[id_lookup[id1]];
		v0->neighbors.emplace_back(v1);
		v1->neighbors.emplace_back(v0);
	}

	void print_breadth_first() const {
		if (vertices.empty()) {return;}
		unordered_set<const Vertex*> processed;
		queue<const Vertex*> q;
		const Vertex* v0 = &vertices[0];
		processed.insert(v0);
		q.push(v0);
		while (!q.empty()) {
			const Vertex* curr = q.front();
			q.pop();
			printf("%s, ", curr->id.c_str());
			for (const Vertex* n : curr->neighbors) {
				if (!processed.contains(n)) {
					q.push(n);
					processed.insert(n);
				}
			}
		}
		printf("\n");
	}

	void print_depth_first() const {
		unordered_set<const Vertex*> processed;
		dft(&vertices[0], &processed);
		printf("\n");
	}

private:
	void dft(const Vertex* v, unordered_set<const Vertex*>* processed) const {
		if (!processed->contains(v)) {
			printf("%s, ", v->id.c_str());
			processed->insert(v);
		}
		for (const Vertex* n : v->neighbors) {
			if (!processed->contains(n)) {
				dft(n, processed);
			}
		}
	}
};

#endif //GRAPH_HPP