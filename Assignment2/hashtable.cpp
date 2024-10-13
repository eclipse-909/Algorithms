//I don't know why, but I can't link with <iostream>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cassert>

#include "hashtable.hpp"

void HashTable::insert(const string& new_str) {arr[hash(new_str)].insert(new_str);}
int HashTable::search(const string& find_str) const {return arr[hash(find_str)].search(find_str);}

int HashTable::hash(string value) {
	int letterTotal = 0;
	std::transform(value.begin(), value.end(), value.begin(), [](const unsigned char c){return std::toupper(c);});
	for (int i = 0; i < value.length(); i++) {
		letterTotal += static_cast<int>(value.at(i));
	}
	return letterTotal % HASHTABLE_SIZE;
}

void Bucket::insert(const string& new_str) {
	if (std::holds_alternative<std::monostate>(variant)) {
		variant = new_str;
	} else if (std::holds_alternative<string>(variant)) {
		string copy = std::get<string>(variant);
		variant = Queue<string>();
		std::get<Queue<string>>(variant).enqueue(copy);
		std::get<Queue<string>>(variant).enqueue(new_str);
	} else if (std::holds_alternative<Queue<string>>(variant)) {
		std::get<Queue<string>>(variant).enqueue(new_str);
	}
}

int Bucket::search(const string& find_str) const {
	if (std::holds_alternative<std::monostate>(variant)) {
		return 1;
	} else if (std::holds_alternative<string>(variant)) {
		assert(std::get<string>(variant) == find_str);
		return 1;
	} else if (std::holds_alternative<Queue<string>>(variant)) {
		printf("Queue length: %d\n", std::get<Queue<string>>(variant).length());
		int comparisons = std::get<Queue<string>>(variant).search(find_str);
        assert(comparisons != -1);//Assume the item exists
		return 1 + comparisons;//get + chaining
	}
    return -1;//satisfy the compiler
}