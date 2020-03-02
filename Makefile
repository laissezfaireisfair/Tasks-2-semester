CC = gcc
CFLAGS = -Wall -pedantic

compile: build_task1 build_task2

task1: build_task1
	echo "\n"
	cat task1/input.txt
	echo "\n"
	(cd task1 && ./main.out)

task2: build_task2
	echo "\n"
	cat task2/input.txt
	echo "\n"
	(cd task2 && ./main.out)

build_task1: task1/main.c
	$(CC) $(CFLAGS) -g $< -o task1/main.out

build_task2: task2/main.c
	$(CC) $(CFLAGS) -g $< -o task2/main.out

clean:
	rm task1/*.out
	rm task2/*.out
