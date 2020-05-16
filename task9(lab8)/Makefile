CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

SOURCES = src/Errors.c src/main.c src/Matrix.c src/Queue.c src/Sequence.c
HEADERS = include/Constants.h include/Errors.h include/Matrix.h include/Queue.h include/Sequence.h

run: main.out in.txt
	echo "\n"
	cat in.txt
	echo "\n"
	./main.out
	echo "\n"
	cat out.txt

clean:
	rm *.out

main.out: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ -I include/
