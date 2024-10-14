#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <string>

#include "queue.hpp"

#define HASHTABLE_SIZE 250

using std::string;

enum class Tag {Empty, Str, Queue};
///Tagged union for either an empty bucket, one string, or a linked list of strings.
///I was going to use std::variant, but I can't link with it, so now I have to make my own tagged union.
struct Bucket {
	Tag tag;
	union {
		string str;
		Queue<string> queue;
	};

	Bucket();
	~Bucket();

	///If the bucket is empty, it will insert the new_str.
	///If the bucket has a string, it will turn it into a linked list with the old string + new_str.
	///If the bucket has a linked list, it will add new_str to the end.
	void insert(const string& new_str);

	///Returns how many comparisons were used to check if the string is in the bucket.
	///Returns <= 0 if not found.
	int search(const string& str) const;
};

struct HashTable {
	void insert(const string& new_str);

	///Returns how many comparisons were used to check if the string is in the hash table.
	///Returns 0 if it doesn't exist.
	int search(const string& find_str) const;

private:
	static int hash(string value);

	Bucket arr[HASHTABLE_SIZE];//hopefully the stack is cool with me dumping 10,000 bytes on it
};

#endif //HASHMAP_HPP