#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include "stack.hpp"
#include "queue.hpp"

void knuthShuffle(std::string* arr, const int size) {
	std::random_device rd;
	std::mt19937 gen(rd());
	for (int i = size - 1; i > 0; i--) {
		std::uniform_int_distribution dist(0, i);
		const int j = dist(gen);
		std::swap(arr[i], arr[j]);
	}
}

int selectionSort(std::string* arr, const int size) {
	//TODO
	//remember to return the number of comparisons
	return 0;
}

int insertionSort(std::string* arr, const int size) {
	//TODO
	//remember to return the number of comparisons
	return 0;
}

int mergeSort(std::string* arr, const int size) {
	//TODO
	//remember to return the number of comparisons
	return 0;
}

int quickSort(std::string* arr, const int size) {
	//TODO
	//remember to return the number of comparisons
	return 0;
}

int main() {
	/* Instructions:
	 *
	 * Check palindromes:
	 *
	 * Read lines from magicitems.txt one at a time.
	 * Ignore capitalization and spaces in each line.
	 * Push/enqueue each character in a line to a stack/queue.
	 * Pop/dequeue each character from the stack/queue.
	 * If all characters are the same when removing, it is a palindrome, so print the line.
	 *
	 * Sorts:
	 *
	 * Sort the lines in magicitems.txt using each of the following sorts.
	 * Make sure to use Knuth shuffle on each array before sorting.
	 * Selection
	 * Insertion
	 * Merge
	 * Quick
	 */

	constexpr int ARR_LEN = 666;

	std::string lines[ARR_LEN];

	//print palindromes
	if (std::ifstream file("./magicitems.txt"); file.is_open()) {
		std::string line;
		std::cout << "Palindromes:" << std::endl;
		int i = 0;
		int palindromes = 0;
		while (std::getline(file, line)) {
			if (i == ARR_LEN) {throw std::out_of_range("Attempted to read more than the existing number of lines.");}//this line shouldn't be necessary
			Stack<char> stack = Stack<char>();
			Queue<char> queue = Queue<char>();

			// create copy string that ignores case and space
			std::string copy = line;
			std::ranges::transform(copy, copy.begin(), [](const unsigned char c) { return std::tolower(c); });
			std::erase(copy, ' ');

			//add characters
			for (const char c : copy) {
				stack.push(c);
				queue.enqueue(c);
			}
			// The queue should have same length and should become empty at the same time as the stack.
			bool palindrome = true;
			while (!stack.isEmpty()) {
				//remove characters
				if (stack.pop() != queue.dequeue()) {
					palindrome = false;
					break;
				}
			}
			//print if palindrome
			if (palindrome) {
				std::cout << line << std::endl;
				palindromes++;
			}
			lines[0] = line;
			i++;
		}
		file.close();
		std::cout << "Lines read: " << i << std::endl;
		std::cout << "Palindromes: " << palindromes << std::endl;
	} else {
		std::cerr << "Unable to open file." << std::endl;
	}

	//sort lines
	knuthShuffle(lines, ARR_LEN);
	std::cerr << "Selection Sort Comparisons: " << selectionSort(lines, ARR_LEN) << std::endl;

	knuthShuffle(lines, ARR_LEN);
	std::cerr << "Insertion Sort Comparisons: " << insertionSort(lines, ARR_LEN) << std::endl;

	knuthShuffle(lines, ARR_LEN);
	std::cerr << "Merge Sort Comparisons: " << mergeSort(lines, ARR_LEN) << std::endl;

	knuthShuffle(lines, ARR_LEN);
	std::cerr << "Quick Sort Comparisons: " << quickSort(lines, ARR_LEN) << std::endl;

	return 0;
}