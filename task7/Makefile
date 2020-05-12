CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

SOURCES = src/Errors.c src/main.c src/Matrix.c src/Permutations.c src/Sequence.c
HEADERS = include/Errors.h include/Matrix.h include/Permutations.h include/Sequence.h

run: main.out input.txt
	echo "\n"
	cat input.txt
	echo "\n"
	./main.out

clean:
	rm *.out

main.out: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ -I include/
