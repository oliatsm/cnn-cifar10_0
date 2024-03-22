# Επίπεδο Συνέλιξης

Χ: διάνυσμα εισόδου
Weights: τα βάρη - φίλτρα
Y: έξοδος

Διαστάσεις διανυσμάτων  
    Height, Width, Depth=Channel
    Kernels, number of Filters, Padding,
    Output H,W,C
X: W_in,H_in,C_in
Weights:  [K x K, C] F, P[valid if =floor((K-1)/2)], S
Y:  W_out=(W_in-K+2*P)/S+1,
    H_out=(H_in-K+2*P)/S+1,
    D_out=F


