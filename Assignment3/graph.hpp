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

using Matrix = vector<vector<uint8_t>>;

//Graph with Matrix.
//Since it's undirected, the matrix is not square. In fact, it's more of a triangle. The diagram below shows a possible matrix.
//"." represents no edge, "1" represents an edge, "X"s are unused bits, row and column represent the index of the vertex given by the lookup table.
//Instead of using a vector of booleans, this uses a vector of uint8_t where all 8 bits could be used. This is more memory efficient.
//   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
// 0 .  X  X  X  X  X  X  X
// 1 .  1  X  X  X  X  X  X
// 2 .  .  .  X  X  X  X  X
// 3 .  .  1  .  X  X  X  X
// 4 .  .  1  .  .  X  X  X
// 5 .  .  .  .  .  .  X  X
// 6 .  1  .  1  .  .  .  X
// 7 .  .  .  .  .  1  .  .
// 8 .  1  .  .  .  .  .  .  1  X  X  X  X  X  X  X
// 9 .  .  .  1  .  .  .  .  .  .  X  X  X  X  X  X
//10 .  .  .  .  .  .  1  .  .  .  .  X  X  X  X  X
//11 .  .  1  .  .  .  .  .  .  .  .  .  X  X  X  X
//12 .  .  .  .  .  .  .  .  .  .  .  1  .  X  X  X
//13 .  .  .  1  .  .  .  .  1  .  .  .  .  .  X  X
//14 .  1  .  .  .  1  .  .  .  .  .  1  .  .  .  X
//15 1  .  .  .  .  .  .  .  .  .  .  .  .  .  .  1
template<>
struct Graph<Matrix> {
	Matrix matrix;
	unordered_map<string, int> id_lookup;

	void add_vertex(const string& id) {
		const int index = static_cast<int>(id_lookup.size());
		id_lookup[id] = index;
		vector<uint8_t> vec = vector<uint8_t>(matrix.size() / 8 + 1);
		matrix.emplace_back(vec);
	}
	void add_edge(const string& id0, const string& id1) {
		uint8_t r = id_lookup[id0];
		uint8_t c = id_lookup[id1];
		if (r < c) {
			std::swap(r, c);
		}
		matrix[r][c / 8] |= (0b10000000 >> (c % 8));
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
			const vector<uint8_t>& row = matrix[pair.second];
			for (int c = 0; c < row.size() - 1; c++) {//haha C++
				for (uint8_t b = 0b10000000; b != 0; b >>= 1) {
					if (const uint8_t bit = row[c] & b; bit == 0) {
						printf(".  ");
					} else {
						printf("1  ");
					}
				}
			}
			//print the last byte
			for (uint8_t b = 0b10000000, i = 0; b != 0; b >>= 1) {
				if (i > pair.second % 8) {
					printf("X  ");
					continue;
				}
				i++;
				if (const uint8_t bit = row[row.size() - 1] & b; bit == 0) {
					printf(".  ");
				} else {
					printf("1  ");
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