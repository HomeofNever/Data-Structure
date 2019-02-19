#ifndef UnrolledLL_h_
#define UnrolledLL_h_
// A simplified implementation of a generic list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>
#include <iostream>

const int NUM_ELEMENTS_PER_NODE = 6;
typedef unsigned int uint;

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  Node() : num_elements_(0), next_(NULL), prev_(NULL) {}
  Node (const Node<T> &n) {
    next_ = n.next_;
    prev_ = n.prev_;
    num_elements_ = n.numElement();
    for (uint i = 0; i < num_elements_; i++)
    {
      elements_[i] = n.elements_[i];
    }
  }
  ~Node() { destroy(); };

  // Accessor 
  uint numElement() const { return num_elements_; };
  const T& getElement(uint offset) const;
  T& getElement(uint offset);
  // Mutator
  void insert(const T& value, uint offset);
  T erase(uint offset);
  void push_front(const T& v) { insert(v, 0); };
  void push_back(const T& v) { insert(v, numElement()); };
  T pop_front() { return erase(0); }
  T pop_back() { return erase(numElement() - 1); }
  // Helper
  void move(uint offset);
  void step_front(uint offset);
  const T& front() const { return getElement(0);  };
  T& front() { return getElement(0); };
  const T& back() const { return getElement(numElement() - 1); };
  T& back() { return getElement(numElement() - 1); };
  // Methods
  bool isLegalIndex(uint offset) const { return offset < numElement(); };
  bool isAllowedIndex(uint offset) const { return offset < NUM_ELEMENTS_PER_NODE; };
  bool isFull() const { return numElement() >= NUM_ELEMENTS_PER_NODE; };
  bool isEmpty() const { return numElement() <= 0; };
  void destroy();

  void print(std::ostream &output) const;

  // REPRESENTATION
  T elements_[NUM_ELEMENTS_PER_NODE];
  uint num_elements_;
  Node<T>* next_;
  Node<T>* prev_;
};

template <class T> const T& Node<T>::getElement(uint offset) const 
{
  if (!isLegalIndex(offset))
  {
    std::cerr << "Error when fetching value: Out of bound." << std::endl;
  } else {
    return elements_[offset];
  }
}

template <class T> T& Node<T>::getElement(uint offset)
{
  if (!isLegalIndex(offset))
  {
    std::cerr << "Error when fetching value: Out of bound." << std::endl;
  } else {
    return elements_[offset];
  }
}

template <class T> void Node<T>::move(uint offset)
{
  // If the set is occupied by other element, move things away.
  // There won't be any empty block between two elements
  if (!isEmpty() && !isFull() && isLegalIndex(offset))
  {
      for (int i = numElement() - 1; i >= (int)offset ; i--)
      {
        // Move one back
        elements_[i + 1] = elements_[i];
      }
  }
}

template <class T> void Node<T>::step_front(uint offset)
{
  // If there is element behind, move one step front
  uint behind = numElement() - 1 - offset;
  if (behind > 0)
  {
    for (uint i = offset; i < offset + behind; i++)
    {
      elements_[i] = elements_[i + 1];
    }
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
    move(offset);
    elements_[offset] = value;
    num_elements_++;
  }
}

template <class T> T Node<T>::erase(uint offset)
{
  if (!isLegalIndex(offset))
  {
    std::cerr << "Value cannot be erased since Index out of bound" << std::endl;
  } else {
    T erased = elements_[offset];
    // delete elements_[offset];
    step_front(offset);
    num_elements_--;

    return erased;
  }
}

template <class T> void Node<T>::destroy()
{
  // delete [] elements_;
}

