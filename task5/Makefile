CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

run: main.out input.txt
	echo "\n"
	cat input.txt
	echo "\n"
	./main.out

clean:
	rm *.out

main.out: src/main.c src/AdjacencyList.c src/List.c include/AdjacencyList.h include/List.h
	$(CC) $(CFLAGS) src/*.c -o $@ -I include/
