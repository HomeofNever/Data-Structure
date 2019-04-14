#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>

typedef unsigned int tq_hook; //Used to point to a location in the heap, fill in the "???"

class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class TimeQueue{
public:
    Job * top() const {
      return queue[0];
    }

    Job * pop();

    void push(Job* job);

    void printHeap(std::ostream & stream) const;

    void remove_from_index(unsigned int index);

private:
    std::vector<Job*> queue;

    void swap(unsigned int x, unsigned int y);

    void percolate_down(unsigned int index);
    void percolate_up(unsigned int index);

    unsigned int last_index() const { return queue.size() - 1; }
};

#endif
