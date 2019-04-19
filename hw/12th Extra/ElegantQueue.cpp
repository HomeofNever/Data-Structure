#include "Job_extra.h"
#include "ElegantQueue.h"


// Remove the first element and return it
// and re-organized heap
Job *ElegantQueue::pop() {
  Job * j = top();
  swap(0, last_index());
  queue.pop_back();
  percolate_down(0);

  return j;
}

// Add a new element and re-organize heap
void ElegantQueue::push(Job *job) {
  assignPtr(job);

  queue.push_back(job);
  unsigned int index = last_index();
  assignIndex(queue.back(), index);
  percolate_up(index);
}

// Print Current Quene's heap
void ElegantQueue::printHeap(std::ostream &stream) const {
  stream << type << ' ';
  stream << queue;
}

// Remove node by index and re-organize heap
void ElegantQueue::remove_from_index(unsigned int index) {
  swap(index, last_index());
  queue.pop_back();
  percolate_down(index);
}

// Swap elements by given indexes, and update hooks
void ElegantQueue::swap(unsigned int x, unsigned int y) {
  Job * t = queue[x];
  queue[x] = queue[y];
  queue[y] = t;

  // Update hook
  assignIndex(queue[x], x);
  assignIndex(queue[y], y);
}

// Action percolate on heap from given index
void ElegantQueue::percolate_down(unsigned int index) {
  while (index < queue.size()) {
    unsigned int left = index * 2 + 1;
    unsigned int right = index * 2 + 2;
    unsigned int smaller = index;

    // Find the smallest
    if (left < queue.size() &&
        compare(queue[left], queue[smaller])) {
      smaller = left;
    }

    if (right < queue.size() &&
        compare(queue[right], queue[smaller])) {
      smaller = right;
    }

    // If the same, do nothing and exit
    if (smaller == index) {
      break;
    } else {
      swap(smaller, index);
      index = smaller;
    }
  }
}

// Action percolate up on heap from given index
void ElegantQueue::percolate_up(unsigned int index) {
  while (index > 0) {
    unsigned int parent = (index - 1) / 2;
    if (compare(queue[index], queue[parent])) {
      swap(index, parent);
      index = parent;
    } else {
      break;
    }
  }
}

// Compare two job based on type
bool ElegantQueue::compare(Job *first, Job *second) const {
  if (getType()) {
    return first->timestamp < second->timestamp;
  } else {
    return first->priority > second->priority;
  }
}

// Get bool on types
bool ElegantQueue::getType() const {
  return type == "TQ";
}

// Assign Job with proper ptr
void ElegantQueue::assignPtr(Job *j) {
  if (getType()) {
    j->time_ptr = this;
  } else {
    j->priority_ptr = this;
  }
}

// Assign Job with proper Index
void ElegantQueue::assignIndex(Job *j, unsigned int index) {
  if (getType()) {
    j->time_hook = index;
  } else {
    j->urgent_hook = index;
  }
}
