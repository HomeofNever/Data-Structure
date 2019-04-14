#include "Job.h"

Job *UrgentQueue::pop() {
  Job * j = top();
  swap(0, last_index());
  queue.pop_back();
  percolate_down(0);

  return j;
}

void UrgentQueue::push(Job *job) {
  job->priority_ptr = this;
  queue.push_back(job);
  unsigned int index = last_index();
  queue.back()->urgent_hook = index;
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

void UrgentQueue::swap(unsigned int x, unsigned int y) {
  Job * t = queue[x];
  queue[x] = queue[y];
  queue[y] = t;

  queue[x]->urgent_hook = x;
  queue[y]->urgent_hook = y;
}

void UrgentQueue::percolate_down(unsigned int index) {
  while (index < queue.size()) {
    unsigned int left = index * 2 + 1;
    unsigned int right = index * 2 + 2;
    unsigned int smaller = index;

    if (left < queue.size() &&
        comparePriotity((*queue[left]), (*queue[smaller]))) {
      smaller = left;
    }

    if (right < queue.size() &&
        comparePriotity((*queue[right]), (*queue[smaller]))) {
      smaller = right;
    }

    if (smaller == index) {
      break;
    } else {
      swap(smaller, index);
      index = smaller;
    }
  }
}

void UrgentQueue::percolate_up(unsigned int index) {
  while (index > 0) {
    unsigned int parent = (index - 1) / 2;
    if (comparePriotity((*queue[index]), (*queue[parent]))) {
      swap(index, parent);
      index = parent;
    } else {
      break;
    }
  }
}
