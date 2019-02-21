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
const int HALF_ELEMENTS_PER_NODE = (int)ceil((float)NUM_ELEMENTS_PER_NODE / (float)2);
typedef unsigned int uint;

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  // Constructors
  Node() : num_elements_(0), next_(NULL), prev_(NULL) {}
  // Copy Constructor
  Node (const Node<T> &n) {
    next_ = n.next_;
    prev_ = n.prev_;
    num_elements_ = n.numElement();
    for (uint i = 0; i < num_elements_; i++)
    {
      elements_[i] = n.getElement(i);
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

  // Helpers
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
  uint num_elements_ = 0;
  Node<T>* next_ = NULL;
  Node<T>* prev_ = NULL;
};

// Get Const reference of an element in the node of specific offset
template <class T>
const T& Node<T>::getElement(uint offset) const
{
  if (!isLegalIndex(offset))
  {
    std::cerr << "Error when fetching value: Out of bound." << std::endl;
  } else {
    return elements_[offset];
  }
}

// Get mutable reference of an element in the node of specific offset
template <class T>
T& Node<T>::getElement(uint offset)
{
  if (!isLegalIndex(offset))
  {
    std::cerr << "Error when fetching value: Out of bound." << std::endl;
  } else {
    return elements_[offset];
  }
}

// Make a space if requested offset has already occupied by an element
template <class T>
void Node<T>::move(uint offset)
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

// Move the elements in the array to eliminate the empty space among elements
template <class T>
void Node<T>::step_front(uint offset)
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

// Insert given value into given offset
template <class T>
void Node<T>::insert(const T& value, uint offset)
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

// Remove element at the given location
// Return erased element
template <class T>
T Node<T>::erase(uint offset)
{
  if (!isLegalIndex(offset))
  {
    std::cerr << "Value cannot be erased since Index out of bound" << std::endl;
  } else {
    T erased = elements_[offset];
    step_front(offset);
    num_elements_--;

    return erased;
  }
}

// Deconstructor/Reset to default
template <class T>
void Node<T>::destroy()
{
  num_elements_ = 0;
}

// Print current node and its element(s)
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
      std::cout << "Iterator end() should not be increased" << std::endl;
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
      std::cout << "Iterator end() should not be increased" << std::endl;
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
  Node<T>* ptr_ = NULL;    // ptr to node in the list
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

  // methods
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

  // Helpers
  void push_back_node(const Node<T> &n);
  iterator erase_node(iterator itr);
  iterator split_node(iterator itr);

  // Methods
  void init(const T &t);

  iterator checkMerge(iterator itr);
  void mergeNode(Node<T> *one, Node<T> *other);

  //REPRESENTATION
  Node<T>* head_ = NULL;
  Node<T>* tail_ = NULL;
  unsigned int size_ = 0;
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
    // Initialize a new node
    init(v);
    size_++;
  } else {
    // Insert to the beginning
    insert(begin(), v);
  }
}

template <class T>
void UnrolledLL<T>::pop_front() {
  // Do nothing when empty
  if (!empty())
  {
    // Erase the first element
    erase(begin());
  } else {
    std::cerr << "Empty list cannot pop_front!" << std::endl;
  }
}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {
  if (empty() || tail_->isFull())
  {
    // The last node is full or does not exist, generate a new Node and add.
    init(v);
  } else {
    // Add to the tail and check merge status
    tail_->push_back(v);
    checkMerge(iterator(tail_, tail_->numElement() - 1));
  }

  size_++;
}

template <class T>
void UnrolledLL<T>::pop_back() {
  // Do nothing when empty
  if (!empty())
  {
    // If it is not empty, tail_ must exist,
    // and tail_ should not be empty
    erase(iterator(tail_, tail_->numElement() - 1));
  } else {
    std::cerr << "Empty list should not be pop_back!" << std::endl;
  }
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  if (itr.ptr_ != NULL){
    // Keep a record of the next elements.
    iterator next(itr);
    next++;

    // Remove from the node and decrease size
    itr.ptr_->erase(itr.offset_);
    size_--;

    if (itr.ptr_->isEmpty())
    {
      // Current Node is Empty, removing...
      return checkMerge(erase_node(itr));
    } else {
      if (next == end()){
        // We just delete the last element of the list, return end()
        return end();
      } else if (itr.offset_ > itr.ptr_->numElement() - 1){
        // We have removed the last element in this node, move to the next node.
        // However, we need to check current node, increase itr after adjustment.
        return ++checkMerge(iterator(itr.ptr_, itr.ptr_->numElement() - 1));
      } else {
        // The next element should be @ the same spot
        return checkMerge(itr);
      }
    }
  } else {
    std::cout << "Iterator not recognized" << std::endl;
  }
}

// Remove a node when it is empty
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase_node(const iterator itr)
{
  Node<T> * prev = itr.ptr_->prev_;
  Node<T> * next = itr.ptr_->next_;

  // If head != tail, there must be >= 2 nodes in the list
  if (itr.ptr_ == head_ && itr.ptr_ == tail_)
  {
    // then this is the only node in the list
    head_ = next;
    tail_ = next;
  } else if (itr.ptr_ == head_)
  {
    // This is the head node?
    head_ = next;
    next->prev_ = NULL;
  } else if (itr.ptr_ == tail_) {
    // Or this is the tail node?
    // Here, we are removing the last node, so we should return end()
    tail_ = prev;
    prev->next_ = NULL;
  } else {
    // Normal node
    prev->next_ = next;
    next->prev_ = prev;
  }

  delete itr.ptr_;

  return iterator(next, 0);
}

