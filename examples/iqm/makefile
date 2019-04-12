CC = gcc
CFLAGS=-ggdb
LDFLAGS=-lraylib -lm
OBJ=obj/iqm.o

main: iqm
	$(CC) -o iqm.exe $(OBJ) $(LDFLAGS)
iqm: iqm.c
	$(CC) -c iqm.c -o obj/iqm.o $(CFLAGS)
