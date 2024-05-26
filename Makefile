# Makefile for cnn-cifar10 project

CC = nvc
CFLAGS = -acc=gpu -Minfo=all  -c11 -Wall -Wextra -march=native #-g  -gpu=lineinfo -pg 

SRC = main.c layers.c malloc2D.c timer.c
EXECUTABLE = cnn-cifar10

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)
