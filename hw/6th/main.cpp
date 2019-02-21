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

  //
  //
  // ADD YOUR OWN TEST CASES HERE
  // ADD COMMENTS TO EXPLAIN THE PURPOSE OF THE TEST CASES
  // TEST CASES SHOULD FINISH AND NOT CRASH. OUTPUT IS HELPFUL AS WELL.
  //
  //

  // Deconstructor/Print: Zero, one, or more node appears.
  std::cout << "**************Begin MoreTest()**************" << std::endl;
  UnrolledLL<int> * a = new UnrolledLL<int>;
  a->print(std::cout);
  delete a;

  UnrolledLL<int> * b = new UnrolledLL<int>;
  b->push_back(1);
  b->print(std::cout);
  delete b;

  UnrolledLL<int> * c = new UnrolledLL<int>;
  for (int i = 0; i < 10; i++)
  {
    c->push_back(1);
  }
  c->print(std::cout);
  delete c;

  std::cout << "End Print/Deconstructor/Special case test" << std::endl;

  // Assignment operator, types other than int
  UnrolledLL<char> d;
  for (char i = 'a'; i <= 'z'; i++)
  {
    d.push_back(i);
  }
  d.print(std::cout);

  for (char i = 'A'; i <= 'Z'; i++)
  {
    d.push_front(i);
  }
  d.print(std::cout);

  UnrolledLL<char> e = d;
  UnrolledLL<char> f(d);
  e.push_back('~');
  f.push_front('@');

  e.print(std::cout);
  f.print(std::cout);

  std::cout << "Finish copy and char type test" << std::endl;

  // Erase/Insert, merge node
  UnrolledLL<std::string> g;

  for (int i = 0; i < NUM_ELEMENTS_PER_NODE; i++)
  {
    g.push_front("abc");
  }

  g.print(std::cout);

  for (int i = 0; i < NUM_ELEMENTS_PER_NODE; i++)
  {
    g.push_front("abc");
  }

  list_iterator<std::string> gi = g.begin();
  for (int i = 1; i < g.size(); i++)
  {
    if (i > NUM_ELEMENTS_PER_NODE && i <= NUM_ELEMENTS_PER_NODE * 1.5)
    {
      gi = g.insert(gi, "cde");
    } else {
      gi++;
    }
  }

  gi++;

  assert(gi == g.end());

  std::cout << "--Before merge" << std::endl;
  g.print(std::cout);

  gi = g.begin();
  for (int i = 0; i < NUM_ELEMENTS_PER_NODE; i++)
  {
    gi++;
  }

  // Erase Merge
  for (int i = 0; i < NUM_ELEMENTS_PER_NODE / 2; i++)
  {
    gi = g.erase(gi);
  }

  std::cout << "--After merge" << std::endl;
  g.print(std::cout);

  std::cout << "Finish std::string, erase merge" << std::endl;

  // Push, Pop one/Zero node
  UnrolledLL<int> l;
  l.push_back(1);
  l.pop_front();
  l.push_front(1);
  l.pop_back();
  l.insert(l.begin(), 1);

  assert(l.front() == 1);
  l.print(std::cout);

  l.pop_back();
  l.pop_front();

  std::cout << "Finished One/Zero Node with pop/push test" << std::endl;
}
