# Makefile for cnn-cifar10 project

CC = nvc
CFLAGS = -Minfo=all -c11 -Wall -Wextra -march=native #-g -pg

SRC = main_serial.c layers_serial.c malloc2D.c
EXECUTABLE = cnn-cifar10

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)
