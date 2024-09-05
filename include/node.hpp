#pragma once

#ifndef NODE_HPP
#define NODE_HPP

/// Node for linked-list-style data structures.
/// Data structures are responsible for cleaning up resources used by Nodes.
template <typename T> struct Node {
	T data;
	Node* next;

	explicit Node(T item) : data(item), next(nullptr) {}

	Node(T item, Node<T>* next) : data(item), next(next) {}
};

#endif //NODE_HPP