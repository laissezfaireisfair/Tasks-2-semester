CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

SOURCES = src/Errors.c src/main.c src/Matrix.c src/Queue.c src/Sequence.c src/List.c src/Constants.c
HEADERS = include/Constants.h include/Errors.h include/Matrix.h include/Queue.h include/Sequence.h include/List.h

run: main.out input.txt
	echo "\n"
	cat input.txt
	echo "\n"
	./main.out
	echo "\n"
	cat output.txt

clean:
	rm *.out

main.out: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ -I include/
