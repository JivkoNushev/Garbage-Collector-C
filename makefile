SOURCE_F = main.c gc.c LinkedList.c wrappers.c

all:
	gcc -Wall ${SOURCE_F} -o a.o 	

clear:
	rm *.o