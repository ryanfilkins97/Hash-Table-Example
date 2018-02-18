HW1: prog_assign_1.o person_hash.o input_validation.o
	gcc -g prog_assign_1.o person_hash.o input_validation.o -o HW1 -lm
prog_assign_1.o: prog_assign_1.c person_hash.h input_validation.h
	gcc -g -c prog_assign_1.c
person_hash.o: person_hash.c person_hash.h
	gcc -g -c person_hash.c -lm
input_validation.o: input_validation.c input_validation.h
	gcc -g -c input_validation.c
clean: 
	rm *.o HW1