template <class T>
void Node<T>::print(std::ostream &output) const
{
  output << " node:[" << numElement() << "] ";
  for (uint i = 0; i < numElement(); i++)
  {
    output << getElement(i) << " ";
  }
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
  list_iterator(Node<T>* p, uint offset_) : ptr_(p), offset_(offset_) {}
  list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_), offset_(old.offset_) {}
  list_iterator<T>& operator=(const list_iterator<T>& old) {
    ptr_ = old.ptr_; offset_ = old.offset_;  return *this; }
  ~list_iterator() {}

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->getElement(offset_);  }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
    if (ptr_ == NULL)
    {
      offset_ = 0;
      std::cout << "Iterator end() should not be increase" << std::endl;
    } else {
      offset_++;
      if (offset_ > ptr_->numElement() - 1){
        ptr_ = ptr_->next_;
        offset_ = 0;
      }
    }

    return *this;
  }

  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
    if (ptr_ == NULL)
    {
      offset_ = 0;
      std::cout << "Iterator end() should not be increase" << std::endl;
    } else {
      offset_++;
      if (offset_ > ptr_->numElement() - 1) {
        ptr_ = ptr_->next_;
        offset_ = 0;
      }
    }
    return temp;
  }

  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
    if (offset_ == 0)
    {
      ptr_ = ptr_->prev_;
      if (ptr_ == NULL)
      {
        // Out of Bound, make it equal to end()
        offset_ = 0;
      } else {
        offset_ = ptr_->numElement() - 1;
      }
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
      if (ptr_ == NULL)
      {
        // Out of Bound, make it equal to end()
        offset_ = 0;
      } else {
        offset_ = ptr_->numElement() - 1;
      }
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
    return ptr_ != r.ptr_ || offset_ != r.offset_; }

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
  const T& front() const { return head_->front();  }
  T& front() { return head_->front(); }
  const T& back() const { return tail_->back(); }
  T& back() { return tail_->back(); }

  // modify the linked list structure
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();

  typedef list_iterator<T> iterator;
  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& v);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(); }

  void print(std::ostream &output) const;

private:
  // private helper functions
  void copy_list(const UnrolledLL<T>& old);
  void destroy_list();

  void push_back_node(const Node<T> &n);
  iterator erase_node(iterator itr);
  iterator split_node(iterator itr);

  // Methods
  void init(const T &t);
  iterator checkMerge(iterator itr);
  void mergeNode(Node<T> *one, Node<T> *other);

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
  if (empty())
  {
    init(v);
    size_++;
  } else {
    insert(begin(), v);
  }
}

template <class T>
void UnrolledLL<T>::pop_front() {
  if (!empty())
  {
    erase(begin());
  }
}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {
  if (empty() || tail_->isFull())
  {
    // The last node is full or does not exist, generate a new Node and add.
    init(v);
  } else {
    tail_->push_back(v);
    checkMerge(iterator(tail_, tail_->numElement() - 1));
  }

  size_++;
}

