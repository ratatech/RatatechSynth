import numpy as np
import matplotlib.pyplot as plt

N = 100;
t = np.arange(0,N, dtype=np.float)
sinWave = np.sin(t*2*np.pi/N)


fig1 = plt.figure()
plt.plot(sinWave)
plt.show()