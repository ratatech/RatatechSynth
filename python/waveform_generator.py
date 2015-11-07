import numpy as np
import matplotlib.pyplot as plt


# N = 2**5;
# t = np.arange(0,N, dtype=np.float)
# sinWave = np.int16(np.floor(np.sin(t*2*np.pi/N)*(2**8-1)/2))
# 
# t = np.linspace( 0, 1, N )
# exp_line =  ( 1 - np.exp(-(1/t*44100)))
# print exp_line
# plt.plot(exp_line)
# plt.show()


###############################
# EXPONENTIAL TABLE GENERATION
###############################
fc_final =20e3;
fc_initial = 20;
potVal = 10e3;
potTaps = 255;
C = 1/(potVal*2*np.pi*fc_initial);
# Manually selected C
# C = 680e-9;


t = range(255, 0, -1)
eN = potTaps;
#a = 1/np.exp(t[-1]/tau);
a = 1;
tau = t[0]/np.log(eN/a);
Rfc_exp_8bit = a*np.exp(t/tau);
Rfc_lin = (t);

print(np.round(Rfc_exp_8bit))


Rfc_exp = np.round((Rfc_exp_8bit/potTaps)*potVal);
# Rfc_lin = np.round((Rfc_lin/potTaps)*potVal);
# 
fc_exp = (1/((Rfc_exp)*C*2*np.pi));
# fc_lin = (1/((Rfc_lin)*C*2*np.pi));
# 
# 

# plt.figure(1)
# plt.plot(fc_exp)
# plt.show()
 
plt.figure(2)
plt.plot(Rfc_exp_8bit)
plt.show()
