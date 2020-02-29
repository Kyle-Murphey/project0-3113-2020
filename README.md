Kyle Murphey, Project 0

Compile: make all or gcc -c project0.c -o project0

Run: cat file | ./project0

Bugs: Any character that is outside the range of values would not get displayed.

I assume all characters are in either unicode or ascii.

The main function loops through the file, stores them, and then diplays the characters in descending order.
The storeChar function stores the characters based on whether or not they are unicode.
The compare function compares two _uni_chars and returns a value for qsort.

Sources:
	https://www.cprogramming.com/tutorial/unicode.html
	Linux man pages