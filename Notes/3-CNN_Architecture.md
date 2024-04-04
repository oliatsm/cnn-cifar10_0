#  Αρχιτεκτονική Νευρωνικού Δικτύου

Το Νευρωνικό Δίκτυο που υλοποιήθηκε έχει την παρακάτω ακολουθία από επίπεδα:

* 1.Convolutional Layer:
        in[32][32][3],out[32][32][16]
        Filters[5][5][3]x(16), stride:1,pad:2
* 2.ReLu Layer:
        in[32][32][16],out[32][32][16]
* 3.Pool Layer:
        in[32][32][16],out[16][16][16]
        pooling(2,2),stride:2,pad:0
* 4.Convolutional Layer:
        in[16][16][16],out[16][16][20]
        Filters[5][5][16]x(20), stride:1,pad:2
* 5.ReLu Layer:
        in[16][16][20],out[16][16][20]
* 6.Pool Layer:
        in[16][16][20],out[8][8][20]
        pooling(2,2),stride:2,pad:0
* 7.Convolutional Layer:
        in[8][8][20],out[8][8][20]
        Filters[5][5][20]x(20), stride:1,pad:2
* 8.ReLu Layer:
        in[8][8][20],out[8][8][20]
* 9.Pool Layer:
        in[8][8][20],out[4][4][20]
        pooling(2,2),stride:2,pad:0
* 10.Fully Connected Layer:
        in[4][4][20],out[1][1][10]
* 11.Softmax Layer:
        in[1][1][10],out[1][1][10]

 Την αρχιτεκτονική και τα προεκπαιδευμένα βάρη τα πήραμε από το [ConvNetJS CIFAR-10 demo](https://cs.stanford.edu/people/karpathy/convnetjs/demo/cifar10.html) το οποίο είναι ένα Συνελικτικό Νευρωνικό Δίκτυο για το σύνολο δεδομένων CIFAR-10 το οποίο εκτελείται σε browser. Τα εκπαιδευμένα βάρη είναι αποθηκευμένα σε 4 αρχεία; layer1_conv.txt, layer4_conv.txt, layer7_conv.txt και layer10_fc.txt και αντιστοιχούν στα επίπεδα του νευρωνικού δικτύου με εκπαιδεύσιμα βάρη.

 ## Πλήρως διασυνδεμένο επίπεδο

Για να αναπαραστήσουμε το πλήρως διαδυνδεμένο επίπεδο δημιουργούμε το `struct fc_layer`. Επειδή οι έξοδοι των προηγούμενων επιπέδων είναι τρισδιάστατοι πίνακες και το πλήρως διασυνδεμένω επίπεδο έχει σαν είσοδο μονοδιάστατο πίνακα, διατηρούμε την πληροφορία των διαστάσεων εισόδου στο `struct` ώστε να υπάρχει σωστή αντιστοίχηση των δεδομένων εισόδου με τα βάρη του επιπέδου. 

Τα δεδομένα εξόδου αποθηκεύονται με την εξής μορφή `Οutput[Depth][Height][Width]`. Τα βάρη του πλήρως διασυνδεμένου επιπέδου είναι αποθηκευμένα στο αρχείο 'layer10_fc.txt' ανά βάθος. Δηλάδή το κάθε βάρος αντιστοιχεί σε έξοδο του προηγούμενου επιπέδου `O[Height][Width][Depth]`. Για αυτό το λόγο διαβάζουμε τα δεδομένα με τον παρακάτω τρόπο:
```c
for(int i = 0; i < l->out_depth; i++){  
        for(int h=0;h<l->in_height;h++){
            for(int w=0;w<l->in_width;w++){
                for(int d=0;d<l->in_depth;d++){
                    int idx = w+(h+d*l->in_height)*l->in_width+i*l->in_neurons;
                    fscanf(fin, "%lf", &val);
                    l->weights[idx]=(float)val;
        }}}
    }

```
 