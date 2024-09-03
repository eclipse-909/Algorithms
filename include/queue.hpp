#pragma once

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "node.hpp"
#include <optional>

using std::optional;
using std::nullopt;

template <typename T>
struct Queue {
private:
	Node<T>* front;

public:
	Queue() : front(nullptr) {}

	void enqueue(T item) {
		if (front == nullptr) {
			front = new Node<T> {item, nullptr};
			return;
		}
		Node<T>* curr = front;
		Node<T>* next = front->next;
        while (next != nullptr) {
			curr = next;
			next = next->next;
        }
        curr->next = new Node<T> {item, nullptr};
	}

	optional<T> dequeue() {
		if (front == nullptr) {
			return nullopt;
		}
		T data = front->data;
		Node<T>* next = front->next;
		delete front;
		front = next;
		return data;
	}

	/// Returns nullptr if the queue is empty.
	T* peek() {
		if (front == nullptr) {
			return nullptr;
		}
		return &front->data;
	}
};

#endif //QUEUE_HPP
