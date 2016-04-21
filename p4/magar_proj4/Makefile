all: main

kapsack.o: knapsack.h knapsack.c
	gcc -Wall -g -c knapsack.c

greedy.o: greedy.h greedy.c
	gcc -Wall -g -c greedy.c

bruteforce.o: bruteforce.h bruteforce.c
	gcc -Wall -g -c -lm bruteforce.c

backtracking.o: backtracking.h backtracking.c
	gcc -Wall -g -c backtracking.c

main.o: main.c
	gcc -Wall -g -c main.c

main: main.o knapsack.o bruteforce.o greedy.o backtracking.o
	gcc -Wall -g main.o knapsack.o bruteforce.o greedy.o backtracking.o -lm -o main
clean:
	rm *.o *~ main

