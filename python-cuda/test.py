import numpy as np
import gpuadder

def test():
	# gpuadder.helloworld()
    arr = np.array(range(1000), dtype=np.float)
    arr_out = np.array(arr)
    gpuadder.helloworld_input(arr, arr_out, 3.3)
    print arr_out

test()
