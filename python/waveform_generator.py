import numpy as np
import matplotlib.pyplot as plt


N = 2**5;
t = np.arange(0,N, dtype=np.float)
sinWave = np.int16(np.floor(np.sin(t*2*np.pi/N)*(2**8-1)/2))


print sinWave
plt.plot(sinWave)
plt.show()
