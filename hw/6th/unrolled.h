#ifndef UnrolledLL_h_
#define UnrolledLL_h_
// A simplified implementation of a generic list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>

const int NUM_ELEMENTS_PER_NODE = 6;
typedef unsigned int uint;

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  Node() : next_(NULL), prev_(NULL), num_elements_(0) {}
  Node(const Node<T> &next, const Node<T> &prev, uint num_elements, const T* elements)
  {
    next_ = next;
    prev_ = prev;
    num_elements_ = num_elements;
    for (uint i = 0; i < num_elements; i++)
    {
      elements_[i] = elements[i];
    }
  };
  ~Node() { destroy(); };

  // Accessor 
  uint numElement() const { return num_elements_; };
  const T& getElement(uint offset) const;
  // Mutator
  void insert(const T& value, uint offset);
  void erase(uint offset);
  // Methods
  bool isLegalIndex(uint offset) const { return offset < numElement(); };
  bool isAllowedIndex(uint offset) const { return offset < NUM_ELEMENTS_PER_NODE; };
  bool isFull() const { return numElement() >= NUM_ELEMENTS_PER_NODE; };
  bool isEmpty() const { return numElement() <= 0; }
  void destroy();

  // REPRESENTATION
  T* elements_[NUM_ELEMENTS_PER_NODE] = {};
  uint num_elements_;
  Node<T>* next_;
  Node<T>* prev_;
};

template <class T> const T& Node<T>::getElement(uint offset) const 
{
  if (!isLegalIndex(offset))
  {
    std::cerr << "Error when fetching value: Out of bound." << std::endl;
    return NULL;
  } else {
    return elements_[offset];
  }
}

template <class T> void Node<T>::insert(const T& value, uint offset)
{
  if (isFull())
  {
    std::cerr << "Value cannot be added when Node is full." << std::endl;
  } else if (!isAllowedIndex(offset)) {
    std::cerr << "Value cannot be added since Index out of Bound." << std::endl;
  } else {
    // If the set is occupied by other element, move things away.
    // There won't be any empty block between two elements
    for (uint i = numElement() - 1; i >= offset ; i--)
    {
      // Move one back
      elements_[i + 1] = elements_[i];
    }

    elements_[offset] = *value;
  }
}

template <class T> void Node<T>::erase(uint offset)
{
  if (!isLegalIndex(offset))
  {
    std::cerr << "Value cannot be erased since Index out of bound" << std::endl;
  } else {
    delete elements_[offset];
    // If there is element behind, move one step front (Don't be out of bound!)
    uint behind = numElement() - 1 - offset;
    if (behind > 0)
    {
      for (uint i = offset; i < offset + behind; i++)
      {
        elements_[i] = elements_[i + 1];
      }
    }
    num_elements_--;
  }
}

template <class T> void Node<T>::destroy()
{
  delete [] elements_;
}

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator() : ptr_(NULL) {}
  list_iterator(Node<T>* p) : ptr_(p) {}
  list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_), offset_(offset_) {}
  list_iterator<T>& operator=(const list_iterator<T>& old) {
    ptr_ = old.ptr_; offset_ = old.offset_;  return *this; }
  ~list_iterator() {}

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->getElement(offset_);  }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
    offset_++;
    if (offset_ > ptr_->numElement() - 1){
      ptr_ = ptr_->next_;
      offset_ = 0;
    }
    return *this;
  }

  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
    offset_++;
    if (offset_ > ptr_->numElement() - 1)
    {
      ptr_ = ptr_->next_;
      offset_ = 0;
    }
    return temp;
  }

  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
    if (offset_ == 0)
    {
      ptr_ = ptr_->prev_;
      offset_ = ptr_->numElement() - 1;
    } else {
      offset_--;
    }
    return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    if (offset_ == 0)
    {
      ptr_ = ptr_->prev_;
      offset_ = ptr_->numElement() - 1;
    } else {
      offset_--;
    }
    return temp;
  }
  // the UnrolledLL class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_ && offset_ == r.offset_; }
  bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_ && offset_ != r.offset_; }

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
  uint offset_ = 0;
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T>& old) { this->copy_list(old); }
  UnrolledLL& operator= (const UnrolledLL<T>& old);
  ~UnrolledLL() { this->destroy_list(); }

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { this->destroy_list(); }

  // read/write access to contents
  const T& front() const { return head_->value_;  }
  T& front() { return head_->value_; }
  const T& back() const { return tail_->value_; }
  T& back() { return tail_->value_; }

  // modify the linked list structure
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();

  typedef list_iterator<T> iterator;
  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& v);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(NULL); }

private:
  // private helper functions
  void copy_list(const UnrolledLL<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);
  }
  return *this;
}

template <class T>
void UnrolledLL<T>::push_front(const T& v) {





}

template <class T>
void UnrolledLL<T>::pop_front() {




}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {





}

template <class T>
void UnrolledLL<T>::pop_back() {




}

// do these lists look the same (length & contents)?
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
  if (left.size() != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}
template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {












}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {










}

template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
















}

template <class T>
void UnrolledLL<T>::destroy_list() {
  iterator i = iterator(head_);
  Node<T> * node = *i;
  while (i != i.end())
  {
    i++;
    delete node;
    node = *i;
  }
  delete node;
}

#endif