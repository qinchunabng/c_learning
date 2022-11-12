all:queue
CFLAGS+=-Wall

queue:main.o queue.o llist.o
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) queue *.o -r