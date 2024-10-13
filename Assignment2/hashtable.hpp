#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <string>
#include <variant>

#include "queue.hpp"

#define HASHTABLE_SIZE 250

using std::string;

///Tagged union to either store a single string or a linked list of strings
struct Bucket {
	using BucketVariant = std::variant<std::monostate, std::string, Queue<std::string>>;

	BucketVariant variant;

	///If the bucket is empty, it will insert the new_str.
	///If the bucket has a string, it will turn it into a linked list with the old string + new_str.
	///If the bucket has a linked list, it will add new_str to the end.
	void insert(const string& new_str);
	///Returns how many comparisons were used to check if the string is in the bucket.
	///Returns 1 if the bucket is empty or only has 1 string.
	///Panics if it doesn't exist.
	int search(const string& str) const;
};

struct HashTable {
	void insert(const string& new_str);
	///Returns how many comparisons were used to check if the string is in the hash table.
	///Returns 0 if it doesn't exist.
	int search(const string& find_str) const;

private:
	static int hash(string value);

	Bucket arr[HASHTABLE_SIZE];
};

#endif //HASHMAP_HPP