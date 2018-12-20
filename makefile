CC = gcc
SRC = ./src/

cat: $(SRC)cat.c
	$(CC) -o cat $(SRC)cat.c

ls: $(SRC)ls.c
	$(CC) -o ls $(SRC)ls.c

rm: $(SRC)rm.c
	$(CC) -o rm $(SRC)rm.c

cp: $(SRC)cp.c
	$(CC) -o cp $(SRC)cp.c
