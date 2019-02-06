HOMEWORK 3: RESIZABLE TABLE


NAME: Xinhao Luo


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Website: StackOverflow
Student: Changdi Chen

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  5



ORDER NOTATION:

Write each answer in terms of n = the number of rows and m = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get O(1)

set O(1)

numRows O(1)

numColumns O(1)

push_back_row O(n)

push_back_column O(n^m)

pop_back_row O(n)

pop_back_column O(n^m)

print O(n^m)


TESTING & DEBUGGING STRATEGY:
Discuss your strategy for testing & debugging your program.
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Table class design & implementation?

GDB, Valgrind, cout and assert.
Use BatchTest() with parameters large.txt and 10,000, and check memory usage in task manager.

EXTRA CREDIT:
Indicate here if you implemented push_back for multiple rows or
multiple columns and/or rewrote your code using pointers instead of
subscripts for extra credit.  Also document the order notation for
your multi-row and multi-column push_back functions.

push_back_rows O(n)

push_back_columns O(n^m)


MISC. COMMENTS TO GRADER:
(optional, please be concise!)
I make use of multi-line comment in .h file at the top of each function since I sometimes add note over parameter types.
I think it won't make my code looks sparse as it is a standard to do so.
And I have not written so much on each function's head section since most of them are implemented at the bottom or just really simple with one line.