// Split a full node into two half-full node so it can hold more elements
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::split_node(UnrolledLL<T>::iterator itr) {
  if (itr.ptr_->isFull()) {
    // Create a new Node
    Node<T> *new_node = new Node<T>();
    // Insert the node at full-node's back
    new_node->prev_ = itr.ptr_;
    if (itr.ptr_ != tail_) {
      new_node->next_ = itr.ptr_->next_;
      itr.ptr_->next_->prev_ = new_node;
    } else {
      tail_ = new_node;
    }

    itr.ptr_->next_ = new_node;

    // Separation
    uint num = itr.ptr_->numElement();
    uint limit = (num - 1) / 2;
    // and make it 50% full
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

// Insert element at given location
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
  Node<T> * n = old.head_;
  while (n != NULL)
  {
    // Copy node and link together
    push_back_node(*n);
    n = n->next_;
  }
}

// Push given node to the back of the list
template <class T>
void UnrolledLL<T>::push_back_node(const Node<T> &n)
{
  // Copy a new Node
  Node<T> * new_node = new Node<T>(n);
  new_node->next_ = NULL;
  if (empty())
  {
    // then this is the first new Node.
    head_ = new_node;
    tail_ = new_node;
    new_node->prev_ = NULL;
  } else {
    // Attached to the back
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    tail_ = new_node;
  }
}

// Deconstructor/Reset the list
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

  size_ = 0;
  head_ = tail_ = NULL;
}

// Check if given node can be merged into nearest location
// Return the correct iterator if merge happened.
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::checkMerge(iterator itr)
{
  if (!empty()){
    // If erase kick out the last element of the list
    // Don't check anything, this is the end()
    if (itr.ptr_ != NULL) {
      // Acquire prev node info
      Node<T> *prev = itr.ptr_->prev_;
      int prev_num = -1;
      if (prev != NULL) {
        prev_num = prev->numElement();
      }

      // Acquire next node info
      Node<T> *next = itr.ptr_->next_;
      int next_num = -1;
      if (next != NULL) {
        next_num = next->numElement();
      }

      // Acquire current node info
      Node<T> *current = itr.ptr_;
      int current_num = current->numElement();

      if (prev_num != -1 &&
          current_num != -1 &&
          prev_num + current_num <= NUM_ELEMENTS_PER_NODE) {
        // If prev can be merged with current, remove current and keep prev
        mergeNode(prev, current);

        return iterator(prev, (uint) (prev_num + itr.offset_));
      } else if (next_num != -1 &&
                 current_num != -1 &&
                 next_num + current_num <= NUM_ELEMENTS_PER_NODE) {
        // If next can be merged with current, remove next and keep current.
        mergeNode(current, next);
      } else {
        // if current node if lower than half
        // Split up a full node nearby and
        if (current_num != -1 && current_num < HALF_ELEMENTS_PER_NODE)
        {
          if (prev_num > HALF_ELEMENTS_PER_NODE)
          {
            // Get one element from the prev
            current->push_front(prev->pop_back());
            itr++;
          } else if (next_num > HALF_ELEMENTS_PER_NODE)
          {
            current->push_back(next->pop_front());
          }
        }
      }

      return itr;
    }
  } else {
    // Empty list should always get the begin()
    return begin();
  }
}

// Merge two nodes with given order and fix relationship
template <class T>
void UnrolledLL<T>::mergeNode(Node<T> *one, Node<T> *other)
{
  while (!other->isEmpty())
  {
    one->push_back(other->pop_front());
  }

  // If we are removing tail, update pointer
  if (other == tail_)
  {
    tail_ = one;
  }

  // Remove "other" and relink nodes
  one->next_ = other->next_;
  if (one->next_ != NULL){
    one->next_->prev_ = one;
  }
  delete other;
}

// Initialize when list is empty
// Given the first element so we can build a node
template <class T>
void UnrolledLL<T>::init(const T &t)
{
  Node<T> * new_node = new Node<T>();
  new_node->push_back(t);
  push_back_node(*new_node);

  delete new_node;
}

//Example:
//UnrolledLL, size: 14
//H   node:[6] 77 92 91 77 16 17
//    node:[3] 77 19 20
//T   node:[5] 22 23 25 77 26
template <class T>
void UnrolledLL<T>::print(std::ostream &output) const
{
  output << "UnrolledLL, size: " << size_ << std::endl;
  Node<T> * n = head_;
  while (n != NULL)
  {
    if (n == head_ && n == tail_)
    {
      output << "H&T";
    } else if (n == head_)
    {
      output << "H  ";
    } else if (n == tail_)
    {
      output << "T  ";
    } else {
      output << "   ";
    }
    n->print(output);
    output << std::endl;
    n = n->next_;
  }
}
#endif