CC = gcc
program: src/tictac.c
	$(CC) src/tictac.c -lpaho-mqtt3c -o tictactoe