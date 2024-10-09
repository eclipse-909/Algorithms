#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <vector>

#include "stack.hpp"
#include "queue.hpp"

using std::string;

//By the way, I like using i, ii, iii, iv for nested loop indices
//because i and j look too similar sometimes
//and Roman numerals make more sense for counting nest level.

void knuthShuffle(string* arr, const int size) {
	std::random_device rd;
	std::mt19937 gen(rd());
	//count backwards from the array
	for (int i = size - 1; i > 0; i--) {
		//pick a random index in the array and swap the element with the element at i
		std::uniform_int_distribution dist(0, i);
		const int ii = dist(gen);
		swap(arr[i], arr[ii]);
	}
}

//Time complexity O(n^2)
//Specifically n(n-1)/2
int selectionSort(string* arr, const int size) {
	int comparisons = 0;
	for (int i = 0; i < size - 1; i++) {
		int min = i;
		//find the smallest element in the array after the index i
		for (int ii = i + 1; ii < size; ii++) {
			if (arr[ii] < arr[min]) {
				min = ii;
			}
			comparisons++;
		}
		//swap the smallest element with the element at the current position
		if (min != i) {
			swap(arr[min], arr[i]);
		}
	}
	return comparisons;
}

//Time complexity O(n^2)
//Specifically ~ n(n-1)/4
int insertionSort(string* arr, const int size) {
	int comparisons = 0;
	for (int i = 1; i < size; i++) {
		const string key = arr[i];
		int ii = i - 1;
		//find where the current element should go in the sorted portion of the array
		while (ii >= 0 && key < arr[ii]) {
			comparisons++;
			arr[ii + 1] = arr[ii];
			ii--;
		}
		comparisons++;//A comparison is made when the while loop stops
		arr[ii + 1] = key;
	}
	return comparisons;
}

int mergeSortHelper(string* arr, const int left, const int right) {
	if (left >= right) {
		return 0;
	}
	int comparisons = 0;
	const int mid = left + (right - left) / 2;
	//merge sort on left side of array
	comparisons += mergeSortHelper(arr, left, mid);
	//merge sort on right side of array
	comparisons += mergeSortHelper(arr, mid + 1, right);
	//divide into left and right temp arrays
	const int leftArrLen = mid - left + 1;
	const int rightArrLen = right - mid;
	std::vector<string> leftArr = std::vector<string>(leftArrLen);
	std::vector<string> rightArr = std::vector<string>(rightArrLen);
	// string leftArr[leftArrLen];//the stack won't be happy about this
	// string rightArr[rightArrLen];
	for (int i = 0; i < leftArrLen; i++) {
		leftArr[i] = arr[left + i];
	}
	for (int i = 0; i < rightArrLen; i++) {
		rightArr[i] = arr[mid + 1 + i];
	}
	//compare and sort
	int i = 0, ii = 0, iii = left;
	while (i < leftArrLen && ii < rightArrLen) {
		comparisons++;
		if (leftArr[i] <= rightArr[ii]) {
			arr[iii] = leftArr[i];
			i++;
		} else {
			arr[iii] = rightArr[ii];
			ii++;
		}
		iii++;
	}
	comparisons++;//A comparison is made when the while loop stops
	//merge back together
	while (i < leftArrLen) {
		arr[iii] = leftArr[i];
		i++;
		iii++;
	}
	while (ii < rightArrLen) {
		arr[iii] = rightArr[ii];
		ii++;
		iii++;
	}
	return comparisons;
}

//Time complexity O(nlog2(n))
//Specifically it's slightly better on average
int mergeSort(string* arr, const int size) {
	return mergeSortHelper(arr, 0, size - 1);
}

int quickSortHelper(string* arr, const int left, const int right) {
	if (left >= right) {
		return 0;
	}
	int comparisons = 0;
	const string pivot = arr[right];
	int i = left - 1;
	//move all elements in sub-array with respect to the pivot
	for (int ii = left; ii < right; ii++) {
		if (arr[ii] < pivot) {
			i++;
			swap(arr[i], arr[ii]);
		}
		comparisons++;
	}
	swap(arr[i + 1], arr[right]);
	//divide into left and right arrays
	const int partitionIndex = i + 1;
	comparisons += quickSortHelper(arr, left, partitionIndex - 1);
	comparisons += quickSortHelper(arr, partitionIndex + 1, right);
	return comparisons;
}

//Time complexity ~ O(nlog2(n))
//Specifically it's a little worse on average
int quickSort(string* arr, const int size) {
	return quickSortHelper(arr, 0, size - 1);
}

int main() {
	constexpr int ARR_LEN = 666;

	string lines[ARR_LEN];

	//print palindromes
	if (std::ifstream file("../magicitems.txt"); file.is_open()) {
		string line;
		std::cout << "Palindromes:" << std::endl;
		int i = 0;
		int palindromes = 0;
		while (std::getline(file, line)) {
			assert(i != ARR_LEN && "Attempted to read more than the existing number of lines.");
			Stack<char> stack = Stack<char>();
			Queue<char> queue = Queue<char>();

			// create copy string that ignores case and space
			string copy = line;
			copy.erase(remove_if(copy.begin(), copy.end(), isspace), copy.end());
			std::transform(copy.begin(), copy.end(), copy.begin(), [](const unsigned char c) {
				return std::tolower(c);
			});

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
			lines[i] = line;//I was previously doing "lines[0] = line;" and it took me hours to figure out why it wasn't working
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
	std::cout << "Selection Sort Comparisons: " << selectionSort(lines, ARR_LEN) << std::endl;
	//use assertions to verify that all sorts produce the same output
	string linesCopy[ARR_LEN];
	for (int i = 0; i < ARR_LEN; i++) {
		linesCopy[i] = lines[i];
	}

	knuthShuffle(lines, ARR_LEN);
	std::cout << "Insertion Sort Comparisons: " << insertionSort(lines, ARR_LEN) << std::endl;
	for (int i = 0; i < ARR_LEN; i++) {
		assert(linesCopy[i] == lines[i] && "Arrays are not equal");
	}

	knuthShuffle(lines, ARR_LEN);
	std::cout << "Merge Sort Comparisons: " << mergeSort(lines, ARR_LEN) << std::endl;
	for (int i = 0; i < ARR_LEN; i++) {
		assert(linesCopy[i] == lines[i] && "Arrays are not equal");
	}

	knuthShuffle(lines, ARR_LEN);
	std::cout << "Quick Sort Comparisons: " << quickSort(lines, ARR_LEN) << std::endl;
	for (int i = 0; i < ARR_LEN; i++) {
		assert(linesCopy[i] == lines[i] && "Arrays are not equal");
	}

	return 0;
}