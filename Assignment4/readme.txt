Matt Zagame
Matt_Zagame@student.uml.edu
COMP3050
Assignment 4

Degree of success: 100%

The mic1 microcode has been modified to use three new assembly instructions,
MULT, RSHIFT and DIV. To accomplish this I modified the original microcode file
to parse for three new opcode instructions and implemented a solution based on
the requirements for the assignment. My implementation of MULT follows closely
along with the solution presented in class. RSHIFT was already provided and
just needed to be slotted and parsed correctly within the microcode. For DIV I
used registers A-F to hold onto the dividend, divisor, quotient, remainder,
dividend sign, and divisor sign respectively. The division loop is an iterative
subtraction of the absolute values of the divisor from the dividend. I did not
encounter any problems with this assignment.