export CC=clang
export CFLAGS=-ggdb -O0 -Wall -std=c99
export LDFLAGS=
export ROOTDIR=$(shell pwd)

# Keep This file from making noise
.SILENT:
