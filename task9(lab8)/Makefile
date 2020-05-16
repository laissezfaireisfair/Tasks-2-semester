CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

SOURCES = Errors.c main.c Matrix.c Queue.c Sequence.c
HEADERS = Constants.h Errors.h Matrix.h Queue.h Sequence.h

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
