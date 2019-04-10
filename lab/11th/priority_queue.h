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

    void pop()
    {
        assert( !m_heap.empty() );
        m_heap[0] = m_heap.back();
        m_heap.pop_back();
        // Start from 1
        int index = 1;
        while (true) {
            int left = index * 2;
            int right = index * 2 + 1;
            int real_index = index - 1;
            int real_left = left - 1;
            int real_right = right - 1;

            int larger = index;
            int real_larger = real_index;
            if (real_left < m_heap.size() && m_heap[real_left] < m_heap[real_larger]) {
                real_larger = real_left;
                larger = left;
            }

            if (real_right < m_heap.size() && m_heap[real_right] < m_heap[real_larger]) {
                real_larger = real_right;
                larger = right;
            }

            if (real_larger != real_index) {
                T tmp = m_heap[real_larger];
                m_heap[real_larger] = m_heap[real_index];
                m_heap[real_index] = tmp;
                index = larger;
            } else {
                break;
            }
        }
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
void heap_sort( std::vector<T> & v )
{
    priority_queue<T> tmp = priority_queue<T>(v);

    for (auto i = v.begin(); i != v.end(); i++) {
        *i = tmp.top();
        tmp.pop();
    }
}

#endif //INC_11TH_PRIORITY_QUEUE_H
