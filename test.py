import myModule
import numpy as np
import sys


print myModule.total([1,2,3,4,5])
n=50  # Number of columns
# Make 2 vectors
x=np.arange(float(n))
y=np.array(x)  # generate a copy of x (will be changed in vecfcn1 call)
st="I'm in a C extension."
df=2.0
try:
	r = myModule.total_cont(x,y,st,df)
	print r, y
except Exception as e:
	print "We have a problem: "
	print e

