HOMEWORK 10: JOB PRIORITIZATION


NAME:  Xinhao Luo


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.
Online resources should have specific URLs

Student: Changdi Chen

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10


EXTRA CREDIT
As described in the hw.pdf create a new ElegantQueue that can function as a TimeQueue or
as an UrgentQueue. Describe the changes you had to make to main/Job, and how your ElegantQueue
supports both getting the highest urgency Job and getting the earliest Job.

I would required a string parameter when new ElegantQueue. "TQ" means time queue and "UQ" means urgent queue.
This type String will be used when printing and updating hook.
I also added some helper functions: AssignPtr, AssignIndex, etc.
These function will be called when updating hook, and these function will take actions based on type String of
current classes.
Function compare will use different attribute of Job class under different type string.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


