Matt Zagame
Matt_Zagame@student.uml.edu
COMP3050
Assignment 7

Degree of success: 100%

This program demonstrates the use of the fork() and pipe() system calls in C.
The initial thread of the program will create a pipe for communication between
processes then fork to create the child process. Both the parent and child
processes will display information about themselves and the parent will write a
message to the child through the pipe which the child will read. If no errors
occur, both processes will exit normally.