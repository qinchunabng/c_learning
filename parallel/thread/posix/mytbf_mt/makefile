CFLAGS+=-pthread
LDFLAGS+=-pthread

all:mytbf_mt

mytbf_mt:main.o mytbf.o
	$(CC) $^ $(CFLAGS) -o $@ $(LDFLAGS)

clean:
	rm -rf *.o mytbf_mt