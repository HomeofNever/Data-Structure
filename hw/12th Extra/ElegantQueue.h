#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>

typedef unsigned int hook; //Used to point to a location in the heap, fill in the "???"

class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class ElegantQueue{
public:
    ElegantQueue(const std::string& str): type(str) {};

    // Actions
    Job * top() const { return queue[0]; }
    Job * pop();
    void push(Job* job);
    void remove_from_index(unsigned int index);

    void printHeap(std::ostream & stream) const;

private:
    std::vector<Job*> queue;
    std::string type = "";

    // Actions
    void swap(unsigned int x, unsigned int y);

    void percolate_down(unsigned int index);
    void percolate_up(unsigned int index);

    // Helpers
    bool compare(Job * first, Job * second) const;
    bool getType() const;
    void assignPtr(Job * j);
    void assignIndex(Job * j, unsigned int index);
    unsigned int last_index() const { return queue.size() - 1; }
};

#endif
