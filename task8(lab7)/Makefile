CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

SOURCES = src/Errors.c src/solution.c src/Dictionary.c src/List.c src/String.c
HEADERS = include/Errors.h include/Dictionary.h include/List.h include/String.h

run: main.out input.txt
	echo "\n"
	cat input.txt
	echo "\n"
	./main.out

test1: test1.out
	echo "\n"
	./test1.out

clean:
	rm *.out

main.out: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ -I include/

test1.out: test/test1-List.c include/Errors.h include/List.h include/String.h src/Errors.c src/List.c src/String.c
	$(CC) $(CFLAGS) src/Errors.c src/List.c src/String.c test/test1-List.c $@ -I include/
