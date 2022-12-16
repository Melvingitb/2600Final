CC = gcc
program: src/tictac.c
	$(CC) tictac.c -lpaho-mqtt3c -o tictactoe