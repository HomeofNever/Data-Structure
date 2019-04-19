#ifndef __URGENTQ_H_
#define __URGENTQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>

typedef unsigned int uq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class UrgentQueue{
public:
    // Accessors
    Job * top() const { return queue[0]; };

    // Mutators
    Job * pop();
    void push(Job* job);
    void remove_from_index(unsigned int index);

    void printHeap(std::ostream & stream) const;

private:
    std::vector<Job*> queue;

    void swap(unsigned int x, unsigned int y);

    void percolate_down(unsigned int index);
    void percolate_up(unsigned int index);

    // Helper
    unsigned int last_index() const { return queue.size() - 1; }
};

#endif
