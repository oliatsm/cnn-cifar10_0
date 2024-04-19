# Υλοποίηση σειριακού κώδικα

## Φόρτωση εικόνων CIFAR-10

Αρχικά διαβάζουμε τα

## Υλοποίηση Επιπέδων

### Αρχιτεκτονική Δικτύου

Karpathi - Convjs

* structs
* make layers
* forward 
    * Convolution
    * ReLU
    * Pooling
    * Fully Connected
    * Softmax
* free layers
* load parameters
    * Snapshot

## Κυρίως πρόγραμμα
![Flow Chart](image/flow-chart-en.png)

Memory allocations

Net Forward

Calculate Net Results and Accuracy

Free memory allocated
### Variables:

* `labels`: Array to store image labels.
input: 2D array to store image data.
* `L1, L2, ..., L11`: Pointers to different types of network layers (Conv_Layer, ReLU_Layer, Pool_Layer, FC_Layer, Softmax_Layer).
* `O1, O2, ..., O11`: Pointers to outputs of each layer.
* `predictions`: Array to store predicted labels.

### Layer Structures
