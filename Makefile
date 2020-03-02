CC = gcc
CFLAGS = -Wall -pedantic

compile: build_task1

task1: build_task1
	echo "\n"
	cat task1/input.txt
	echo "\n"
	(cd task1 && ./main.out)

build_task1: task1/main.c
	$(CC) $(CFLAGS) -g $< -o task1/main.out

clean:
	rm task1/*.out
