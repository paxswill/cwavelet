CC=clang
CFLAGS="-g -O0"


wavelet.o: wavelet.c haar.o
	$(CC) $(CFLAGS) wavelet.c -o wavelet.o

haar.o: haar.c
	$(CC) $(CFLAGS) haar.c -o haar.o


