all: project0

project0.o: project0.c
	gcc -c project0.c

project0: project0.o
	gcc project0.o -o project0

clean:
	rm -f *.o project0
