CC=nvc
CFLAGS= -Minfo=all

cnn: simple-cnn.c layers.c
	$(CC) -o $@ simple-cnn.c layers.c $(CFLAGS)

.PHONY : clean

clean:
	rm -f *.o cnn
