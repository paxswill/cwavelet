# Makefile for the main src

all: wavelet.o haar.o daubechies.o circ_array.o

.PHONY: clean all

clean:
	rm *.o

wavelet.o: wavelet.c wavelet.h
	$(CC) $(CFLAGS) -c $< -o $@

haar.o: haar.c haar.h
	$(CC) $(CFLAGS) -c $< -o $@

daubechies.o: daubechies.c daubechies.h
	$(CC) $(CFLAGS) -c $< -o $@

circ_array.o: circ_array.c circ_array.h
	$(CC) $(CFLAGS) -c $< -o $@
