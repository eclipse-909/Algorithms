#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>

//#include <filesystem>
#include <sys/stat.h>//replacement for filesystem since I can't link with it

#include "binary_search_tree.hpp"
#include "graph.hpp"

using std::vector;

void print_graphs(const Graph<Matrix>* graph_m, const Graph<AdjList>* graph_al, const Graph<vector<Vertex>>* graph_lo) {
	printf("Graph with Matrix:\n");
	graph_m->sorted_print();
	printf("\nGraph with Adjacency List:\n");
	graph_al->print();
	printf("\nGraph with Linked Objects - Depth First:\n");
	graph_lo->print_depth_first();
	printf("\nGraph with Linked Objects - Breadth First:\n");
	graph_lo->print_breadth_first();
	printf("\n");
}

int main(int argc, char* argv[]) {
	//Make a list of all the graph files to use
	vector<string> graph_files = vector<string>();
	if (argc == 1) {
		graph_files.emplace_back("./graphs1.txt");
	} else {
		for (int i = 1; i < argc; i++) {
			struct _stat buffer;
			// File exists and is a regular file
			if (_stat(argv[i], &buffer) == 0 && (buffer.st_mode & S_IFREG) != 0) {
				graph_files.emplace_back(argv[i]);
			} else {
				fprintf(stderr, "Error - invalid file path: %s\n", argv[i]);
				return 1;
			}
		}
	}

	//Do graph stuff for each graph file
	string line;
	for (const string& file : graph_files) {
		std::ifstream graph_file(file);
		if (!graph_file.is_open()) {
			fprintf(stderr, "Unable to open file %s\n", file.c_str());
			return 1;
		}
		Graph<Matrix> graph_m;
		Graph<AdjList> graph_al;
		Graph<vector<Vertex>> graph_lo;
		bool init = false;
		int lineNum = 0;
		while (std::getline(graph_file, line)) {
			lineNum++;
			//ignore comments
			if (size_t pos = line.find("--"); pos != std::string::npos) {
				line = line.substr(0, pos);
			}
			//skip empty lines
			if (line.empty()) {continue;}

			//parse tokens
			std::istringstream iss(line);
			std::string command;
			iss >> command;
			if (command == "new") {
				std::string graph;
				iss >> graph;
				if (graph == "graph") {
					if (init) {
						print_graphs(&graph_m, &graph_al, &graph_lo);
					}
					graph_m = Graph<Matrix>();
					graph_al = Graph<AdjList>();
					graph_lo = Graph<vector<Vertex>>();
					init = true;
				} else {
					fprintf(stderr, "Error - unrecognized token: %s\nLine number: %d\n", graph.c_str(), lineNum);
					return 1;
				}
			} else if (command == "add") {
				std::string type;
				iss >> type;
				if (type == "vertex") {
					if (string vertex; iss >> vertex) {
						graph_m.add_vertex(vertex);
						graph_al.add_vertex(vertex);
						graph_lo.add_vertex(vertex);
					} else {
						fprintf(stderr, "Error - failed to parse vertex id as int\nLine Number: %d\n", lineNum);
						return 1;
					}
				} else if (type == "edge") {
					char dash;
					if (string vertex0, vertex1; iss >> vertex0 >> dash >> vertex1 && dash == '-') {
						graph_m.add_edge(vertex0, vertex1);
						graph_al.add_edge(vertex0, vertex1);
						graph_lo.add_edge(vertex0, vertex1);
					} else {
						fprintf(stderr, "Error - failed to parse vertex id as int\nLine Number: %d\n", lineNum);
						return 1;
					}
				} else {
					fprintf(stderr, "Error - unrecognized token: %s\nLine Number%d\n", type.c_str(), lineNum);
					return 1;
				}
			} else {
				fprintf(stderr, "Error - unrecognized token: %s\nLine Number %d\n", command.c_str(), lineNum);
				return 1;
			}
		}
		print_graphs(&graph_m, &graph_al, &graph_lo);
		graph_file.close();
	}

	//Read lines from magicitems.txt and insert into BST
	std::ifstream magicitems("../magicitems.txt");
	if (!magicitems.is_open()) {
		fprintf(stderr, "Unable to open magicitems.txt\n");
		return 1;
	}
	BinarySearchTree bst = BinarySearchTree();
	while (std::getline(magicitems, line)) {
		bst.insert(line);
	}
	magicitems.close();

	//print items in order
	bst.depth_first_traverse();

	//Read lines from magicitems-find-in-bst.txt and search BST
	std::ifstream file("./magicitems-find-in-bst.txt");
	if (!file.is_open()) {
		fprintf(stderr, "Unable to open magicitems-find-in-bst.txt\n");
		return 1;
	}
	int comparisons = 0;
	int count = 0;
	while (std::getline(file, line)) {
		int c = bst.search(line);
		if (c < 0) {
			fprintf(stderr, ", Not found after %d comparisons\n", c);
			c *= -1;
		} else {
			printf(", Found after %d comparisons\n", c);
		}
		comparisons += c;
		count++;
	}
	file.close();
	printf("Average comparisons: %f\n", static_cast<float>(comparisons) / static_cast<float>(count));

	return 0;
}