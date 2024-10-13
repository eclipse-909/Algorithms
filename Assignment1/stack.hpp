#ifndef STACK_HPP
#define STACK_HPP

#include "node.hpp"
#include <optional>

using std::optional;
using std::nullopt;

/// Last in, first out data structure with linked-list implementation.
template <typename T>
struct Stack {
private:
	Node<T>* top;

public:
	/// Creates an empty stack.
	Stack() : top(nullptr) {}

	/// Deallocates all allocated nodes from the heap.
	~Stack() {
		while (top != nullptr) {
			Node<T>* next = top->next;
			delete top;
			top = next;
		}
	}

    /// Adds the item on top of the stack.
	void push(T item) {
		if (top == nullptr) {
			top = new Node<T>(item);
			return;
		}
		Node<T>* newTop = new Node<T> {item, top};
		top = newTop;
	}

	/// Removes the item from the top of the stack.
	/// Deletes data from the heap and copies the data into the stack.
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

	/// Returns nullptr if stack is empty, otherwise it views the item on the top of the stack without removing it.
	T* peek() {
		if (top == nullptr) {return nullptr;}
		return &top->data;
	}

	bool isEmpty() {
		return top == nullptr;
	}
};

#endif //STACK_HPP