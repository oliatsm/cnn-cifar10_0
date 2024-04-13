# Εκτέλεση κώδικα με nvc compiler

## Συνάρτηση `Load_data()`

Στη συνάρτηση που φορτώνει τα δεδομένα του cifar-10, ο nvc compiler παρουσίασε σφάλμα:

```
$ make
nvc -g -Minfo=all -c11 -Wall -Wextra -march=native -o cnn-cifar10 main.c

$ ./cnn-cifar10 
Batches: 6, Samples: 0.
Loading input batch 1...
Segmentation fault (core dumped)
```

Το σφάλμα συμβαίνει στην επανάληψη n=2650, στη δήλωση της μεταβλητής `uint8_t data[LINE_SIZE];` η οποία δηλώνετε μέσα στο loop:
```c
int load_data(int **image, int * label, int N) {
    
    /*...Code...*/
    size_t LINE_SIZE = 3073;
    for (int b=1;b<batches;b++){
        printf("Loading input batch %d...\n", b);

        /*...Code...*/

        for (int i = 0; i < MAX_BATCH_DATA; i++) {

            uint8_t data[LINE_SIZE];

            size_t bytesRead = fread(data, 1, LINE_SIZE, fbin);
            assert(bytesRead == LINE_SIZE);

            label[n] = data[0];
            size_t data_i=1;
            for (int j = 0; j < IMAGE_PIXELS && data_i<LINE_SIZE; j++) {
                image[n][j] = (int)data[data_i++];
            }
            n++;
        }
        assert((n%MAX_BATCH_DATA)==0);
        fclose(fbin);
    }

    /*... Code..*/
}
```

ο κώδικας τρέχει κανονικά εάν το `uint8_t data[LINE_SIZE];` δηλωθεί έξω από το loop:

```c
int load_data(int **image, int * label, int N) {
    
    /*...Code...*/
    
    for (int b=1;b<batches;b++){
        printf("Loading input batch %d...\n", b);

        /*...Code...*/

        uint8_t data[LINE_SIZE];

        for (int i = 0; i < MAX_BATCH_DATA; i++) {

            size_t bytesRead = fread(data, 1, LINE_SIZE, fbin);
            assert(bytesRead == LINE_SIZE);

            label[n] = data[0];
            size_t data_i=1;
            for (int j = 0; j < IMAGE_PIXELS && data_i<LINE_SIZE; j++) {
                image[n][j] = (int)data[data_i++];
            }
            n++;
        }
        assert((n%MAX_BATCH_DATA)==0);
        fclose(fbin);
    }

    /*... Code..*/
}
```
# SOLVED

Δήλωση του `LINE_SIZE` με `#define`. Λειτουργεί κανονικά. 
```c
#define LINE_DATA 3073

//...

int load_data(int **image, int * label, int N) {
    
    /*...Code...*/
    size_t LINE_SIZE = 3073;
    for (int b=1;b<batches;b++){
        printf("Loading input batch %d...\n", b);

        /*...Code...*/

        for (int i = 0; i < MAX_BATCH_DATA; i++) {

            uint8_t data[LINE_SIZE];

            size_t bytesRead = fread(data, 1, LINE_SIZE, fbin);

            label[n] = data[0];
            size_t data_i=1;
            for (int j = 0; j < IMAGE_PIXELS && data_i<LINE_SIZE; j++) {
                image[n][j] = (int)data[data_i++];
            }
            n++;
        }
        fclose(fbin);
    }

    /*... Code..*/
}
```