# Δέσμευση μνήμης

## Κλασσικός Τρόπος - Pointer σε Pointer
Για μεγάλους πίνακες (arrays), κλασσικός τρόπος δέσμευσης μνήμης στην C γίνεται με ένα διπλό pointer για κάθε γραμμή, και δέσμευση σε κάθε pointer των στοιχείων της κάθε γραμμής. Η δέσμευση μνήμης δεν είναι συνεχόμενη.
 ```c
    //Allocate
    float **input=(float **)malloc(sizeof(float*)*N);
    if(input==NULL) return 1; // Check if the allocation failed

    for (int i=0;i<N;i++){
        input[i] = (float *)malloc(sizeof(float)*M);
        if(input[i]==NULL) return 1;
    }

    //Free
    for (int i=0;i<N;i++){
        free(input[i]);
    }
    free(input);

 ```
 Τυπώνοντας τις διευθύνσεις κάθε στοιχείου του πίνακα:
 ```c
 Input[4][3]
Addresses of input[i]:
0x6193984416f0 0x6193984416f8 0x619398441700 0x619398441708 

Addresses of input[i][j]:
0x619398441720 0x619398441724 0x619398441728 
0x619398441740 0x619398441744 0x619398441748 
0x619398441760 0x619398441764 0x619398441768 
0x619398441780 0x619398441784 0x619398441788 
```
> οι pointer `input(i)` είναι συνεχόμενοι.  
> Τα στοιχεία κάθε γραμμής είναι συνεχόμενα. Οι γραμμές έχουν διαφορά 32 byte για Μ<32.  


 
 ## Συνεχόμενη Δέσμευση Μνήμης

 :arrow_right: Εάν ο αριθμός των στοιχείων των της κάθε γραμμής δεν είναι πολύ μεγάλος:

 ```c
    float (*input)[Μ]=malloc(sizeof(*input)*N);

 ```
 Με αυτό τον τρόπο οι θέσεις μνήμης είναι συνεχόμενες και γίνεται μόνο ένα `malloc`.
 
 ```c
Input[4][3]
 Addresses of input[i]:
0x6193984416b0 0x6193984416bc 0x6193984416c8 0x6193984416d4 
Addresses of input[i][j]:
0x6193984416b0 0x6193984416b4 0x6193984416b8 
0x6193984416bc 0x6193984416c0 0x6193984416c4 
0x6193984416c8 0x6193984416cc 0x6193984416d0 
0x6193984416d4 0x6193984416d8 0x6193984416dc 
```
> οι θέσεις μνήμης είναι συνεχόμενες, κάθε pointer `input(i)` δείχνει στο πρώτο στοιχείο τις κάθε γραμμής.  

:arrow_right: Εάν ο αριθμός των στοιχείων και των δύο διαστάσεων είναι πολύ μεγάλος:

```c
float **input=(float **)malloc(sizeof(float*)*N);
    input[0] = malloc(M*N*sizeof(float));

    for (int i=1;i<N;i++){
        input[i] = input[i-1]+M;
    }
```

```c
Addresses of input[i]:
0x6193984417a0 0x6193984417a8 0x6193984417b0 0x6193984417b8 
Addresses of input[i][j]:
0x6193984417d0 0x6193984417d4 0x6193984417d8 
0x6193984417dc 0x6193984417e0 0x6193984417e4 
0x6193984417e8 0x6193984417ec 0x6193984417f0 
0x6193984417f4 0x6193984417f8 0x6193984417fc 
```
> δεσμεύεται χώρος χωριστά για τους pointer κάθε γραμμής, τα στοιχεία είναι συνεχόμενα.

Εναλλακτικά:
```c
float **input=(float **)malloc(sizeof(float*)*N+sizeof(float)*(N*M));
input[0] = (float*)(input + N);

    for (int i=1;i<N;i++){
        input[i] = input[i-1]+M;
    }
```
```c
Addresses of input[i]:
0x55e6e40b1810 0x55e6e40b1818 0x55e6e40b1820 0x55e6e40b1828 
Addresses of input[i][j]:
0x55e6e40b1830 0x55e6e40b1834 0x55e6e40b1838 
0x55e6e40b183c 0x55e6e40b1840 0x55e6e40b1844 
0x55e6e40b1848 0x55e6e40b184c 0x55e6e40b1850 
0x55e6e40b1854 0x55e6e40b1858 0x55e6e40b185c 
```
> οι pointers είναι συνεχόμενα και με τα δεδομένα.

---

