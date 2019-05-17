# ---- Link ---------------------------
_C_arraytest.so:  C_arraytest.o  C_arraytest.mak
	gcc -bundle -flat_namespace -undefined suppress -o _C_arraytest.so  C_arraytest.o

# ---- gcc C compile ------------------
C_arraytest.o:  C_arraytest.c C_arraytest.h C_arraytest.mak
	gcc -c C_arraytest.c -I. -I/Users/millad/anaconda2/include -I/Users/millad/anaconda2/lib/python2.7/site-packages/numpy/core/include -I/Users/millad/anaconda2/include/python2.7
