# Makefile for Unit tests

all: tests.o testing

.PHONY: clean all

clean:
	rm *.o
	rm testing

tests.o: tests.c tests.h
	$(CC) $(CFLAGS) -I$(ROOTDIR)/src -c $< -o $@

VPATH = $(ROOTDIR)/src
testing: tests.o haar.o wavelet.o daubechies.o circ_array.o
	$(CC) $(CFLAGS) $^ -o $@


