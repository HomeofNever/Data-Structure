#include "Job.h"

// Pop the first on heap and return
// will re-organize heap
Job *TimeQueue::pop() {
  Job * j = top();
  swap(0, last_index());
  queue.pop_back();
  percolate_down(0);

  return j;
}

// Add new element to heap and update hook
void TimeQueue::push(Job *job) {
  // Update hook
  job->time_ptr = this;
  queue.push_back(job);
  unsigned int index = last_index();
  queue.back()->time_hook = index;

  // Organize heap
  percolate_up(index);
}

void TimeQueue::printHeap(std::ostream &stream) const {
  stream << "TQ ";
  stream << queue;
}

// Remove element by index
void TimeQueue::remove_from_index(unsigned int index) {
  swap(index, last_index());
  queue.pop_back();
  percolate_down(index);
}

// Swap elements by indexes, and update hook
void TimeQueue::swap(unsigned int x, unsigned int y) {
  Job * t = queue[x];
  queue[x] = queue[y];
  queue[y] = t;

  // Update hook
  queue[x]->time_hook = x;
  queue[y]->time_hook = y;
}

// Action percolate down from given index
void TimeQueue::percolate_down(unsigned int index) {
  while (index < queue.size()) {
    unsigned int left = index * 2 + 1;
    unsigned int right = index * 2 + 2;
    unsigned int larger = index;

    // Find the smallest
    if (left < queue.size() &&
        queue[left]->timestamp < queue[larger]->timestamp) {
      larger = left;
    }

    if (right < queue.size() &&
        queue[right]->timestamp < queue[larger]->timestamp) {
      larger = right;
    }

    // Break if index is self
    if (larger == index) {
      break;
    } else {
      swap(larger, index);
      index = larger;
    }
  }
}

// Action percolate up from given index
void TimeQueue::percolate_up(unsigned int index) {
  while (index > 0) {
    unsigned int parent = (index - 1) / 2;
    if (queue[index]->timestamp < queue[parent]->timestamp) {
      swap(index, parent);
      index = parent;
    } else {
      break;
    }
  }
}
