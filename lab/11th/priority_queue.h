//
// Created by NeverBehave on 2019-04-09.
//

#ifndef INC_11TH_PRIORITY_QUEUE_H
#define INC_11TH_PRIORITY_QUEUE_H
#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
    std::vector<T> m_heap;

public:
    priority_queue() {}

    priority_queue( std::vector<T> const& values )
    {
        for (auto i = values.begin(); i != values.end(); i++) {
            push(*i);
        }
    }

    const T& top() const
    {
        assert( !m_heap.empty() );
        return m_heap[0];
    }

    void push( const T& entry )
    {
        m_heap.push_back(entry);
        // Find until reach the root
        int index = m_heap.size() - 1;
        while (index != 0) {
            int parent = (index - 1) / 2;
            if (m_heap[parent] > m_heap[index]) {
                T tmp = m_heap[parent];
                m_heap[parent] = m_heap[index];
                m_heap[index] = tmp;
            }
            index = parent;
        }
    }

    void percolate_down(int index) {
        while (true) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;

            int larger = index;
            if (left < m_heap.size() && m_heap[left] < m_heap[larger]) {
                larger = left;
            }

            if (right < m_heap.size() && m_heap[right] < m_heap[larger]) {
                larger = right;
            }

            if (larger != index) {
                T tmp = m_heap[larger];
                m_heap[larger] = m_heap[index];
                m_heap[index] = tmp;
                index = larger;
            } else {
                break;
            }
        }
    }

    void pop()
    {
        assert( !m_heap.empty() );
        m_heap[0] = m_heap.back();
        m_heap.pop_back();
        percolate_down(0);
    }

    int size() { return m_heap.size(); }
    bool empty() { return m_heap.empty(); }


    //  The following three functions are used for debugging.

    //  Check to see that internally the heap property is realized.
    bool check_heap( )
    {
        return this->check_heap( this->m_heap );
    }

    //  Check an external vector to see that the heap property is realized.
    bool check_heap( const std::vector<T>& heap )
    {
        if (heap.size() > 1) {
            int index = 2;
            while (index < heap.size()) {
                if (heap[(index - 1) / 2] > heap[index]) {
                    return false;
                }
                index++;
            }
        }

        return true;
    }

    //  A utility to print the contents of the heap.  Use it for debugging.
    void print_heap( std::ostream & ostr )
    {
        for ( unsigned int i=0; i<m_heap.size(); ++i )
            ostr << i << ": " << m_heap[i] << std::endl;
    }

};

template <class T>
void down( int index, int size, std::vector<T> & v )
{
    while (true) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;

        int larger = index;
        if (left < size && v[left] > v[larger]) {
            larger = left;
        }

        if (right < size && v[right] > v[larger]) {
            larger = right;
        }

        if (larger != index) {
            T tmp = v[larger];
            v[larger] = v[index];
            v[index] = tmp;
            index = larger;
        } else {
            break;
        }
    }
}

template <class T>
void heap_sort( std::vector<T> & v )
{
  int heap_size = 0;
  // Turn it to tree
  while (heap_size != v.size()) {
    if (heap_size != 0) {
      int current = heap_size;
      // Find until reach the root
      while (current != 0) {
        int parent = (current - 1) / 2;
        if (v[parent] < v[current]) {
          T tmp = v[parent];
          v[parent] = v[current];
          v[current] = tmp;
        }
        current = parent;
      }
    }

    heap_size++;
  }

  // Output
  int output = v.size() - 1;
  while (output >= 0) {
    T tmp = v[output];
    v[output] = v[0];
    v[0] = tmp;
    output--;
    heap_size--;

    down(0, heap_size, v);
  }
}

#endif //INC_11TH_PRIORITY_QUEUE_H
