#include <cstdio>
#include <fstream>

#include "binary_search_tree.hpp"

int main() {
	//Read lines from magicitems.txt and insert into BST
	std::ifstream magicitems("../magicitems.txt");
	if (!magicitems.is_open()) {
		printf("Unable to open magicitems.txt\n");
		return 1;
	}
	BinarySearchTree bst = BinarySearchTree();
	string line;
	while (std::getline(magicitems, line)) {
		bst.insert(line);
	}
	magicitems.close();

	//print items in order
	bst.in_order_traverse();

	//Read lines from magicitems-find-in-bst.txt and search BST
	std::ifstream file("./magicitems-find-in-bst.txt");
	if (!file.is_open()) {
		printf("Unable to open magicitems-find-in-bst.txt\n");
		return 1;
	}
	int comparisons = 0;
	int count = 0;
	while (std::getline(file, line)) {
		int c = bst.search(line);
		if (c < 0) {
			printf(", Not found after %d comparisons\n", c);
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