CC = gcc
CFLAGS = -Wall -pedantic

compile: task1/main.out task2/main.out task3/main.out task4/main.out

task1: task1/main.out task1/input.txt
	echo "\n"
	cat task1/input.txt
	echo "\n"
	(cd task1 && ./main.out)

task2: task2/main.out task2/input.txt
	echo "\n"
	cat task2/input.txt
	echo "\n"
	(cd task2 && ./main.out)

task3: task3/main.out task3/input.txt
	echo "\n"
	cat task3/input.txt
	echo "\n"
	(cd task3 && ./main.out)

task4:  task4/input.txt task4/main.out
	echo "\n"
	cat task4/input.txt
	echo "\n"
	(cd task4 && ./main.out)

task1/main.out: task1/main.c
	$(CC) $(CFLAGS) -g $< -o $@

task2/main.out: task2/main.c
	$(CC) $(CFLAGS) -g $< -o $@

task3/main.out: task3/main.c
	$(CC) $(CFLAGS) -g $< -o $@

task4/main.out:  task4/src/main.c task4/src/AdjacencyList.c task4/src/List.c task4/include/AdjacencyList.h task4/include/List.h
	$(CC) $(CFLAGS) -g task4/src/*.c -o $@ -I task4/include/

clean:
	rm task1/*.out
	rm task2/*.out
	rm task3/*.out
	rm task4/*.out
