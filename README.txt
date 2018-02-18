README:
This program directory includes a makefile and can be compiled using the 'make' command. 'make clean' can be used to remove all object files and executables, leaving only source code. 

CONTENTS:
prog_assign_1.c : main program file

input_validation.c/input_validation.h : contain functions for collecting and validating user input

person_hash.c/person_hash.h : contain functions for hash table operations, as well as constants defining hash table size and maximum allowed number of friends

INSTRUCTIONS:
This program takes no command line arguments.
This program supports the following commands:

P <name> : creates and stores a person with the given name

F <name1> <name2> : if the listed people exist, records that they are friends

U <name1> <name2> : if the listed people are friends, records that they are no longer friends

L <name> : if the listed person exists, list their friends

Q <name1> <name2> : if the listed people exist, print whether or not they are friends

X : terminates the program

* NOTE: the program currently supports a maximum of 25 friends per person. If this is insufficient, you can change the constant MAX_NUM_FRIENDS located in person_hash.h


