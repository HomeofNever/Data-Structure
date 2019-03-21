HOMEWORK 7: SPATIALLY-EMBEDDED ADJACENCY MAPS


NAME:  Xinhao Luo


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Student: Changdi Chen

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 10


ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity along with a short
justification for each of the functions below:

n: The total number of users
l: The total number of users with a location
d: The total number of users with degree >= 1
m: The total number of connections
p: The number of users that a function will print out

* Define q as the number of friends one user have.

loadConnections(O(m * log m)): Iterate over the connections in the file, and insert into the map (worst case)

loadLocations(O(l * log(l))): Iterate over users that provided locations, and insert into the map (worst case)

printAllUsersWithinDistance(O(l)): Iterate over users with locations and calculate locations

printDegreesHistogram(O(n)): Iterate over all users and identify if their degrees >= 1

printDegreesOfAll(O(n)): Iterate over all users and collect degrees

printFriendsWithDegree(O(q * log(n))): Go through each friends and find in the adj_list; then collect their degrees

printFriendsWithinDistance(O(q * log(n))): Go through each friends and find in the adj_list; then calculate distances

printUsersWithinIDRange(O(n)): Iterate over all users(worst case) and calculate if it is in offset


MISC. COMMENTS TO GRADER:  

Since I cannot add extra function, in order to prevent int overflow, I copy the if code to calculate the diff
in function printUsersWithinIDRange(). I hope this is not considered as bad code style.






