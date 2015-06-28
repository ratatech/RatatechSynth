import numpy as np
import matplotlib.pyplot as plt

"""
N = 2**8;
t = np.arange(0,N, dtype=np.float)
sinWave = np.int16(np.floor(np.sin(t*2*np.pi/N)*(2**16-1)/2))
"""


FS = 96000
N = 2**12
f = 17000

phInc = (np.float(N)/FS)*f
K = phInc-np.floor(phInc)
fracPart = np.uint16((phInc-np.floor(phInc))*N)
phInc_16 = np.left_shift(np.uint16(phInc),4) + fracPart
print phInc
print np.left_shift(np.uint16(phInc),4)
print fracPart
print phInc_16
print K

phInd = 0
ascending = 1
triangle = np.array([])
triangleInt = np.array([])
triangleFrac = np.array([])

nSamples = 100

triangle= np.append(triangle,0)
triangleFrac = np.append(triangleFrac,0)
triangleInt= np.append(triangleInt,np.floor(0))
phIndFrac = 0
sampleRef =0
for i in range(0,nSamples):
    
        
        
    if ascending:         
        phInd = phInd+ phInc
        phIndFrac = (phInd-sampleRef)*K
        phIndFrac = sampleRef+phIndFrac
        sampleRef = phInd
    else:
        phInd = phInd-phInc
        phIndFrac = (sampleRef-phInd)*K
        phIndFrac = sampleRef-phIndFrac
        sampleRef = phInd

    if phInd >= N:
        ascending = 0
        #phInd = np.left_shift(N,0)
    if phInd <= 0:
        ascending = 1 
        #phInd = 0  
                       
    
    triangle = np.append(triangleFrac,phInd)
    triangleInt= np.append(triangleInt,np.floor(phInd))
    triangleFrac= np.append(triangleFrac,phIndFrac)

#print triangleFrac
#print triangleInt


fig1 = plt.figure()
plt.plot(triangleInt,'o')
plt.plot(triangleFrac,'mo')
plt.plot(triangleFrac)
plt.plot((0,nSamples), (N,N), 'r-')
plt.plot((2.8,2.8), (N,N), 'b-')
plt.show()
