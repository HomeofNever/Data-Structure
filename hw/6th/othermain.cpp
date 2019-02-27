//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN
//       CHANGES TO MoreTests()
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>

#include "unrolled.h"

// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true iff the lists are the same size, and contain the same
// elements in the same order.
template <class T>
bool SAME(UnrolledLL<T>& a, std::list<T> &b) {
  if (a.size() != b.size()) return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end()) {
    if (*a_iter != *b_iter) return false;
    a_iter++;
    b_iter++;
  }
  assert (a_iter == a.end() && b_iter == b.end());
  return true;
}


// ===================================================================
void BasicTests();
void MoreTests();

int main() {
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}


// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    a.push_back(i);
    b.push_back(i);
  }

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(a,b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert (a.size() == 20);
  assert (a.front() == 10);
  assert (a.back() == 29);
  a.pop_front();
  b.pop_front();
  assert (a.size() == 19);
  assert (a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert (a.size() == 18);
  assert (a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert (SAME(a,b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  b.pop_back();
  a.print(std::cout);

  assert (a.size() == 12);
  assert (a.front() == 16);
  assert (a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 16);
  assert (a.front() == 93);
  assert (SAME(a,b));

  // erase the multiples of 3
  std::cout <<"erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 3 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 3 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 10);
  assert (SAME(a,b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = a.insert(itr,77);
      itr++;
    }
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = b.insert(itr,77);
      itr++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 14);
  assert (SAME(a,b));

  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 17) {
      itr = a.insert(itr,88);
      itr++;
    }
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 17) {
      itr = b.insert(itr,88);
      itr++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 15);
  assert (SAME(a,b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 9);
  assert (SAME(a,b));

}


// ===================================================================
void MoreTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.

  std::cout << std::endl << "******* Starting more tests **********" << std::endl << std::endl;
  UnrolledLL<int> a;
  UnrolledLL<int> c;
  std::list<int> b;

  std::cout << "erase on list of one element" << std::endl;
  // testing empty function
  assert(a.empty() == true);
  assert(a.size() == 0);

  a.push_front(80);
  b.push_front(80);
  a.print(std::cout);
  a.erase(a.begin());
  b.erase(b.begin());

  assert(a.empty() == true);
  assert(a.size() == 0);

  std::cout << std::endl << "insert on empty list" << std::endl;
  a.insert(a.begin(), 60);
  b.insert(b.begin(), 60);

  a.print(std::cout);
  assert(a.empty() == false);
  assert(a.size() == 1);
  assert (SAME(a,b));

  a.erase(a.begin());
  b.erase(b.begin());

  std::cout << std::endl << "begin some more normal tests" << std::endl;
  for (int i = 1; i < 13; ++i) {
    a.push_back(i);
    b.push_back(i);
  }

  a.print(std::cout);

  // regular push_back and push_front
  a.push_back(20);
  a.push_back(21);
  a.push_back(22);
  a.push_back(23);
  a.push_back(24);
  b.push_back(20);
  b.push_back(21);
  b.push_back(22);
  b.push_back(23);
  b.push_back(24);
  a.push_front(30);
  a.push_front(31);
  a.push_front(32);
  a.push_front(33);
  a.push_front(34);
  b.push_front(30);
  b.push_front(31);
  b.push_front(32);
  b.push_front(33);
  b.push_front(34);
  assert(SAME(a,b));
  a.print(std::cout);

  // making nodes with one element
  std::cout << std::endl << "making nodes with one element" << std::endl;
  a.push_back(25);
  a.push_back(26);
  a.push_front(35);
  a.push_front(36);
  b.push_back(25);
  b.push_back(26);
  b.push_front(35);
  b.push_front(36);
  assert(a.front() == 36);
  assert(a.back() == 26);
  assert(SAME(a,b));

  a.print(std::cout);

  // erasing node with one element, and testing ability for head_ to update
  std::cout  << "testing erase on one element and updating head_" << std::endl;
  a.erase(a.begin());
  b.erase(b.begin());
  a.erase(a.begin());
  b.erase(b.begin());

  a.print(std::cout);

  std::cout <<"erase the multiples of 2, which will also test erase on one element and updating tail_" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 2 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
    a.print(std::cout);
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 2 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 11);
  assert (SAME(a,b));

  std::cout << std::endl << "testing pop_back, pop_front on only one element in list" << std::endl;
  c.push_back(100);
  c.pop_back();
  assert(c.empty() == true);
  assert(c.size() == 0);
  c.push_front(100);
  c.pop_front();
  assert(c.empty() == true);
  assert(c.size() == 0);

  std::cout << std::endl << "testing with int is good! Now testing other types, as well as other functions" << std::endl;

  UnrolledLL<char> d;
  std::list<char> e;
  // regular push_back and push_front
  d.push_back('q');
  d.push_back('w');
  d.push_back('e');
  d.push_back('r');
  d.push_back('t');
  e.push_back('q');
  e.push_back('w');
  e.push_back('e');
  e.push_back('r');
  e.push_back('t');
  d.push_front('a');
  d.push_front('s');
  d.push_front('d');
  d.push_front('f');
  d.push_front('g');
  e.push_front('a');
  e.push_front('s');
  e.push_front('d');
  e.push_front('f');
  e.push_front('g');
  assert(SAME(d,e));
  d.print(std::cout);

  // making nodes with one element
  std::cout << std::endl << "making nodes with one element" << std::endl;
  d.push_back('.');
  d.push_front('@');
  d.push_front('#');
  d.push_front('=');
  e.push_back('.');
  e.push_front('@');
  e.push_front('#');
  e.push_front('=');
  assert(d.front() == '=');
  assert(d.back() == '.');
  assert(SAME(d,e));

  d.print(std::cout);

  // erasing node with one element, and testing ability for head_ to update
  std::cout  << "testing erase on one element and updating head_" << std::endl;
  d.erase(d.begin());
  e.erase(e.begin());
  d.erase(d.begin());
  e.erase(e.begin());

  assert(SAME(d,e));
  d.print(std::cout);

  // Calling assignment operator, testing copy and clear as well
  std::cout  << std::endl << "testing assignment, copy, and destroy functions" << std::endl;
  UnrolledLL<int> f;
  f.push_back(1000);
  std::cout << "BEFORE: unrolled list - a" << std::endl;
  a.print(std::cout);
  std::cout << "BEFORE: unrolled list - d" << std::endl;
  f.print(std::cout);
  // assignment
  f = a;
  std::cout << std::endl <<"AFTER: unrolled list - a" << std::endl;
  a.print(std::cout);
  std::cout << "AFTER: unrolled list - d" << std::endl;
  f.print(std::cout);
  assert(a.size() == f.size());

  // editing on list f to make sure list was properly copied
  std::cout << std::endl << "editing with list f to check copy function" << std::endl;
  f.push_back(99);
  f.push_front(66);
  a.print(std::cout);
  f.print(std::cout);
  assert(a.back() == 25);
  assert(a.size() != f.size());
  std::cout << std::endl <<"AFTER: unrolled list - a" << std::endl;
  a.print(std::cout);
  std::cout << "AFTER: unrolled list - d" << std::endl;
  f.print(std::cout);

  std::cout << std::endl << "More testing done, see below for memory error if using Dr.Memory" << std::endl;
}