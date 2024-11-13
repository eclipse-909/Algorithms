#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <algorithm>

using std::vector;
using std::unordered_map;
using std::pair;

//Base Graph
//Has specific template implementations for Matrix, AdjList, and vector<Vertex>.
template<typename Storage>
struct Graph {
	Storage storage;
	unordered_map<string, int> id_lookup;

	void add_vertex(const string& id);
	void add_edge(const string& id0, const string& id1);
};

using Matrix = vector<vector<bool>>;

//Graph with Matrix.
//Uses a vector<bool> which uses the memory optimization with bit manipulation.
//Since it's undirected, the matrix is not square. In fact, it's more of a triangle. The diagram below shows a possible matrix.
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
		vector<bool> vec(matrix.size() + 1);
		matrix.emplace_back(vec);
	}
	void add_edge(const string& id0, const string& id1) {
		uint8_t r = id_lookup[id0];
		uint8_t c = id_lookup[id1];
		if (r < c) {
			std::swap(r, c);
		}
		matrix[r][c] = true;
	}

	//Prints the matrix in the order given by the unordered_map.
	//This is done in n^2 time, but it looks hideous.
	void quick_print() const {print(id_lookup);}

	//Prints the matrix in the order they are listed in the file.
	//This is also done in n^2 time, but it requires additional computation to sort, and it looks pretty.
	void sorted_print() const {
		vector<pair<string, int>> sortedPairs(id_lookup.begin(), id_lookup.end());
		std::sort(
			sortedPairs.begin(),
			sortedPairs.end(),
			[](const pair<string, int>& a, const pair<string, int>& b) {
				return a.second < b.second;
			}
		);
		print(sortedPairs);
	}

private:
	template <typename Iterable>
	void print(const Iterable& iter) const {
		printf(" ");
		//print X-axis vertex IDs
		for (const auto& pair : iter) {
			if (pair.first.length() == 1) {
				printf("  %s", pair.first.c_str());
			} else {
				printf(" %s", pair.first.c_str());
			}
		}
		printf("\n");
		//Print each row
		for (const auto& pair : iter) {
			//print vertex ID
			if (pair.first.length() == 1) {
				printf(" %s ", pair.first.c_str());
			} else {
				printf("%s ", pair.first.c_str());
			}
			//Print all bytes except the last
			for (const bool col : matrix[pair.second]) {//haha C++
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

using AdjList = vector<vector<int>>;

//Graph with Adjacency List
template<>
struct Graph<AdjList> {
	AdjList adj_list;
	unordered_map<string, int> id_lookup;

	void add_vertex(const string& id) {
		id_lookup[id] = static_cast<int>(id_lookup.size());
		// vector<uint8_t> vec = vector<uint8_t>(adj_list.size() / 8 + 1);
		// adj_list.emplace_back(vec);
		//TODO
	}
	void add_edge(const string& id0, const string& id1) {
		//TODO
	}

	void print() const {
		//TODO
	}
};

//Vertex for Graph with Linked Objects
struct Vertex {vector<Vertex> neighbors;};

//Graph with Linked Objects
template<>
struct Graph<vector<Vertex>> {
	vector<Vertex> vertices;
	unordered_map<string, int> id_lookup;

	void add_vertex(const string& id) {
		id_lookup[id] = static_cast<int>(id_lookup.size());
		//TODO
	}
	void add_edge(const string& id0, const string& id1) {
		//TODO
	}

	void print_breadth_first() const {
		//TODO
	}
	void print_depth_first() const {
		//TODO
	}
};

#endif //GRAPH_HPP