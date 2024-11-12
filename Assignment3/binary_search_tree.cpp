#include <cstdio>

#include "binary_search_tree.hpp"

Node::Node(const string data): data(data), left(nullptr), right(nullptr) {}

Node::~Node() {
	if (left != nullptr) {
		delete left;
	}
	if (right != nullptr) {
		delete right;
	}
}

BinarySearchTree::BinarySearchTree(): root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
	if (root != nullptr) {
		delete root;
	}
}

void BinarySearchTree::insert(const string data) {
	printf("Inserting %s - Root", data.c_str());
	if (root == nullptr) {
		root = new Node(data);
		printf("\n");
		return;
	}
	Node* curr = root;
	while (curr != nullptr) {
		if (data < curr->data) {
			printf(",L");
			if (curr->left == nullptr) {
				curr->left = new Node(data);
				break;
			}
			curr = curr->left;
		} else {
			printf(",R");
			if (curr->right == nullptr) {
				curr->right = new Node(data);
				break;
			}
			curr = curr->right;
		}
	}
	printf("\n");
}

void traverse_helper(Node* curr) {
	if (curr == nullptr) {return;}
	traverse_helper(curr->left);
	printf(" - %s", curr->data.c_str());
	traverse_helper(curr->right);
}

void BinarySearchTree::in_order_traverse() const {
	printf("In-order traversal");
	traverse_helper(root);
}

int BinarySearchTree::search(const string target) const {
	printf("Searching %s - Root", target.c_str());
	int comparisons = 0;
	Node* curr = root;
	while (curr != nullptr) {
		comparisons++;
		if (target == curr->data) {
			return comparisons;
		} else if (target < curr->data) {
			printf(",L");
			curr = curr->left;
		} else {
			printf(",R");
			curr = curr->right;
		}
	}
	return comparisons * -1;
}