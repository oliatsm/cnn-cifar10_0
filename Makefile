# Makefile for cnn-cifar10 project

CC = nvc
CFLAGS = -acc -Minfo=acc -c11 -Wall -Wextra -march=native

SRC = main.c layers.c malloc2D.c tests.c
EXECUTABLE = cnn-cifar10

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)
