CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

SOURCES = src/main.c src/Matrix.c src/List.c src/Errors.c
HEADERS = include/Matrix.h include/List.h include/Errors.h

run: main.out input.txt
	echo "\n"
	cat input.txt
	echo "\n"
	./main.out

clean:
	rm *.out

main.out: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ -I include/
