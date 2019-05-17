
#include <stdio.h>
#include <iostream>
#include <cuda_runtime.h>

using namespace std;

extern void call_kernel(double *a, int N, double coeff);



int main(int argc, char const *argv[])
{
	int N = 100000;
	double *a;
	cudaMalloc((void**)&a, sizeof(double) * N);
	call_kernel(a, N, 1.0);
	double *ah = (double*) malloc(sizeof(double) * N);
	cudaMemcpy(ah, a, sizeof(double)*N, cudaMemcpyDefault);
	ah[10] = -1000;
	int max_count = 10;
	int counter = 0;
	for(int i=0;i<N;i++)
		if(ah[i] != i*1.0 && counter++ < max_count)
			cout << "Error in " << i << endl;
	return 0;
}
