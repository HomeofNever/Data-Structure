HOMEWORK 6: CROSSWORD BLACKOUT


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



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h)
The number of words in the dictionary (d)?
The total number of spaces with a letter (l)?
The total number of blacked out spaces (b)?
The number of constraints (c)?
Etc.
-------------
Unique number of constraints: (u)
number of words with certain length: (l)
number of letters of certain words: (t)
number of appearance of each constraints: (a), may varies based on different u

There are three stages: search for all possible words: so I need to go through the grid once. which is O(w*h).
Within each search, I need to go though dict once, which is O(log(d))
After search stages, I need to do combination from each constraints which is nearly: O(l^a)
And mixed each kind of solutions, so the final order notation should be: foreach u, O(u*(l^a))
In Pre-check stage, I need to go though word list and the letter of each word: O(l*t)
In Post-check stage, I need to go though the external block of word: O(l*t)


DESCRIPTION OF YOUR ADDTIONAL PUZZLES/DICTIONARIES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).

file: dict.txt and puzzle.txt
I make this one for testing nyt1_mini exception and gc extra credit:
by adding a word next to each other in dictionary, the one next one should not/also be considered.
Adding a new constraint also help sometimes.

(and it is not interested!)

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND
ON YOUR ADDITIONAL PUZZLES/DICTIONARIES:
# of solutions & approximate wall clock running time for different
puzzles / dictionaries for a single solution or all solutions. Be
specific about which puzzle/dictionary/parameters you were timing.

.------------------------------------.---------------.---------------------------.
|                Test                | # of solution | Runing time(all_solution) |
:------------------------------------+---------------+---------------------------:
| blackout1(dict1)                   |             3 | <1s                       |
:------------------------------------+---------------+---------------------------:
| blackout2(dict1)                   |             0 | <1s                       |
:------------------------------------+---------------+---------------------------:
| blackout3(dict1)                   |             9 | <1s                       |
:------------------------------------+---------------+---------------------------:
| nyt1_mini_1                        |             1 | <1s                       |
:------------------------------------+---------------+---------------------------:
| reverse_ell(both test)             |             1 | <1s                       |
:------------------------------------+---------------+---------------------------:
| sporcle1_constraintsA(dict1,3,4)   |             1 | <=1s                      |
:------------------------------------+---------------+---------------------------:
| sporcle1_constraintsA(dict2)       |             1 | ~1mins                    |
:------------------------------------+---------------+---------------------------:
| sporcle1_constraintsB(dict1,2,3,4) |            40 | <1s                       |
:------------------------------------+---------------+---------------------------:
| puzzle(dict)[myself]               |            15 | <1s                       |
'------------------------------------'---------------'---------------------------'

Note: one_solution mode has similar timing, and gc is not included.

MISC. COMMENTS TO GRADER:
I leave some print methods for debug purpose, and there may also some duplicate code for different position.
Hope this won't hurt my grade on style XD.