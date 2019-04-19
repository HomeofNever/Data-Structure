#include "Job.h"

// Pop on current heap and return
// will Re-organize heap
Job *UrgentQueue::pop() {
  Job * j = top();
  swap(0, last_index());
  queue.pop_back();
  percolate_down(0);

  return j;
}

// Add new element to queue
void UrgentQueue::push(Job *job) {
  // Update hook
  job->priority_ptr = this;
  queue.push_back(job);
  unsigned int index = last_index();
  queue.back()->urgent_hook = index;

  // Organize heap
  percolate_up(index);
}

void UrgentQueue::printHeap(std::ostream &stream) const {
  stream << "UQ ";
  stream << queue;
}

void UrgentQueue::remove_from_index(unsigned int index) {
  swap(index, last_index());
  queue.pop_back();
  percolate_down(index);
}

// Swap two element with index, and update hook
void UrgentQueue::swap(unsigned int x, unsigned int y) {
  Job * t = queue[x];
  queue[x] = queue[y];
  queue[y] = t;

  // Update hook
  queue[x]->urgent_hook = x;
  queue[y]->urgent_hook = y;
}

// Action percolate down on heap starts from given index
void UrgentQueue::percolate_down(unsigned int index) {
  while (index < queue.size()) {
    unsigned int left = index * 2 + 1;
    unsigned int right = index * 2 + 2;
    unsigned int smaller = index;

    // Find the smallest
    if (left < queue.size() &&
        queue[left]->priority > queue[smaller]->priority) {
      smaller = left;
    }

    if (right < queue.size() &&
        queue[right]->priority > queue[smaller]->priority) {
      smaller = right;
    }

    // If same, do nothing and break;
    if (smaller == index) {
      break;
    } else {
      swap(smaller, index);
      index = smaller;
    }
  }
}

// Action percolate up on heap start from given index
void UrgentQueue::percolate_up(unsigned int index) {
  while (index > 0) {
    unsigned int parent = (index - 1) / 2;
    if (queue[index]->priority > queue[parent]->priority) {
      swap(index, parent);
      index = parent;
    } else {
      break;
    }
  }
}
