all:compute
CFLAGS+=-Wall

compute:main.o stack.o llist.o
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) compute *.o -r