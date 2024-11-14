#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <algorithm>
#include <tuple>

using std::vector;
using std::unordered_map;
using std::pair;
using std::tuple;

//Base Graph
//Has specific template specializations for Matrix, AdjList, and vector<Vertex>.
//Cannot be used otherwise.
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
		vector<bool> vec(matrix.size() + 1);
		matrix.emplace_back(vec);
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
		matrix[r][c] = true;
	}

	//Prints the matrix in the order given by the unordered_map.
	//This is done in n^2 time, but it looks hideous.
	//Vertex IDs are assumed to be strings of length 1 or 2.
	void quick_print() const {print(id_lookup);}

	//Prints the matrix in the order they are listed in the file.
	//This is also done in n^2 time, but it requires additional computation to sort, and it looks pretty.
	//Vertex IDs are assumed to be strings of length 1 or 2.
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

using AdjList = vector<tuple<string, vector<int>>>;

//Graph with Adjacency List
template<>
struct Graph<AdjList> {
	AdjList adj_list;
	unordered_map<string, int> id_lookup;

	void add_vertex(const string& id) {
		id_lookup[id] = static_cast<int>(id_lookup.size());
		vector<int> vec;
		adj_list.emplace_back(std::make_tuple(id, vec));
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
		std::get<1>(adj_list[index0]).emplace_back(index1);
	}

	void print() const {
		for (const tuple<string, vector<int>>& row : adj_list) {
			//print vertex ID
			printf("%s |", std::get<0>(row).c_str());
			//print vertex ID of adjacent vertices
			for (const int col : std::get<1>(row)) {
				printf(" %s,", std::get<0>(adj_list[col]).c_str());
			}
			printf("\n");
		}
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