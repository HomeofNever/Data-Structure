#ifndef UnrolledLL_h_
#define UnrolledLL_h_
const int NUM_ELEMENTS_PER_NODE = 6;
// Three separate classes are defined: a Node class, an iterator class, and
// the actual UnrolledLL list class. 
#include <cassert>

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
    // Default Constructor, Constructor
    Node();
    Node(T *a);// Passing an array as a parameter
    // How to pass the size of array? Question

    // Member Function
    void element_erase(int location);
    void element_insert(int location, const T& value);

    // REPRESENTATION
    // Static array for dynamic node
    T elements_[NUM_ELEMENTS_PER_NODE];
    Node<T>* next_;
    Node<T>* prev_;
    int num_elements_;
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
    // Default constructor
    list_iterator() : ptr_(NULL), offset_(0), itrEnd(false) {}
    // Constructor
    list_iterator(Node<T>* p, bool end=false) {
      ptr_ = p; offset_ = 0; itrEnd = end;
      if (itrEnd == true) offset_ = (ptr_->num_elements_);
    }
    // Copy constructor
    list_iterator(const list_iterator<T>& old);
    // Assignment operator
    list_iterator<T>& operator=(const list_iterator<T>& copy);

    // Dereferencing operator gives access to the value at the pointer
    T& operator*()  { return ptr_->elements_[offset_]; }

    // Increment & decrement operators
    list_iterator<T>& operator++();// Pre
    list_iterator<T> operator++(int);// Post
    list_iterator<T>& operator--();// Pre
    list_iterator<T> operator--(int);// Post

    // Comparions operators are straightforward
    bool operator==(const list_iterator<T>& r) const;
    bool operator!=(const list_iterator<T>& r) const;

    // Determine whether is the end of an array/ node
    // Determine whether is the last node in the list if next_ is NULL
    bool itrEnd;

    // The UnrolledLL class needs access to the private ptr_ member variable
    friend class UnrolledLL<T>;

private:
    // REPRESENTATION
    Node<T>* ptr_;    // ptr to node in the list
    int offset_;// which element within the Node it is on
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    UnrolledLL();
    UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
    UnrolledLL& operator=(const UnrolledLL<T>& old);
    ~UnrolledLL() { destroy_list(); }

    typedef list_iterator<T> iterator;

    // Accessors & Modifiers
    unsigned int size() const { return size_; }
    bool empty() const { return head_ == NULL; }

    // read/write access to contents
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();

    // modify the linked list structure
    void push_front(const T& v);
    void pop_front();
    void push_back(const T& v);
    void pop_back();

    iterator erase(iterator itr);
    iterator insert(iterator itr, const T& v);
    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(tail_, true); }

    // Comparison
    bool operator==(UnrolledLL<T>& right);
    bool operator!=(UnrolledLL<T>& right);

    // Helper function
    void print(std::ostream& output) const;

private:
    // private helper functions
    void copy_list(const UnrolledLL<T>& old);
    void destroy_list();
    void memory_clear(Node<T>* node);

    //REPRESENTATION
    Node<T>* head_;
    Node<T>* tail_;
    unsigned int size_;// Total number of elements in the list
    /* If the array is empty, the node will be deleted. So the size_ can be
    used to determine whether the list is empty(0 node)
    */
};


// -----------------------------------------------------------------
// -----------------------------------------------------------------
// -----------------------------------------------------------------
// -----------------------------------------------------------------
// NODE CLASS IMPLEMENTATION
// Node Default Constructor
template <class T>
Node<T>::Node() {
  next_ = NULL;
  prev_ = NULL;
  num_elements_ = 0;
  for (unsigned int i = 0; i < NUM_ELEMENTS_PER_NODE; ++i) {
    elements_[i] = T(); // Value initialization
  }
}

// Constructor
template <class T>
Node<T>::Node(T *a) {
  next_ = NULL;
  prev_ = NULL;
  for (unsigned int i = 0; i < NUM_ELEMENTS_PER_NODE; ++i) {
    elements_[i] = *(a+i);
    if (elements_[i]) {
      num_elements_++;
    }
  }
}


