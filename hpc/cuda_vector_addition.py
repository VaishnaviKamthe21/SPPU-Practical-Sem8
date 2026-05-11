%%writefile vectoradd.cu
#include <iostream>
using namespace std;

__global__ void vectorAdd(int *A, int *B, int *C) {

    int i = threadIdx.x;

    C[i] = A[i] + B[i];
}

int main() {

    int h_A[5] = {1,2,3,4,5};
    int h_B[5] = {10,20,30,40,50};
    int h_C[5];

    int *d_A, *d_B, *d_C;

    cudaMalloc((void**)&d_A, 5*sizeof(int));
    cudaMalloc((void**)&d_B, 5*sizeof(int));
    cudaMalloc((void**)&d_C, 5*sizeof(int));

    cudaMemcpy(d_A, h_A, 5*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, 5*sizeof(int), cudaMemcpyHostToDevice);

    vectorAdd<<<1,5>>>(d_A, d_B, d_C);

    cudaMemcpy(h_C, d_C, 5*sizeof(int), cudaMemcpyDeviceToHost);

    cout << "Result: ";

    for(int i=0;i<5;i++) {
        cout << h_C[i] << " ";
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}