#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <string>
#include <cstdint>

#include "queue.hpp"

#define HASHTABLE_SIZE 250

using std::string;

enum class Tag : uint8_t {Empty, Str, LinkedList};
///Size of string
union Value {
	string str;
	Queue<string> queue;

	///Initializes linkedList to nullptr
	Value();
	///Initializes str to value
	explicit Value(const string& value);
	///This destructor doesn't do anything.
	///Memory is freed from Value when the Bucket destructor is called because only Bucket has access to the tag.
	///This destructor needs to be declared to satisfy the compiler.
	~Value();

	///Unions don't have an assignment operator by default, so this function uses the tag to determine how to assign the new value.
	void set(Value new_value, Tag this_tag, Tag new_tag);

	///Creates a linked list with str and the given value.
	///YOU MUST CHECK IF bucket.tag == Tag::Str BEFORE CALLING THIS FUNCTION.
	void insert(const string& new_str);
};
///Tagged union to either store a single string or a linked list of strings
struct Bucket {
	Tag tag;
	Value value;

	Bucket();
	~Bucket();

	void insert(const string& new_str);
	///Returns how many comparisons were used to check if the string is in the hash table.
	///Returns -1 if it doesn't exist.
	int search(const string& str) const;
};

struct HashTable {
	HashTable();
	~HashTable();

	void insert(const string& new_str);
	///Returns how many comparisons were used to check if the string is in the hash table.
	///Returns -1 if it doesn't exist.
	int search(const string& find_str) const;

private:
	static int hash(string value);

	Bucket arr[HASHTABLE_SIZE];
};

#endif //HASHMAP_HPP