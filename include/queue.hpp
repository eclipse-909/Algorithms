#pragma once

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "node.hpp"
#include <optional>

using std::optional;
using std::nullopt;

/// First in, first out data structure with linked-list implementation.
template <typename T>
struct Queue {
private:
	Node<T>* head;
	Node<T>* tail;

public:
	/// Creates an empty queue.
	Queue() : head(nullptr), tail(nullptr) {}

	/// Deallocates all allocated nodes from the heap.
	~Queue() {
		while (head != nullptr) {
			Node<T>* next = head->next;
			delete head;
			head = next;
		}
	}

	/// Adds the item to the tail of the queue.
	void enqueue(T item) {
		if (tail == nullptr) {
			head = tail = new Node<T>(item);
			return;
		}
		tail->next = new Node<T>(item);
		tail = tail->next;
	}

	/// Removes the item from the head of the queue.
	/// Deletes data from the heap and copies the data into the stack.
	optional<T> dequeue() {
		if (head == nullptr) {
			return nullopt;
		}
		T data = head->data;
		Node<T>* next = head->next;
		delete head;
		head = next;
		return data;
	}

	/// Returns nullptr if the queue is empty, otherwise it views the item at the head of the queue without removing it.
	T* peek() {
		if (head == nullptr) {
			return nullptr;
		}
		return &head->data;
	}

	bool isEmpty() {
		return head == nullptr;
	}
};

#endif //QUEUE_HPP
