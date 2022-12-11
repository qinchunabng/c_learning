all:btree
CFLAGS+=-Wall

btree:main.o 
	$(CC) $^ $(CFLAGS) -o $@ -lqueue -lllist

clean:
	$(RM) stack *.o -r