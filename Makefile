CC=gcc

trap: trap.c
	$(CC) -fopenmp -o trap trap.c -lm
