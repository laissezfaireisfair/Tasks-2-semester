CC = gcc
CFLAGS = -Wall -pedantic -g

compile: task1/main.out task2/main.out task3/main.out task4/main.out task5/main.out task6/main.out task7.out

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

task5:  task5/input.txt task5/main.out
	echo "\n"
	cat task5/input.txt
	echo "\n"
	(cd task5 && ./main.out)

task6:  task6/input.txt task6/main.out
	echo "\n"
	cat task6/input.txt
	echo "\n"
	(cd task6 && ./main.out && cat output.txt)

task7:  task7/input.txt task7/main.out
	echo "\n"
	cat task7/input.txt
	echo "\n"
	(cd task7 && ./main.out && cat output.txt)

task1/main.out: task1/main.c
	$(CC) $(CFLAGS) $< -o $@

task2/main.out: task2/main.c
	$(CC) $(CFLAGS) $< -o $@

task3/main.out: task3/main.c
	$(CC) $(CFLAGS) $< -o $@

task4/main.out:  task4/src/main.c task4/src/AdjacencyList.c task4/src/List.c task4/include/AdjacencyList.h task4/include/List.h
	$(CC) $(CFLAGS) task4/src/*.c -o $@ -I task4/include/

task5/main.out:  task5/src/main.c
	$(CC) $(CFLAGS) task5/src/*.c -o $@ -I task5/include/

task6/main.out:  task6/src/main.c task6/src/Matrix.c task6/src/List.c task6/src/Errors.c task6/include/Matrix.h task6/include/List.h task6/include/Errors.h
	$(CC) $(CFLAGS) task6/src/*.c -o $@ -I task6/include/

task7/main.out:  task7/include/Errors.h task7/include/Matrix.h task7/include/Permutations.h task7/include/Sequence.h task7/src/Errors.c task7/src/main.c task7/src/Matrix.c task7/src/Permutations.c task7/src/Sequence.c
	$(CC) $(CFLAGS) task7/src/*.c -o $@ -I task7/include/

clean:
	rm task1/*.out
	rm task2/*.out
	rm task3/*.out
	rm task4/*.out
	rm task5/*.out
	rm task6/*.out
	rm task7/*.out
