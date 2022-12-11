OBJS=main.o mytool1.o mytool2.o
CC=gcc
CFLAGS+=-c -Wall -g

mytool:$(OBJS)
	$(CC) $^ -o $@

%.o:%c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o mytool -r