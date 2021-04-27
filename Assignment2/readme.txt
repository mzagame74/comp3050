Matt Zagame
Matt_Zagame@student.uml.edu
COMP3050
Assignment 2

Degree of success: 100%

add_floats.c takes two positive floating point values from the user and emulates addition as well as printing each number and the result as a binary string. The program uses a union to store floating point data for the two numbers and the resulting sum. The function addFloats() is responsible for matching the exponents of the two numbers, shifting the smaller number's mantissa accordingly, then making sure overflow does not occur in the addition of the mantissas, and if necessary, incrementing the exponent. I also included a check to make sure the exponent cannot overflow if two infs are to be added. I did not encounter any issues with this program.
