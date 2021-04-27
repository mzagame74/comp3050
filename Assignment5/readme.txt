Matt Zagame
Matt_Zagame@student.uml.edu
COMP3050
Assignment 5

Degree of success: 100%

AddInput.asm takes two positive base 10 integers as input and outputs the sum
of the two integers or reports if an overflow occurred. This is done by
interacting with the mic1's polled IO at memory addresses 4092-4095. First, two
numbers are input and converted from ascii to be stored in memory. Then the two
numbers are added and lastly converted back to ascii in order to be output.
I used my own microcode to run the assembly file on the mic1 machine and also
tested to make sure it worked with the given prom_mrd.dat file as well. See
build.txt for example commands to compile and run AddInput on the mic1 machine.