// Erase opertaion on array in the node
// Do not consider the empty node situation after erasing
template <class T>
void Node<T>::element_erase(int location) {
  if (location >= NUM_ELEMENTS_PER_NODE || location < 0) { // Error check
    std::cerr << "The location for erase operation is wrong!" << std::endl;
    exit(1);
  }
  for (int i = location; i < (num_elements_ - 1); ++i) {
    elements_[i] = elements_[i+1];// Replace the elements one by one
  }
  elements_[num_elements_ - 1] = T();// Value initialization
  num_elements_--;
}


// Insert operation on array in the node
// Do not consider the full array situation that requires to create a new node
template <class T>
void Node<T>::element_insert(int location, const T& value) {
  if (location >= NUM_ELEMENTS_PER_NODE || location < 0) { // Error check
    std::cerr << "The location for insert operation is wrong!" << std::endl;
  }
  if (location < num_elements_) { // The location is not 'NULL'
    for (int i = num_elements_; i > location; --i) {
      elements_[i] = elements_[i-1];// Move elements that after location backward
    }
    elements_[location] = value;// Assign the value to the location
    num_elements_++;
  } else { // The location is 'NULL'
    elements_[location] = value;// Assign the value directly
    num_elements_++;
  }
}

// -----------------------------------------------------------------
// -----------------------------------------------------------------
// LIST ITERATOR CLASS IMPLEMENTATION
// Copy constructor
template <class T>
list_iterator<T>::list_iterator(const list_iterator<T>& old) {
  this->ptr_ = old.ptr_;
  this->offset_ = old.offset_;
  this->itrEnd = old.itrEnd;
}

// Assignment operator
template <class T>
list_iterator<T>& list_iterator<T>::operator=(const list_iterator<T>& copy) {
  if (this != &copy) {
    this->ptr_ = copy.ptr_;
    this->itrEnd = copy.itrEnd;
    this->offset_ = copy.offset_;
  }
  return *this;
}

// increment & decrement operators
// Firstly, moving within the elements of array
// Secondly, moving along the nodes
/* 
Pre-increment operator++: Increase offset at first
If the pointed location of iterator is greater than or equal to the length of array 
or number of elements, checking whether the current node is the last node and determining 
the movement of iterator, moving to next node or stop there.
 */
template <class T>
list_iterator<T>& list_iterator<T>::operator++() { // pre-increment, e.g., ++iter
  offset_++;
  if ((offset_ >= NUM_ELEMENTS_PER_NODE) || (offset_ >= ptr_->num_elements_)) {
    if (ptr_->next_ == NULL) { // Last node in the list, iterator stop here
      itrEnd = true;
      offset_ = ptr_->num_elements_;
    } else { // Move to the first location of next node, reset the parameter
      offset_ = 0;
      ptr_ = ptr_->next_;
    }
  }
  return *this;
}

/* 
Post-increment operator++:
Store the current iterator, and then implement the increment operation
 */
template <class T>
list_iterator<T> list_iterator<T>::operator++(int) { // post-increment, e.g., iter++
  list_iterator<T> temp(*this);
  offset_++;
  if ((offset_ >= NUM_ELEMENTS_PER_NODE) || (offset_ >= ptr_->num_elements_)) {
    if (ptr_->next_ == NULL) { // Last node in the list, iterator stop here
      itrEnd = true;
      offset_ = ptr_->num_elements_;
    } else { // Move to the first location of next node, reset the parameter
      offset_ = 0;
      ptr_ = ptr_->next_;
    }
  }
  return temp;
}

/* 
Pre-decrement --operator: Decrease the offset at first
If the location of iterator pointer is less than 0, moving to the preview node.
If this is a empty node, it will be deleted in the later operation. So the iterator 
is unable to stop there.
 */
template <class T>
list_iterator<T>& list_iterator<T>::operator--() { // pre-decrement, e.g., --iter
  if (itrEnd == true) {
    itrEnd = false;
  }
  offset_--;
  if (offset_ < 0) {
    ptr_ = ptr_->prev_;// Change the pointer to the preview node firstly
    offset_ = ptr_->num_elements_-1;// Reset the pointer to the last element of array
  }
  return *this;
}

