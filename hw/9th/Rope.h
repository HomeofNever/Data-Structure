/*
You may add things to this .h file as needed. 
However keep in mind that Rope_provided.cpp will always be compiled in Submitty tests.
So you should not delete or change any methods that are implemented in Rope_provided.cpp
All your implementation should go in Rope_student.cpp
*/

#ifndef _ROPE_H
#define _ROPE_H

#include <string>
#include <vector>
#include <iostream>

class Node{
public:
	Node() : left{NULL}, right{NULL}, parent{NULL}, weight{0} {}
	Node* left;
	Node* right;
	Node* parent;
	int weight;
	std::string value = "";

	static int sum(Node * n);
	char getChar(unsigned int i) const;

	static Node * go_left_leaf(Node * begin);

	void split(int index);
};

class Rope;

class rope_iterator{
public:
	rope_iterator();
	rope_iterator(Node* p);
	rope_iterator& operator++();
	rope_iterator operator++(int);
	int weight() const;
	const std::string& value() const;
	friend class Rope;
	bool operator!=(const rope_iterator& it2) const;
private:
	Node* ptr_;
};

class Rope{
public:
	Rope();
	~Rope();
	Rope(Node* p);
	Rope(const Rope& r);
	Rope& operator= (const Rope& r);

	bool index(int i, char& c) const; //Get a single character
	void concat(const Rope& r); //Add the other string to me
	bool report(int i, int j, std::string& s) const; //Substring
	Rope& split(int i, Rope& rhs); //Split the string at index i into this (LHS) and a new Rope rhs

	rope_iterator begin() const;
	rope_iterator end() const;

	int size() const;
	void print(std::ostream& out) const;
	void print_strings(std::ostream& out) const;
	Node* expose_root() const;

private:
	void print(std::ostream& out, Node* head, int depth) const;
	void clear();
	void delete_node(Node *n);
	Node * copy_node(Node *n);

	void move(Node *n);
	int getIndex(int i, Node *& n) const;

private:
	int size_ = 0;
	Node *root = nullptr;

	void leaf_recursive(Node *n, int &total, std::string &s, int &i, int& j, int &l) const;
};

bool is_leaf(Node* p);

#endif
