#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

void stack_and_queue() {
	std::cout << "Numbers inserted 0-9" << std::endl;

	//Add 0-9 to stack and queue
	Stack<int> stack = Stack<int>();
	Queue<int> queue = Queue<int>();
	for (int i = 0; i < 10; i++) {
		stack.push(i);
		queue.enqueue(i);
	}

	//Pop and print each item from stack
	std::cout << "Stack:" << std::endl;
	for (int i = 0; i < 10; i++) {
		if (optional<int> sNum = stack.pop(); sNum.has_value()) {
			std::cout << sNum.value();
		} else {
			std::cout << "nullopt";
		}
	}

	//Dequeue and print each item from queue
	std::cout << std::endl << "Queue:" << std::endl;
	for (int i = 0; i < 10; i++) {
		if (optional<int> qNum = queue.dequeue(); qNum.has_value()) {
			std::cout << qNum.value();
		} else {
			std::cout << "nullopt";
		}
	}
}

int main() {
	stack_and_queue();
	return 0;
}