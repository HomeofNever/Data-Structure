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



EXTRA CREDIT:
If the # of elements in the list changes with function pop/push/insert/erase, I will do a check over the node that being mod



MISC. COMMENTS TO GRADER:
Optional, please be concise!

