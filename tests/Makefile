# Makefile for Unit tests

tests.o: tests.c test.h
	$(CC) $(CFLAGS) -c $< -o $@

testing: tests.o haar.o wavelet.o daubechies.o circ_array.o
	$(CC) $(CFLAGS) $^ -o $@

test: testing
	./testing

debug-test: testing
	gdb testing

clean:
	rm *.o