/* 
Post-decrement operator--:
Store the current iterator, and then implement the decrement operation
 */
template <class T>
list_iterator<T> list_iterator<T>::operator--(int) { // post-decrement, e.g., iter--
  list_iterator<T> temp(*this);
  if (itrEnd == true) {
    itrEnd = false;
  }
  offset_--;
  if (offset_ < 0) {
    ptr_ = ptr_->prev_;// Change the pointer to the preview node firstly
    offset_ = ptr_->num_elements_-1;// Reset the pointer to the last element of array
  }
  return temp;
}

// Comparions operators are straightforward
template <class T>
bool list_iterator<T>::operator==(const list_iterator<T>& r) const {
  return ((this->ptr_ == r.ptr_) && (this->offset_ == r.offset_));
}

template <class T>
bool list_iterator<T>::operator!=(const list_iterator<T>& r) const {
  return ((this->ptr_ != r.ptr_) || (this->offset_ != r.offset_));
}

// -----------------------------------------------------------------
// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
// Constructor
template <class T>
UnrolledLL<T>::UnrolledLL() {
  size_ = 0;
  head_ = new Node<T>;
  head_->prev_ = NULL;
  head_->next_ = NULL;
  tail_ = head_;
}

template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}

// read/write access to contents
template <class T>
const T& UnrolledLL<T>::front() const {
  if (size_ == 0) {
    std::cerr << "The list size is 0! unable to get the front value." << std::endl;
    exit(1);
  }
  return head_->elements_[0];
}

template <class T>
T& UnrolledLL<T>::front() {
  if (size_ == 0) {
    std::cerr << "The list size is 0! unable to get the front value." << std::endl;
    exit(1);
  }
  return head_->elements_[0];
}

template <class T>
const T& UnrolledLL<T>::back() const {
  if (size_ == 0) {
    std::cerr << "The list size is 0! unable to get the back value." << std::endl;
    exit(1);
  }
  return tail_->elements_[tail_->num_elements_ - 1];
}

template <class T>
T& UnrolledLL<T>::back() {
  if (size_ == 0) {
    std::cerr << "The list size is 0! unable to get the back value." << std::endl;
    exit(1);
  }
  return tail_->elements_[tail_->num_elements_ - 1];
}

/*
Erase operation for the erasing the node of list.
 */
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  assert (size_ > 0);
  --size_;
  // Modify the element erase firstly
  itr.ptr_->element_erase(itr.offset_);

  if (itr.ptr_->num_elements_ == 0) {
    iterator result(itr.ptr_->next_);
    // One node left in the list.
    // Empty list
    if (itr.ptr_ == head_ && head_ == tail_) {
      destroy_list();
    } else if (itr.ptr_ == head_) {
      // Removing the head in a list with at least two nodes
      head_ = head_->next_;
      head_->prev_ = NULL;
    } else if (itr.ptr_ == tail_) {
      // Removing the tail in a list with at least two nodes
      tail_ = tail_->prev_;
      tail_->next_ = NULL;
    } else { // Normal remove
      itr.ptr_->prev_->next_ = itr.ptr_->next_;
      itr.ptr_->next_->prev_ = itr.ptr_->prev_;
    }
    delete itr.ptr_;
    itr = result;
  } // The node is not empty
  // Do not need to delete a node

  return itr;
}


template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  ++size_ ;
  // If the current node is full
  // insert a new node and then insert the element
  if (itr.ptr_->num_elements_ == NUM_ELEMENTS_PER_NODE) {
    if (itr.offset_ == 0) { // For push front operation. itr == begin() == head_ 
      Node<T>* new_node = new Node<T>;
      new_node->prev_ = itr.ptr_->prev_;
      new_node->next_ = itr.ptr_;
      if (itr.ptr_ == head_) {
        head_ = new_node;
      } else {
        new_node->prev_->next_ = new_node;
      }
      itr.ptr_->prev_ = new_node;
      new_node->element_insert(0, v);
      return iterator(new_node);
    } else { // If inserting into array, moving the elements to a new node
      Node<T>* new_node = new Node<T>;
      new_node->next_ = itr.ptr_->next_;
      new_node->prev_ = itr.ptr_;
      if (itr.ptr_ == tail_) {
        tail_ = new_node;
      } else {
        new_node->next_->prev_ = new_node;
      }
      itr.ptr_->next_ = new_node;
      // Moving the elements after the insertion to the new node
      for (int i = itr.offset_; i < itr.ptr_->num_elements_; ++i) {
        for (int j = 0; j < ((itr.ptr_->num_elements_)-itr.offset_); ++j) {
          new_node->element_insert(j, itr.ptr_->elements_[i]);
        }
        itr.ptr_->element_erase(itr.offset_);// Clear the rest of array
      }
      itr.ptr_->element_insert(itr.offset_, v);// Insert the value
      return iterator(new_node);
    }
    // If the node is not full, just insert the element at the iterator location
  } else {
    itr.ptr_->element_insert(itr.offset_, v);
    return itr;// The iterator does not change
  }
}


template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
  this->size_ = old.size_;
  // Handle the special case of an empty list.
  if (this->size_ == 0) {
    this->head_ = this->tail_ = NULL;
  }
  // Create a new head node.
  this->head_ = new Node<T>(old.head_->elements_);
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  this->tail_ = this->head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    this->tail_->next_ = new Node<T>(old_p->elements_);
    this->tail_->next_->prev_ = this->tail_;
    this->tail_ = this->tail_->next_;
    old_p = old_p->next_;
  }
}

// Delete the whole list
template <class T>
void UnrolledLL<T>::destroy_list() {
  memory_clear(head_);
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

template <class T>
void UnrolledLL<T>::memory_clear(Node<T>* node) {
  if (node != tail_) {
    memory_clear(node->next_);
  }
  delete node;
}

template <class T>
void UnrolledLL<T>::push_front(const T& v) {
  iterator b = begin();
  insert(b, v);
  /* Here can increase the memory performance
  Keeping every node 50% full. After pushing front, moving the elements of next
  node to fill in the new node to reach 50% capacity.
   */
}

template <class T>
void UnrolledLL<T>::pop_front() {
  if (size_ == 0) { // Error check
    std::cerr << "Empty list! Unable to pop front!" << std::endl;
    exit(1);
  }
  iterator b = begin();
  erase(b);
}

/*
Here can increase memory performance
Keeping every node in 50% full status. If the number of elements in the
current node plus a new element can exceed the 50% capacity of new node,
creating a new node and moving elements to it. 
Basicly, keeping every node in 50% capacity.
*/
template <class T>
void UnrolledLL<T>::push_back(const T& v) {
  ++size_;
  if (tail_->num_elements_ == NUM_ELEMENTS_PER_NODE) { // Node is full
    Node<T>* new_node = new Node<T>;
    new_node->next_ = NULL;
    new_node->prev_ = tail_;
    tail_->next_ = new_node;
    tail_ = new_node;
    new_node->element_insert(0, v);
  } else {// Node is not full
    tail_->element_insert(tail_->num_elements_, v);
  }
}

template <class T>
void UnrolledLL<T>::pop_back() {
  if (size_ == 0) { // Error check
    std::cerr << "Empty list! Unable to pop back!" << std::endl;
    exit(1);
  }
  iterator e = end();
  erase(e);
}

template <class T>
void UnrolledLL<T>::print(std::ostream& output) const {
  output << "UnrolledLL, size: " << size_ << std::endl;
  Node<T>* new_node = head_;
  while (new_node) {
    output << " node:[" << new_node->num_elements_ << "]";
    for (int i = 0; i < new_node->num_elements_; i++){
      if (!(new_node->elements_[i])) {
        break;
      }
      output << " " << new_node->elements_[i];
    }
    output << std::endl;
    new_node = new_node->next_;
  }
}


// do these lists look the same (length & contents)?
template <class T>
bool UnrolledLL<T>::operator== (UnrolledLL<T>& right) {
  if (this->size_ != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = this->begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != this->end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}

template <class T>
bool UnrolledLL<T>::operator!= (UnrolledLL<T>& right){ return !(*this==right); }

#endif