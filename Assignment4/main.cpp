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
#include "spice.hpp"

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

	//Spice heist
	std::ifstream spice_file("spice.txt");
	if (!spice_file.is_open()) {
		fprintf(stderr, "Unable to open spice.txt\n");
		return 1;
	}
	int lineNum = 0;
	vector<Spice> spices;
	vector<int> knapsacks;//int represents the capacity of the knapsack
	while (std::getline(spice_file, line)) {
		lineNum++;
		//ignore comments
		if (size_t pos = line.find("--"); pos != std::string::npos) {
			line = line.substr(0, pos);
		}
		//skip empty lines
		if (line.empty()) {continue;}

		//parse tokens
		//this was annoying so please don't change the syntax for other spice files during testing
		std::istringstream iss(line);
		string command;
		iss >> command;
		if (command == "spice") {
			string token;
			string name;
			float total_price;
			int quantity;
			while (std::getline(iss, token, ';')) {
				std::istringstream pair_stream(token);
				string key, value;

				if (!std::getline(pair_stream, key, '=')) {
					fprintf(stderr, "Error - Missing '=' in line %d\n", lineNum);
					return 1;
				}

				// Trim key and value
				key.erase(0, key.find_first_not_of(" \t"));
				key.erase(key.find_last_not_of(" \t") + 1);
				if (!std::getline(pair_stream, value)) {
					fprintf(stderr, "Error - Missing value in line %d\n", lineNum);
					return 1;
				}
				value.erase(0, value.find_first_not_of(" \t"));
				value.erase(value.find_last_not_of(" \t") + 1);

				if (key == "name") {
					name = value;
					if (name.empty()) {
						fprintf(stderr, "Error - Missing name in line %d\n", lineNum);
						return 1;
					}
				} else if (key == "total_price") {
					try {
						total_price = std::stof(value);
					} catch (...) {
						fprintf(stderr, "Error - Invalid total_price in line %d\n", lineNum);
						return 1;
					}
				} else if (key == "qty") {
					try {
						quantity = std::stoi(value);
					} catch (...) {
						fprintf(stderr, "Error - Invalid qty in line %d\n", lineNum);
						return 1;
					}
				} else {
					fprintf(stderr, "Error - Unknown key '%s' in line %d\n", key.c_str(), lineNum);
					return 1;
				}
			}
			spices.emplace_back(Spice{name, total_price, quantity});
		} else if (command == "knapsack") {
			string capacity;
			char eq;
			if (int cap; iss >> capacity >> eq >> cap && capacity == "capacity" && eq == '=') {
				knapsacks.emplace_back(cap);
			} else {
				fprintf(stderr, "Error - Failed to parse knapsack capacity\nLine Number %d\n", lineNum);
				return 1;
			}
		} else {
			fprintf(stderr, "Error - unrecognized token: %s\nLine Number %d\n", command.c_str(), lineNum);
			return 1;
		}
	}
	for (const Spice& s : spices) {
		printf("spice name = %s; total_price = %.1f; qty = %d;\n", s.name.c_str(), s.total_price, s.quantity);
	}
	for (const int cap : knapsacks) {
		printf("Knapsack capacity: %d\n", cap);
	}

	return 0;
}