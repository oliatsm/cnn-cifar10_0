# Makefile for cnn-cifar10 project

CC = nvc
CFLAGS = -Minfo=all -c11 -Wall -Wextra -march=native -pg

SRC = main_acc.c layers_acc.c malloc2D.c
EXECUTABLE = cnn-cifar10-acc

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)
