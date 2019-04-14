#include "Job.h"

Job *TimeQueue::pop() {
  Job * j = top();
  swap(0, last_index());
  queue.pop_back();
  percolate_down(0);

  return j;
}

void TimeQueue::push(Job *job) {
  job->time_ptr = this;
  queue.push_back(job);
  unsigned int index = last_index();
  queue.back()->time_hook = index;
  percolate_up(index);
}

void TimeQueue::printHeap(std::ostream &stream) const {
  stream << "TQ ";
  stream << queue;
}

void TimeQueue::remove_from_index(unsigned int index) {
  swap(index, last_index());
  queue.pop_back();
  percolate_down(index);
}

void TimeQueue::swap(unsigned int x, unsigned int y) {
  Job * t = queue[x];
  queue[x] = queue[y];
  queue[y] = t;

  queue[x]->time_hook = x;
  queue[y]->time_hook = y;
}

void TimeQueue::percolate_down(unsigned int index) {
  while (index < queue.size()) {
    unsigned int left = index * 2 + 1;
    unsigned int right = index * 2 + 2;
    unsigned int smaller = index;

    if (left < queue.size() &&
        compareTime((*queue[left]), (*queue[smaller]))) {
      smaller = left;
    }

    if (right < queue.size() &&
        compareTime((*queue[right]), (*queue[smaller]))) {
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

void TimeQueue::percolate_up(unsigned int index) {
  while (index > 0) {
    unsigned int parent = (index - 1) / 2;
    if (compareTime((*queue[index]), (*queue[parent]))) {
      swap(index, parent);
      index = parent;
    } else {
      break;
    }
  }
}
