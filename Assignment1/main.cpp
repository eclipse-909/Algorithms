#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

int main() {
	std::cout << "Numbers inserted 0-9" << std::endl;

	Stack<int> stack = Stack<int>();
	Queue<int> queue = Queue<int>();
	for (int i = 0; i < 10; i++) {
		stack.push(i);
		queue.enqueue(i);
	}

	std::cout << "Stack:" << std::endl;
	for (int i = 0; i < 10; i++) {
		optional<int> sNum = stack.pop();
		if (sNum.has_value()) {
			std::cout << sNum.value();
		} else {
			std::cout << "nullopt";
		}
	}

	std::cout << std::endl << "Queue:" << std::endl;
	for (int i = 0; i < 10; i++) {
		optional<int> qNum = queue.dequeue();
		if (qNum.has_value()) {
			std::cout << qNum.value();
		} else {
			std::cout << "nullopt";
		}
	}

	return 0;
}