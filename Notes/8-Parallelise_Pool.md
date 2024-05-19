```
void pool_forward(float * restrict X, Pool_Layer * l,float * restrict Y)

#pragma acc kernels present (X,l,Y)

```
```
pool_forward:
    162, Generating update device(X[:l->in_depth*(l->in_height*l->in_width)])
         Generating present(l[:],Y[:],X[:])
    164, Loop carried dependence due to exposed use of Y prevents parallelization
         Generating NVIDIA GPU code
        164, #pragma acc loop seq
        166, #pragma acc loop seq
        168, #pragma acc loop seq
        172, #pragma acc loop vector(128) collapse(2) /* threadIdx.x */
             Generating implicit reduction(max:max)
        173,   /* threadIdx.x auto-collapsed */
    166, Loop carried dependence due to exposed use of Y prevents parallelization
    168, Loop carried dependence due to exposed use of Y prevents parallelization
    172, Loop is parallelizable
    173, Loop is parallelizable
    190, Generating update self(Y[:l->out_size])
    ```