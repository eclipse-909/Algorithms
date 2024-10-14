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

Bucket::Bucket() : tag(Tag::Empty) {}
Bucket::~Bucket() {
	switch (tag) {
		case Tag::Empty:break;
		case Tag::Str:
			str.~string();
			break;
		case Tag::Queue:
			queue.~Queue();
	}
}

void Bucket::insert(const string& new_str) {
	switch (tag) {
		case Tag::Empty:
			tag = Tag::Str;
			new (&str) string(new_str);
			break;
		case Tag::Str: {
			std::string copy = std::move(str);
			str.~string();
			tag = Tag::Queue;
			new (&queue) Queue<string>();
			queue.enqueue(copy);
			queue.enqueue(new_str);
			break;
		}
		case Tag::Queue:
			queue.enqueue(new_str);
	}
}

int Bucket::search(const string& find_str) const {
	switch (tag) {
		case Tag::Empty:
			return -1; //not found
		case Tag::Str:
			assert(str == find_str);
			return 1;
		case Tag::Queue:
			return 1 + queue.search(find_str);
	}
	return -1; //unreachable
}