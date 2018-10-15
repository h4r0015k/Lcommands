CC = gcc
SRC = ./src/

cat: $(SRC)cat.c
	$(CC) -o cat $(SRC)cat.c

ls: $(SRC)ls.c
	$(CC) -o ls $(SRC)ls.c
