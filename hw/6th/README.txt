HOMEWORK 5: UNROLLED LINKED LISTS


NAME: Xinhao Luo


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Student: Changdi Chen

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  12



TESTING & DEBUGGING STRATEGY:
1) I use GDB to go through each seg fault I have met.
2) I also add "H/T" in list's print function when printing Node so that I know that list (head_ and tail_) is properly tagged.
3) I use valgrind to check memory leak and evaluate which function causes the leak.


ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case?

n = # of elements in the node
m = # of nodes in the list

+=================+==========+
| operations\type | Unrolled |
+=================+==========+
| front           | O(1)     |
+-----------------+----------+
| back            | O(1)     |
+-----------------+----------+
| erase           | O(1)     |
+-----------------+----------+
| insert          | O(1)     |
+-----------------+----------+
| pop_front       | O(1)     |
+-----------------+----------+
| pop_back        | O(1)     |
+-----------------+----------+
| push_back       | O(1)     |
+-----------------+----------+
| push_front      | O(1)     |
+-----------------+----------+
| print           | O(m*n)   |
+-----------------+----------+
| copy_list       | O(m*n)   |
+-----------------+----------+
| destroy_list    | O(m)     |
+-----------------+----------+


Difference:
1) UnrolledLL can hold multiple elements in one node, while dslist and std::list hold only one at a time.
UnrolledLL won't need to allocate memory again if node is not full when adding while others need to allocate each time when adding new elements.
And Unrolled won't need to relink nodes if deleting an elements won't lead to an empty node.
2) Iterator of UnrolledLL need to keep track of both node and offset in order to locate an element, while others won't need offset.
3) std::list support operation -- on end()
4) both dslist and UnrolledLL don't have reverse_iterator

Inefficient:
If a node contain only one element, and we need to erase it.
UnrolledLL::erase->Node::erase->Node::isEmpty->UnrolledLL::erase_node

We need to remove the element and remove the node as well, when each node's average # of node is 1.

EXTRA CREDIT:
If the # of elements in the list changes with function pop/push/insert/erase, I will do a check over the node that being modified:

1) Acquire its neighbourhoods
    a) next, next_num(# of element in next node)
    b) prev, prev_num(# of element in prev node)
2) If current node is < 50% filled, and next or prev can be merged into one node, then merge.
3) Or borrow one element from next/prev to make current node 50% filled.

These operations is actually O(1) since it is not influence by the n and m mentioned above in order notation section.
CheckMerge is only influenced by the NUM_ELEMENTS_PER_NODE:
The larger the number the more time it costs to merge/split nodes.

MISC. COMMENTS TO GRADER:
Some operator and constructor function are written inline either because they are short or it gives errors when I try to move them outside.
I hope those inline won't causes grading issue.

