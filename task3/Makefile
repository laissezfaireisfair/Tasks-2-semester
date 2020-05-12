CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

run: main.out input.txt
	echo "\n"
	cat input.txt
	echo "\n"
	./main.out

clean:
	rm *.out

main.out: main.c
	$(CC) $(CFLAGS) $< -o $@
