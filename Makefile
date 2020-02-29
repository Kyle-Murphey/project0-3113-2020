all: project0

main.o: project0.c
	gcc -c project0.c

main: project0.o
	gcc project0.o -o project0

clean:
	rm -f *.o project0
