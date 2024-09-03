#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include "node.hpp"
#include <optional>

using std::optional;
using std::nullopt;

template <typename T>
struct Stack {
private:
	Node<T>* top;

public:
	Stack() : top(nullptr) {}

	void push(T item) {
		if (top == nullptr) {
			top = new Node<T> {item, nullptr};
			return;
		}
		Node<T>* newTop = new Node<T> {item, top};
		top = newTop;
	}

	optional<T> pop() {
		if (top == nullptr) {
			return nullopt;
		}
		T data = top->data;
		Node<T>* next = top->next;
		delete top;
		top = next;
		return data;
	}

	/// Returns nullptr if stack is empty.
	T* peek() {
		if (top == nullptr) {return nullptr;}
		return &top->data;
	}
};

#endif //STACK_HPP