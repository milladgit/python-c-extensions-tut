# Python C Extensions Tutorial

## How to use?

```Python
# Python 2.x example
python setup.py build
python setup.py install
python test.py
```

Or,

```Python
# Python 2.x example
python setup.py build

# copy .so file from the ./build/lib.XXX/myModule.so folder to current folder

python test.py
```



## Python 3:

- https://tutorialedge.net/python/python-c-extensions-tutorial/
- https://docs.python.org/3/extending/extending.html
- https://stackabuse.com/enhancing-python-with-custom-c-extensions/
- https://docs.python.org/3/extending/building.html
- https://docs.python.org/3/distutils/setupscript.html


## Python 2

- https://docs.python.org/2/extending/extending.html
- https://www.oreilly.com/library/view/python-cookbook/0596001673/ch16s03.html
- https://docs.python.org/2/extending/building.html
- https://docs.python.org/2/distutils/setupscript.html


## Python 2 & 3

- https://pythonextensionpatterns.readthedocs.io/en/latest/compiler_flags.html
- Examples of how to use distutils.ccompiler: https://www.programcreek.com/python/example/95911/distutils.ccompiler


## Numpy

- https://docs.scipy.org/doc/numpy/user/c-info.how-to-extend.html
- https://docs.scipy.org/doc/numpy-1.13.0/user/c-info.how-to-extend.html
- https://scipy-cookbook.readthedocs.io/items/C_Extensions_NumPy_arrays.html
- For numpy header files in distutils: https://stackoverflow.com/questions/2379898/make-distutils-look-for-numpy-header-files-in-the-correct-place


## Building for CUDA support

- https://stackoverflow.com/questions/10034325/can-python-distutils-compile-cuda-code
- [Robert](http://rmcgibbo.org/ "Robert T. McGibbon")'s repo (from the above StackOverflow answer) for an example on how to compile CUDA codes: https://github.com/rmcgibbo/npcuda-example


## Cext folder

This is a sample code borrowed from following link: 

https://scipy-cookbook.readthedocs.io/items/C_Extensions_NumPy_arrays.html
