#include <Python.h>
#include <iostream>
#include "numpy/arrayobject.h"

using namespace std;

__global__
static void kernel(double *a, int N, double coeff) {
	int index = blockDim.x * blockIdx.x + threadIdx.x;
	if(index >= N)
		return;
	a[index] = index*coeff;
}

static void call_kernel(double *a, int N, double coeff) {
	int vector_size = 256;
	int gang = (N + vector_size-1)/vector_size;
	kernel<<<gang, vector_size>>>(a, N, coeff);
}

double *pyvector_to_Carrayptrs(PyArrayObject *arrayin)  {
    int i,n;
    
    n=arrayin->dimensions[0];
    return (double *) arrayin->data;  /* pointer to arrayin data as double */
}
/* ==== Check that PyArrayObject is a double (Float) type and a vector ==============
    return 1 if an error and raise exception */ 
int  not_doublevector(PyArrayObject *vec)  {
    if (vec->descr->type_num != NPY_DOUBLE || vec->nd != 1)  {
        PyErr_SetString(PyExc_ValueError,
            "In not_doublevector: array must be of type Float and 1 dimensional (n).");
        return 1;  }
    return 0;
}


static PyObject* helloworld(PyObject* self, PyObject* args)
{
    printf("Hello World\n");
    int N = 1000;
    double *a;
    cudaMalloc((void**)&a, sizeof(double)*N);
    call_kernel(a, N, 1.0);
	double *ah = (double*) malloc(sizeof(double) * N);
	cudaMemcpy(ah, a, sizeof(double)*N, cudaMemcpyDefault);
	ah[10] = -1000;
	int max_count = 10;
	int counter = 0;
	for(int i=0;i<N;i++)
		if(ah[i] != i*1.0 && counter++ < max_count)
			cout << "Error in " << i << endl;

    return Py_None;
}


static PyObject *helloworld_input(PyObject *self, PyObject *args)
{
    PyArrayObject *vecin, *vecout;  // The python objects to be extracted from the args
    double *cin, *cout;             // The C vectors to be created to point to the 
                                    //   python vectors, cin and cout point to the row
                                    //   of vecin and vecout, respectively
    int n;
    double dfac;

    printf("====HELLO 0\n");
    
    /* Parse tuples separately since args will differ between C fcns */
    if (!PyArg_ParseTuple(args, "O!O!d", &PyArray_Type, &vecin,
        &PyArray_Type, &vecout, &dfac))  {printf("RIDI\n");return NULL;}
    if (NULL == vecin)  {printf("RIDI 2\n");return NULL;}
    if (NULL == vecout)  {printf("RIDI 3\n");return NULL;}

    printf("====HELLO 1\n");
    
    /* Check that objects are 'double' type and vectors
         Not needed if python wrapper function checks before call to this routine */
    if (not_doublevector(vecin)) return NULL;
    if (not_doublevector(vecout)) return NULL;
    
    /* Change contiguous arrays into C * arrays   */
    cin=pyvector_to_Carrayptrs(vecin);
    cout=pyvector_to_Carrayptrs(vecout);
    
    /* Get vector dimension. */
    n=vecin->dimensions[0];
    
    double *a;
    cudaMalloc((void**)&a, sizeof(double)*n);
	cudaMemcpy(a, cin, sizeof(double)*n, cudaMemcpyDefault);
    call_kernel(a, n, dfac);
	cudaMemcpy(cout, a, sizeof(double)*n, cudaMemcpyDefault);
	cudaFree(a);
        
    return Py_BuildValue("i", 1);
}


// Our Module's Function Definition struct
// We require this `NULL` to signal the end of our method
// definition
static PyMethodDef myMethods[] = {
    { "helloworld", helloworld, METH_NOARGS, "Prints Hello World" },
    { "helloworld_input", helloworld_input, METH_VARARGS},
    { NULL, NULL, 0, NULL }
};

// Initializes our module using our above struct
PyMODINIT_FUNC initgpuadder(void)
{
    Py_InitModule("gpuadder", myMethods);
	import_array();
}

