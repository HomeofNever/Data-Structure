HOMEWORK 8: ROPES


NAME:  Xinhao Luo


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Student: Changdi Chen

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  12

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Extremely Unbalanced rope: for each parents, it has a leaf node on its right and the rest of the node on its right

Copy Constructor:
1) O(2^p + m)
2) O(m + 2 * p)

No matter what condition, we need to copy the whole string once.
For Balance tree, we also need to visit each node once. The number of node is 2^p - 1, which can be seen as 2^p.
For extreme unbalance rope, every leaf node in the rope has the longest value (like single char)
and each of them has the longest path as well.


Construct from Node*:
1) O(p)
2) O(p)

constructing from Node* requires to calculate the size of the tree.
So it has the same big-O as sum() function.
Sum function goes deep into the right tree.

Index:
1) O(p)
2) O(p)

Since no matter it is a balance tree or not, it has to reach the longest path to reach a leaf.

Report:
1) O(v * log(p))
2) O(v * p)

I use index for report function and on average index works as log(p) for each characters.
While in extreme condition, it just goes through the tree v times as the string length required.

iterator operator++:
1) O(p)
2) O(p) / O(1) if it only has one way

For each time when reaching the leaf, we need to go to the parents, and next we may need to go right down
the bottom again, which should be 2 * p.

Split:
1) O(p^2)
2) O(p)

For balance tree, we need to go from the target leaf and straight to the root (iterator == nullptr) and cut each of them.
However, for balance tree, each time we need to re-calculate the weight of the nodes from the tree cut down, while
extreme we don't (just +1 for the new right node).

Concat:
1) O(2^p + m)
2) O(p + m)

Concat will have to calculate the sum of the left tree (for the root's weight).
No matter what condition, we need to go to the left-most leaf.

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

- use GDB to go step by step when something goes wrong
- write error message when encounter exceptions
- test corner cases and use assert to test them
- Observe print() result
- write test cases for each function


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

