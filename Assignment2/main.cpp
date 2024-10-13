//I don't know why, but I can't link with <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <random>

#include "hashtable.hpp"

#define NUM_LINES 666
#define NUM_RAND 42

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

int main() {
	//Read lines from magicitems.txt
	std::ifstream file("../magicitems.txt");
	if (!file.is_open()) {
		printf("Unable to open file\n");
		return 1;
	}
	string lines[NUM_LINES];
	string line;
	int index = 0;
	while (std::getline(file, line)) {
		lines[index] = line;
		index++;
	}
	file.close();

	//Get 42 random items
	string rand42[NUM_RAND];
	knuthShuffle(lines, NUM_LINES);
	for (int i = 0; i < NUM_RAND; i++) {
		rand42[i] = lines[i];
	}
	mergeSort(lines, NUM_LINES);

	//Linear search
	int comparisons = 0;
	int totalComparisons = 0;
	for (const string& rand : rand42) {
		for (const string& ln : lines) {
			comparisons++;
			if (rand == ln) {
				break;//It's assumed that the target string will be found
			}
		}
		printf("Linear search comparisons for %s: %d\n", rand.c_str(), comparisons);
		totalComparisons += comparisons;
		comparisons = 0;
	}
	printf("Linear search average comparisons: %.2f\n", static_cast<float>(totalComparisons) / static_cast<float>(NUM_RAND));

	//Binary search
	//That's right, I did it without recursion. Stay mad Haskell developers!
	totalComparisons = 0;
	int left, right, mid;
	for (const string& rand : rand42) {
		left = 0;
		right = NUM_LINES - 1;
		while (left < right) {
			comparisons++;
			mid = (left + right) / 2;
			if (rand == lines[mid]) {
				break;//It's assumed that the target string will be found
			}
			if (rand < lines[mid]) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}
		printf("Binary search comparisons for %s: %d\n", rand.c_str(), comparisons);
		totalComparisons += comparisons;
		comparisons = 0;
	}
	printf("Binary search average comparisons: %.2f\n", static_cast<float>(totalComparisons) / static_cast<float>(NUM_RAND));

	//hash table
	HashTable table = HashTable();
	for (const string& ln : lines) {
		table.insert(ln);
	}
	//BUG sometimes the bucket uses a queue when there is only one string in the queue.
	//BUG Queue::search always returns 0. It never finds the target item.
	//BUG seg fault in HashTable::search.
	for (const string& str : rand42) {
		printf("HashTable retrieval comparisons for %s: %d\n", str.c_str(), table.search(str));
	}

	return 0;
}