#include "Python.h"
#include "numpy/arrayobject.h"
// #include "C_arraytest.h"
// #include <Python.h>

// Function 1: A simple 'hello world' function
static PyObject* helloworld(PyObject* self, PyObject* args)
{
    printf("Hello World\n");
    return Py_None;
}

// Function 2: A C fibonacci implementation
// this is nothing special and looks exactly
// like a normal C version of fibonacci would look
int Cfib(int n)
{
    if (n < 2)
        return n;
    else
        return Cfib(n-1)+Cfib(n-2);
}
// Our Python binding to our C function
// This will take one and only one non-keyword argument
static PyObject* fib(PyObject* self, PyObject* args)
{
    // instantiate our `n` value
    int n;
    // if our `n` value
    if(!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    // return our computed fib number
    return Py_BuildValue("i", Cfib(n));
}


/* a preexisting C-level function you want to expose -- e.g: */
static double total(double* data, int len)
{
    double total = 0.0;
    int i;
    for(i=0; i<len; ++i)
        total += data[i];
    return total;
}

/* here is how you expose it to Python code: */
static PyObject *totalDoubles(PyObject *self, PyObject *args)
{
    PyObject* seq;
    double *dbar;
    double result;
    int seqlen;
    int i;

    /* get one argument as a sequence */
    if(!PyArg_ParseTuple(args, "O", &seq))
        return 0;
    seq = PySequence_Fast(seq, "argument must be iterable");
    if(!seq)
        return 0;

    /* prepare data as an array of doubles */
    seqlen = PySequence_Fast_GET_SIZE(seq);
    dbar = malloc(seqlen*sizeof(double));
    if(!dbar) {
        Py_DECREF(seq);
        return PyErr_NoMemory(  );
    }
    for(i=0; i < seqlen; i++) {
        PyObject *fitem;
        PyObject *item = PySequence_Fast_GET_ITEM(seq, i);
        if(!item) {
            Py_DECREF(seq);
            free(dbar);
            return 0;
        }
        fitem = PyNumber_Float(item);
        if(!fitem) {
            Py_DECREF(seq);
            free(dbar);
            PyErr_SetString(PyExc_TypeError, "all items must be numbers");
            return 0;
        }
        dbar[i] = PyFloat_AS_DOUBLE(fitem);
        printf("in iter: %d - val: %.2f\n", i, dbar[i]);
        Py_DECREF(fitem);
    }    

    /* clean up, compute, and return result */
    Py_DECREF(seq);
    result = total(dbar, seqlen);
    free(dbar);
    return Py_BuildValue("d", result);
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



static PyObject *total_cont(PyObject *self, PyObject *args)
{
    PyArrayObject *vecin, *vecout;  // The python objects to be extracted from the args
    double *cin, *cout;             // The C vectors to be created to point to the 
                                    //   python vectors, cin and cout point to the row
                                    //   of vecin and vecout, respectively
    int i,j,n;
    const char *str;
    double dfac;
    PyObject *pyStr = NULL;


    printf("====HELLO 0\n");
    
    /* Parse tuples separately since args will differ between C fcns */
    if (!PyArg_ParseTuple(args, "O!O!sd", &PyArray_Type, &vecin,
        &PyArray_Type, &vecout, &str, &dfac))  {printf("RIDI\n");return NULL;}
    if (NULL == vecin)  {printf("RIDI 2\n");return NULL;}
    if (NULL == vecout)  {printf("RIDI 3\n");return NULL;}

    printf("====HELLO 1\n");
    
    // Print out input string
    printf("Input string: %s and double: %.2f\n", str, dfac);
    
    /* Check that objects are 'double' type and vectors
         Not needed if python wrapper function checks before call to this routine */
    if (not_doublevector(vecin)) return NULL;
    if (not_doublevector(vecout)) return NULL;
    
    /* Change contiguous arrays into C * arrays   */
    cin=pyvector_to_Carrayptrs(vecin);
    cout=pyvector_to_Carrayptrs(vecout);
    
    /* Get vector dimension. */
    n=vecin->dimensions[0];
    
    /* Operate on the vectors  */
    for ( i=0; i<n; i++)  {
            cout[i]=dfac*cin[i]*cin[i];
    }
        
    return Py_BuildValue("i", 1);
}





// Our Module's Function Definition struct
// We require this `NULL` to signal the end of our method
// definition
static PyMethodDef myMethods[] = {
    { "helloworld", helloworld, METH_NOARGS},
    { "fib", fib, METH_VARARGS},
    { "total", totalDoubles, METH_VARARGS},
    { "total_cont", total_cont, METH_VARARGS},
    { NULL, NULL}
};

// Our Module Definition struct
// static struct PyModuleDef myModule = {
//     "myModule",
//     "Test Module",
//     -1,
//     myMethods
// };

// Initializes our module using our above struct
// PyMODINIT_FUNC 
void initmyModule()
{
    Py_InitModule("myModule", myMethods);
    import_array();  // Must be present for NumPy.  Called first after above line.
}
