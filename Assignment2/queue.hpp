#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "node.hpp"

///First in, first out data structure with linked-list implementation.
///For this project, this queue will be used more like a regular linked list,
///and has some linked list methods instead of queue methods.
template<typename T> struct Queue {
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
	void enqueue(const T& item) {
		if (tail == nullptr) {
			head = tail = new Node<T>(item);
			return;
		}
		tail->next = new Node<T>(item);
		tail = tail->next;
	}

	///Returns how many comparisons were used to check if the target is in the queue.
	///Returns -1 if it doesn't exist.
	int search(const T& target) const {
		int comparisons = 0;
		Node<T>* curr = head;
		while (curr != nullptr) {
			comparisons++;
			if (curr->data == target) {
				return comparisons;
			}
			curr = curr->next;
		}
		return -1;
	}

	int length() const {
		int length = 0;
		Node<T>* curr = head;
		while (curr != nullptr) {
			length++;
			curr = curr->next;
		}
		return length;
	}
};

#endif //QUEUE_HPP