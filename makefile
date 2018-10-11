CC = gcc
SRC = ./src/

cat: $(SRC)cat.c
	$(CC) -o cat $(SRC)cat.c
