CC=clang
CFLAGS=-ggdb -O0


wavelet.o: wavelet.c
	$(CC) $(CFLAGS) -c wavelet.c -o wavelet.o

haar.o: haar.c circ_array.o
	$(CC) $(CFLAGS) -c haar.c -o haar.o

daubechies.o: daubechies.c haar.o circ_array.o
	$(CC) $(CFLAGS) -c haar.o daubechies.c -o daubechies.o

circ_array.o: circ_array.c
	$(CC) $(CFLAGS) -c circ_array.c -o circ_array.o

testing.o: tests.c haar.o wavelet.o daubechies.o
	$(CC) $(CFLAGS) tests.c haar.o wavelet.o daubechies.o -o testing.o

test: testing.o
	./testing.o

debug-test: testing.o
	gdb testing.o

all: wavelet.o haar.o testing.o daubechies.o circ_array.o

clean:
	rm *.o