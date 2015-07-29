import numpy as np
import matplotlib.pyplot as plt

"""
N = 2**8;
t = np.arange(0,N, dtype=np.float)
sinWave = np.int16(np.floor(np.sin(t*2*np.pi/N)*(2**16-1)/2))
"""


FS = 96000
N = 2**8
f = 17000

env_lut = range(128,-128,-1);
print env_lut
#for items in env_lut:
#    print items','