template <class T>
void UnrolledLL<T>::pop_back() {
  if (!empty())
  {
    erase(iterator(tail_, tail_->numElement() - 1));
  }
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
  if (itr.ptr_ != NULL){
    // Keep a record of the next elements.
    iterator next(itr);
    next++;

    itr.ptr_->erase(itr.offset_);
    size_--;

    if (itr.ptr_->isEmpty())
    {
      // Current Node is Empty, removing...
      return checkMerge(erase_node(itr));
    } else {
      if (next == end()){
        // We just delete the last element, return end
        return end();
      } else if (itr.offset_ > itr.ptr_->numElement() - 1){
        // We have removed the last element in this node, move to the next node.
        return checkMerge(iterator(itr.ptr_->next_, 0));
      } else {
        // The next element should be @ the same spot
        return checkMerge(itr);
      }
    }
  } else {
    std::cout << "Iterator not recognized" << std::endl;
  }
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase_node(const iterator itr)
{
  Node<T> * prev = itr.ptr_->prev_;
  Node<T> * next = itr.ptr_->next_;

  if (itr.ptr_ == head_)
  {
    head_ = next;
    next->prev_ = NULL;
  } else if (itr.ptr_ == tail_) {
    tail_ = prev;
    prev->next_ = NULL;

    delete itr.ptr_;

    return iterator(tail_, tail_->numElement() - 1);
  } else {
    prev->next_ = next;
    next->prev_ = prev;
  }

  delete itr.ptr_;

  return iterator(next, 0);
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::split_node(UnrolledLL<T>::iterator itr) {
  if (itr.ptr_->isFull()) {
    // Create a new Node and make them 50% full
    Node<T> *new_node = new Node<T>();
    new_node->prev_ = itr.ptr_;
    if (itr.ptr_ != tail_) {
      new_node->next_ = itr.ptr_->next_;
      itr.ptr_->next_->prev_ = new_node;
    } else {
      tail_ = new_node;
    }

    itr.ptr_->next_ = new_node;

    uint num = itr.ptr_->numElement();
    uint limit = (num - 1) / 2;
    for (uint i = num - 1; i > limit; i--) {
      new_node->push_front(itr.ptr_->pop_back());
    }

    // Retrieve current iterator
    if (itr.offset_ > limit) {
      itr = iterator(itr.ptr_->next_, itr.offset_ - limit - 1);
    }
  } else {
    std::cerr << "Node should not be split if it is not full!" << std::endl;
  }

  return itr;
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v)
{
  if (itr.ptr_ != NULL) {
    // First, if there is a spot for the element: Great! Do Nothing but add.
    if (itr.ptr_->isFull()) {
      // OOPs, current node is full, split up into two node.
      itr = split_node(itr);
    }
    itr.ptr_->insert(v, itr.offset_);
    itr++;
  } else {
    if (empty())
    {
      // Current List is empty, init and add element
      init(v);
      itr = iterator(tail_);
    } else {
      std::cerr << "Iterator not recognized." << std::endl;
    }
  }

  size_++;

  return checkMerge(itr);
}

template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old)
{
  size_ = old.size_;
  iterator o = old.begin();
  o++; // Increase one since head is added.
  while (o != old.end())
  {
    // Copy node and link together
    push_back(*o);
    o++;
  }
}

template <class T>
void UnrolledLL<T>::push_back_node(const Node<T> &n)
{
  // Create a new Node
  Node<T> * new_node = new Node<T>(n);
  new_node->next_ = NULL;
  if (tail_ == NULL && head_ == NULL)
  {
    // then this is the first new Node.
    head_ = new_node;
    tail_ = new_node;
    new_node->prev_ = NULL;
  } else {
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    tail_ = new_node;
  }
}

template <class T>
void UnrolledLL<T>::destroy_list()
{
  Node<T> * n = head_;
  while (n != NULL)
  {
    Node<T> * next = n->next_;
    delete n;
    n = next;
  }
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::checkMerge(iterator itr)
{
  if (!empty()){
    if (itr.ptr_ == NULL)
    {
      // Erase kick out the last element of the list
      itr = iterator(tail_, tail_->numElement() - 1);
    }

    Node<T> *prev = itr.ptr_->prev_;
    int prev_num = -1;
    if (prev != NULL) {
      prev_num = prev->numElement();
    }

    Node<T> *next = itr.ptr_->next_;
    int next_num = -1;
    if (next != NULL) {
      next_num = next->numElement();
    }

    Node<T> *current = itr.ptr_;
    int current_num = current->numElement();

    if (prev_num != -1 &&
        current_num != -1 &&
        prev_num + current_num <= NUM_ELEMENTS_PER_NODE) {

      mergeNode(prev, current);

      return iterator(prev, prev_num + current_num - 1);
    } else if (next_num != -1 &&
               current_num != -1 &&
               next_num + current_num <= NUM_ELEMENTS_PER_NODE) {

      mergeNode(current, next);
    }

    return itr;
  } else {
    return begin();
  }
}

template <class T>
void UnrolledLL<T>::mergeNode(Node<T> *one, Node<T> *other)
{
  while (!other->isEmpty())
  {
    one->push_back(other->pop_front());
  }


  // Remove "other" and relink Nodes
  one->next_ = other->next_;
  if (one->next_ != NULL){
    one->next_->prev_ = one;
  }
  delete other;
}

template <class T>
void UnrolledLL<T>::init(const T &t)
{
  Node<T> * new_node = new Node<T>();
  new_node->push_back(t);
  push_back_node(*new_node);

  delete new_node;
}

//UnrolledLL, size: 18
// node:[5] 11 12 13 14 15
// node:[6] 16 17 18 19 20 21
// node:[6] 22 23 24 25 26 27
// node:[1] 28
template <class T>
void UnrolledLL<T>::print(std::ostream &output) const
{
  output << "UnrolledLL, size: " << size_ << std::endl;
  Node<T> * n = head_;
  while (n != NULL)
  {
    n->print(output);
    output << std::endl;
    n = n->next_;
  }
}
#endif