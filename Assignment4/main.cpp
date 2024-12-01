#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

//#include <filesystem>
//replacement for filesystem since I can't link with it
#include <sys/stat.h>
//define stat for posix compatibility
#ifdef _WIN32
	#define stat _stat
#endif

#include "graph.hpp"

using std::string;

int main(int argc, char* argv[]) {
	//Make a list of all the graph files to use
	vector<string> graph_files;
	if (argc == 1) {
		graph_files.emplace_back("./graphs2.txt");
	} else {
		for (int i = 1; i < argc; i++) {
			struct stat buffer;
			// File exists and is a regular file
			if (stat(argv[i], &buffer) == 0 && (buffer.st_mode & S_IFREG) != 0) {
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
		Graph graph;
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
				std::string token;
				iss >> token;
				if (token == "graph") {
					if (init) {
						graph.bellman_ford(1);
					}
					graph = Graph();
					init = true;
				} else {
					fprintf(stderr, "Error - unrecognized token: %s\nLine number: %d\n", token.c_str(), lineNum);
					return 1;
				}
			} else if (command == "add") {
				std::string token;
				iss >> token;
				if (token == "vertex") {
					if (int vertex; iss >> vertex) {
						graph.add_vertex(vertex);
					} else {
						fprintf(stderr, "Error - failed to parse vertex id as int\nLine Number: %d\n", lineNum);
						return 1;
					}
				} else if (token == "edge") {
					char dash;
					if (int vertex0, vertex1, weight; iss >> vertex0 >> dash >> vertex1 >> weight && dash == '-') {
						graph.add_edge(vertex0, vertex1, weight);
					} else {
						fprintf(stderr, "Error - failed to parse vertex id as int\nLine Number: %d\n", lineNum);
						return 1;
					}
				} else {
					fprintf(stderr, "Error - unrecognized token: %s\nLine Number%d\n", token.c_str(), lineNum);
					return 1;
				}
			} else {
				fprintf(stderr, "Error - unrecognized token: %s\nLine Number %d\n", command.c_str(), lineNum);
				return 1;
			}
		}
		graph.bellman_ford(1);
		graph_file.close();
	}
	return 0;
}