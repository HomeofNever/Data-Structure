HOMEWORK 9: IMDB SEARCH


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


HASH FUNCTION DESCRIPTION

I used the one provided in lab 9 that will hash a string to an unsigned int.


HASH TABLE IMPLEMENTATION

I converted each query into a string: e.g. title-year-length-actors...
if there is a field that is unknown, I would use placeholder "?" to build the query

When adding an movie into the hashtable, I would go through all possible queries of that movie (64 in total),
and hash queries into int then put into the table.
I use linear probing to solve possible collision of different queries.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


