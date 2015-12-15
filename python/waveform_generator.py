import numpy as np
import matplotlib.pyplot as plt
# 
# 
# # N = 2**5;
# # t = np.arange(0,N, dtype=np.float)
# # sinWave = np.int16(np.floor(np.sin(t*2*np.pi/N)*(2**8-1)/2))
# # 
# # t = np.linspace( 0, 1, N )
# # exp_line =  ( 1 - np.exp(-(1/t*44100)))
# # print exp_line
# # plt.plot(exp_line)
# # plt.show()
# 
# 
# ###############################
# # EXPONENTIAL TABLE GENERATION
# ###############################
# fc_final =20e3;
# fc_initial = 20;
# potVal = 10e3;
# potTaps = 255;
# C = 1/(potVal*2*np.pi*fc_initial);
# # Manually selected C
# # C = 680e-9;
# 
# 
# t = range(255, 0, -1)
# eN = potTaps;
# #a = 1/np.exp(t[-1]/tau);
# a = 1;
# tau = t[0]/np.log(eN/a);
# Rfc_exp_8bit = a*np.exp(t/tau);
# Rfc_lin = (t);
# 
# print(np.round(Rfc_exp_8bit))
# 
# 
# Rfc_exp = np.round((Rfc_exp_8bit/potTaps)*potVal);
# # Rfc_lin = np.round((Rfc_lin/potTaps)*potVal);
# # 
# fc_exp = (1/((Rfc_exp)*C*2*np.pi));
# # fc_lin = (1/((Rfc_lin)*C*2*np.pi));
# # 
# # 
# 
# # plt.figure(1)
# # plt.plot(fc_exp)
# # plt.show()
#  
# plt.figure(2)
# plt.plot(Rfc_exp_8bit)
# plt.show()


def writeTable(name,N,data):
    
    lineBreakCtr = 0
    outstring = 'const int16_t ' + str(name) + '[' + str(N) + '] = {'
    for element in data:
        outstring = outstring + str(element) + ','
        lineBreakCtr = lineBreakCtr + len(str(element)) + 1
        if (lineBreakCtr)>=100:
            outstring = outstring + '\n'
            outstring = outstring + '                                         '
            lineBreakCtr = 0
        
    outstring = outstring + '};'
    return outstring

# Define output file
filename = 'tables.cc'
fp = open(filename, 'w')

# Optionally plot the table
plotting = True

file_header = """/*
@file tables.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Aug 8, 2015
This file is part of XXXXXXX

    XXXXXXX is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    XXXXXXX is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with XXXXXXX.  If not, see <http://www.gnu.org/licenses/>
*/

#include "tables.h"

"""

# Write file header
fp.writelines(file_header)



'''-------------------------------------------------------------------------------
 SINE TABLE
------------------------------------------------------------------------------'''
bits = 10;
N = 2**bits;
t = np.arange(0,N, dtype=np.float)
wave = np.int16(np.floor(np.sin(t*2*np.pi/N)*(2**bits-1)/2))
name = 'sin_lut_q15_' + str(bits) + 'bit'
table = writeTable(name,N,wave)

if plotting:
    plt.figure(1)
    plt.plot(wave)
    plt.show()

# Write to output file
fp.writelines(table)
fp.writelines('\n\n')

'''-------------------------------------------------------------------------------
 SAW TABLE
------------------------------------------------------------------------------'''
bits = 8;
N = 2**bits;
t = np.arange(-128,128, dtype=np.float)
wave = np.int16(t)
name = 'saw_lut_q15_' + str(bits) + 'bit'
table = writeTable(name,N,wave)

if plotting:
    plt.figure(2)
    plt.plot(wave)
    plt.show()

# Write to output file
fp.writelines(table)
fp.writelines('\n\n')

'''-------------------------------------------------------------------------------
 SQUARE TABLE
------------------------------------------------------------------------------'''
bits = 8;
N = 2**bits;
ones_neg = np.ones(N/2)*(-N/2);
ones_pos = np.ones(N/2)*((N/2)-1);
wave = np.int16(np.concatenate((ones_neg,ones_pos), axis=1))
name = 'squ_lut_q15_' + str(bits) + 'bit'
table = writeTable(name,N,wave)

if plotting:
    plt.figure(3)
    plt.plot(wave)
    plt.show()

# Write to output file
fp.writelines(table)
fp.writelines('\n\n')


'''-------------------------------------------------------------------------------
 LFO SINE TABLE
------------------------------------------------------------------------------'''
bits = 5;
N = 2**bits;
t = np.arange(0,N, dtype=np.float)
wave = np.int16(np.floor(np.sin(t*2*np.pi/N)*(2**8-1)/2))

name = 'sin_lut_q15_' + str(bits) + 'bit'
table = writeTable(name,N,wave)

if plotting:
    plt.figure(4)
    plt.plot(wave)
    plt.show()

# Write to output file
fp.writelines(table)
fp.writelines('\n\n')

'''-------------------------------------------------------------------------------
 POT EXP TABLE
------------------------------------------------------------------------------'''
bits = 12;
N = (2**bits)-1;
t = np.arange(0,N+1, dtype=np.float)
c = 100;
b = np.power((2**14/c),(np.divide(1.0, N)));
exp_curve = np.int16(np.round(np.power(b, t)*c))

name = 'exp_curve_q15_' + str(bits) + 'bit'
table = writeTable(name,N,exp_curve)

if plotting:
    plt.figure(5)
    plt.plot(exp_curve)
    plt.show()

# Write to output file
fp.writelines(table)
fp.writelines('\n\n')

fp.close()
