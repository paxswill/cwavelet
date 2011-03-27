CC=clang
CFLAGS=-ggdb -O0


wavelet.o: wavelet.c
	$(CC) $(CFLAGS) -c wavelet.c -o wavelet.o

haar.o: haar.c
	$(CC) $(CFLAGS) -c haar.c -o haar.o

daubechies.o: haar.o
	$(CC) $(CFLAGS) -c haar.o daubechies.c -o daubechies.o

testing.o: tests.c haar.o wavelet.o daubechies.o
	$(CC) $(CFLAGS) tests.c haar.o wavelet.o daubechies.o -o testing.o

test: testing.o
	./testing.o

all: wavelet.o haar.o testing.o daubechies.o

clean:
	rm *.o