//I don't know why, but I can't link with <iostream>
#include <cstdio>
#include <algorithm>
#include <cctype>

#include "hashtable.hpp"

HashTable::HashTable() {}

HashTable::~HashTable() {
	for (const Bucket& bucket : arr) {
    	bucket.~Bucket();
	}
}

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

Value::Value() {}
///GDB says I am writing to the heap after the memory has been freed. I have no idea why, or if it affects anything.
Value::Value(const string& value) : str(value) {}
Value::~Value() {}
void Value::set(const Value new_value, Tag this_tag, Tag new_tag) {
	switch (this_tag) {
		case Tag::Empty:
			break;
		case Tag::Str:
			str.~string();
			break;
		case Tag::LinkedList:
			queue.~Queue();
	}
	switch (new_tag) {
		case Tag::Empty:
			break;
		case Tag::Str:
			str = new_value.str;
			break;
		case Tag::LinkedList:
			queue = new_value.queue;
	}
}
void Value::insert(const string& new_str) {
	Queue<string> q = Queue<string>();
    q.enqueue(str);
	str.~string();
    q.enqueue(new_str);
    queue = q;
}

Bucket::Bucket() : tag(Tag::Empty), value(Value()) {}
Bucket::~Bucket() {
	switch (tag) {
		case Tag::Empty:
			break;
		case Tag::Str:
			value.str.~string();
			break;
		case Tag::LinkedList:
			value.queue.~Queue();
	}
}

void Bucket::insert(const string& new_str) {
	switch (tag) {
    	case Tag::Empty:
        	tag = Tag::Str;
          	value.set(Value(new_str), Tag::Empty, Tag::Str);
        	break;
		case Tag::Str:
            tag = Tag::LinkedList;
            value.insert(new_str);
            break;
		case Tag::LinkedList:
            value.queue.enqueue(new_str);
	}
}

///Returns how many comparisons were used to check if the string is in the bucket.
///Returns 1 if the bucket is empty or only has 1 string.
///Returns -1 if it doesn't exist.
int Bucket::search(const string& find_str) const {
	printf("Bucket tag: %d\n", tag);
	switch (tag) {
		case Tag::Empty:
            return 1;
		case Tag::Str:
            return 1;
		case Tag::LinkedList:
            printf("Queue length: %d\n", value.queue.length());
			return value.queue.search(find_str);
	}
    return 0;
}