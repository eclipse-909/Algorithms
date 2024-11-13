#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <string>

using std::string;

struct Node {
	string data;
    Node* left;
    Node* right;

	explicit Node(string data);
	~Node();
};

struct BinarySearchTree {
	Node* root;

	BinarySearchTree();
	~BinarySearchTree();

	void insert(string data);
	void depth_first_traverse() const;
	int search(string target) const;
};

#endif //BINARY_SEARCH_TREE_HPP