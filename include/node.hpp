#pragma once

#ifndef NODE_HPP
#define NODE_HPP

/// Node for linked-list-style data structures.
template <typename T> struct Node {T data; Node* next;};

#endif //NODE_HPP