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

phInc = np.floor((np.float(N*2)/FS)*f)
K = phInc-np.floor(phInc)

print phInc 
print K

phInd = 0

ascending = 1
triangle = np.array([])
triangleInt = np.array([])
triangleFrac = np.array([])

nSamples = 15

phIndFrac = 0
sampleRef =0
for i in range(0,nSamples):
    
        
        
    if ascending:         
        phInd = phInd + phInc
        if phInd >= N:
            phInd = N
            ascending = 0
        phIndFrac = (phInd-sampleRef)*K
        phIndFrac = sampleRef+phIndFrac
        sampleRef = (phInd)
    else:
        phInd = phInd-phInc

            
        
        phIndFrac = (sampleRef-phInd)*K
        phIndFrac = sampleRef-phIndFrac
        sampleRef = (phInd)
        if phInd < 0:
            print phInd
            phInd = 0
            phIndFrac = 0
            ascending = 1       
                


        
    
    triangle = np.append(triangleFrac,phInd)
    triangleFrac= np.append(triangleFrac,phIndFrac)   
                       
            


#print triangleFrac
#print triangleInt


fig1 = plt.figure()
plt.plot(triangle)
plt.plot(triangle,'o')
#plt.plot(triangleFrac,'mo')
plt.plot((0,nSamples), (N,N), 'r-')
plt.plot((0,nSamples), (0,0), 'r-')
plt.show()
