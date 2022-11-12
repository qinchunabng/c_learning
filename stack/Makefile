all:stack
CFLAGS+=-Wall

stack:main.o stack.o llist.o
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) stack *.o -r