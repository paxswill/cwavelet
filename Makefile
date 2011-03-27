CC=clang
CFLAGS=-g -O0


wavelet.o: wavelet.c haar.o
	$(CC) $(CFLAGS) -c wavelet.c -o wavelet.o

haar.o: haar.c
	$(CC) $(CFLAGS) -c haar.c -o haar.o

testing.o: tests.c haar.o wavelet.o
	$(CC) $(CFLAGS) tests.c haar.o wavelet.o -o testing.o

test: testing.o
	./testing.o

all: wavelet.o haar.o testing.o

clean:
	rm *.o