# from distutils.core import setup, Extension

# setup(name = 'myModule', version = '1.0',  ext_modules = [Extension('myModule', ['helloworld.c'])])

from distutils.core import setup, Extension
import numpy as np

module1 = Extension('myModule', sources = ['helloworld.c'])

setup (name = 'myModule', 
	version = '1.0', 
	description = 'This is a demo package', 
	include_dirs = [np.get_include()], 
	ext_modules = [module1]
)

