#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <cassert>
#include <vector>

#include "stack.hpp"
#include "queue.hpp"

void knuthShuffle(std::string* arr, const int size) {
	std::random_device rd;
	std::mt19937 gen(rd());
	for (int i = size - 1; i > 0; i--) {
		std::uniform_int_distribution dist(0, i);
		const int ii = dist(gen);
		std::swap(arr[i], arr[ii]);
	}
}

int selectionSort(std::string* arr, const int size) {
	int comparisons = 0;
	for (int i = 0; i < size - 1; i++) {
		int min = i;
		//By the way, I like using i, ii, iii, iv for nested loop indices
		//because i and j look too similar sometimes
		//and Roman numerals make more sense for counting nest level.
		for (int ii = i + 1; ii < size; ii++) {
			if (arr[ii] < arr[min]) {
				min = ii;
			}
			comparisons++;
		}
		if (min != i) {
			swap(arr[min], arr[i]);
		}
	}
	return comparisons;
}

//The number of comparisons in the insertion sort changes each time the exe is run.
//I can't tell if this is due to randomness in the shuffle, and the insertion sort does more or less
//comparisons based on how shuffled the array already was, or if this is undefined behavior.
//The other sorting algorithms have repeatable outputs despite the shuffling.
//Maybe that's inherent to the algorithm, but I'm not sure.
//All algorithms are followed by an assertion to make sure they all produce the same output,
//and all of them pass the assertion. I looked at multiple sources to see how they implemented the
//insertion sort and nothing appears to be incorrect.
int insertionSort(std::string* arr, const int size) {
	int comparisons = 0;
	for (int i = 1; i < size; i++) {
		const std::string key = arr[i];
		int ii = i - 1;
		while (ii >= 0 && arr[ii] > key) {
			arr[ii + 1] = arr[ii];
			ii--;
			comparisons++;
		}
		arr[ii + 1] = key;
	}
	return comparisons;
}

int mergeSort(std::string* arr, const int left, const int right) {
	int comparisons = 0;
	if (left >= right) {
		return 0;
	}
	const int mid = left + (right - left) / 2;
	comparisons += mergeSort(arr, left, mid);
	comparisons += mergeSort(arr, mid + 1, right);
	//create left and right temp arrays
	const int leftArrLen = mid - left + 1;
	const int rightArrLen = right - mid;
	std::string leftArr[leftArrLen], rightArr[rightArrLen];
	for (int i = 0; i < leftArrLen; i++) {
		leftArr[i] = arr[left + i];
	}
	for (int i = 0; i < rightArrLen; i++) {
		rightArr[i] = arr[mid + 1 + i];
	}
	//divide, conquer, and merge
	int i = 0, ii = 0, iii = left;
	while (i < leftArrLen && ii < rightArrLen) {
		if (leftArr[i] <= rightArr[ii]) {
			arr[iii] = leftArr[i];
			i++;
		} else {
			arr[iii] = rightArr[ii];
			ii++;
		}
		iii++;
		comparisons++;
	}
	while (i < leftArrLen) {
		arr[iii] = leftArr[i];
		i++;
		iii++;
		comparisons++;//does this count as a comparison?
	}
	while (ii < rightArrLen) {
		arr[iii] = rightArr[ii];
		ii++;
		iii++;
		comparisons++;//does this count as a comparison?
	}
	return comparisons;
}

int mergeSort(std::string* arr, const int size) {
	return mergeSort(arr, 0, size - 1);
}

int quickSort(std::string* arr, const int low, const int high) {
	int comparisons = 0;
	if (low < high) {
		const int pivot = high;
		int i = low - 1;
		for (int ii = low; ii <= high - 1; ii++) {
			if (arr[ii] < arr[pivot]) {
				i++;
				std::swap(arr[i], arr[ii]);
			}
			comparisons++;
		}
		std::swap(arr[i + 1], arr[high]);
		const int partitionIndex = i + 1;
		comparisons += quickSort(arr, low, partitionIndex - 1);
		comparisons += quickSort(arr, partitionIndex + 1, high);
	}
	return comparisons;
}

int quickSort(std::string* arr, const int size) {
	return quickSort(arr, 0, size - 1);
}

int main() {
	constexpr int ARR_LEN = 666;

	std::string lines[ARR_LEN];

	//print palindromes
	if (std::ifstream file("./magicitems.txt"); file.is_open()) {
		std::string line;
		std::cout << "Palindromes:" << std::endl;
		int i = 0;
		int palindromes = 0;
		while (std::getline(file, line)) {
			assert(i != ARR_LEN && "Attempted to read more than the existing number of lines.");
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
	//Comparisons: 221,445
	std::cout << "Selection Sort Comparisons: " << selectionSort(lines, ARR_LEN) << std::endl;
	//use assertions to verify that all sorts produce the same output
	std::string linesCopy[ARR_LEN];
	for (int i = 0; i < ARR_LEN; i++) {
		linesCopy[i] = lines[i];
	}

	knuthShuffle(lines, ARR_LEN);
	//Comparisons: variable; a few hundred on average
	std::cout << "Insertion Sort Comparisons: " << insertionSort(lines, ARR_LEN) << std::endl;
	for (int i = 0; i < ARR_LEN; i++) {
		assert(linesCopy[i] == lines[i] && "Arrays are not equal");
	}

	knuthShuffle(lines, ARR_LEN);
	//Comparisons: 6,302
	std::cout << "Merge Sort Comparisons: " << mergeSort(lines, ARR_LEN) << std::endl;
	for (int i = 0; i < ARR_LEN; i++) {
		assert(linesCopy[i] == lines[i] && "Arrays are not equal");
	}

	knuthShuffle(lines, ARR_LEN);
	//Comparisons: 221,445
	std::cout << "Quick Sort Comparisons: " << quickSort(lines, ARR_LEN) << std::endl;
	for (int i = 0; i < ARR_LEN; i++) {
		assert(linesCopy[i] == lines[i] && "Arrays are not equal");
	}

	return 0;
}