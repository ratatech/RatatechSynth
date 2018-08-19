import numpy as np
import matplotlib.pyplot as plt
import datetime
import os,sys
from FourierSeries import FourierSeries
from ADSR import ADSR


def writeTableContent(data,tableStr,isMultDim):
    
    lineBreakCtr = 0
        
    tables = data
    if not isMultDim:      
        tables = np.array([[],data])
        
    for subTable in tables:
        if isMultDim:
            tableStr = tableStr + '{'
        for element in subTable:
            tableStr = tableStr + str(element) + ','
            lineBreakCtr = lineBreakCtr + len(str(element)) + 1
            if (lineBreakCtr)>=100:
                tableStr = tableStr + '\n'
                lineBreakCtr = 0  
        if isMultDim:          
            tableStr = tableStr + '},'
            
    return tableStr
    
def writeTable(name,N,data,type,isConst=True,macro_M=[]):
    
    lineBreakCtr = 0
    if isConst:
        constType = 'const '
    else:
        constType = ''
        
    if len(macro_M):
        isMultDim=True      
        outstring =  constType + str(type) + ' ' + str(name) + '[' + str(macro_M) + ']' + '[' + str(N) + '] = {\n'
    else:
        isMultDim=False 
        outstring = constType + str(type) + ' ' + str(name) + '[' + str(N) + '] = {\n'
    
    outstring = writeTableContent(data,outstring,isMultDim)
        
    outstring = outstring + '};'
    return outstring

# Define output file
filename = '../src/tables.cc'
fp = open(filename, 'w')

# Optionally plot the table
plotting = False


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
    but WITHOUT ANY WARRANTY without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with XXXXXXX.  If not, see <http://www.gnu.org/licenses/>
*/

#include "tables.h"

"""

# Write file header
fp.writelines(file_header)

# Common amplitude in most table calculations
AMP = 2**15-1

# Common sampling frequency
AUDIO_FS = 48000
CONTROL_FS = 16000

# Enable/disable wavetable generation
USE_LFO_TABLE = False
USE_BANDLIMITED = True
USE_ADSR_BETA_COEFFS = False

if USE_BANDLIMITED :

    '''-------------------------------------------------------------------------------
     BANDLIMITED SQUARE/SAW/TRI WAVES
    ------------------------------------------------------------------------------'''
    bits = 8
    N = 2**bits
    fs = AUDIO_FS
    a = 440
    
    for mode in ['squ','saw','tri']:
    
        midi = np.array([])
        for x in range(0,127+1):
           midi = np.append(midi,(np.double(a) / 32) * (2 ** (np.double(x - 9) / 12)))
        
        # Define the number of octaves to be included as wavetables
        octaves = np.append(midi[23:-1:12],midi[-1])
        
        # Init variables
        wavetables = np.int16(np.zeros(256))
        wavetable = np.array([])
        max_ripple = 0.0278668934426245; # Empirical ripple observation. To be changed in each case, to avoid
                                         # Clipping or negative to positive int16 jumps
        A = 1-max_ripple
        
        # Create fourier series object
        fos = FourierSeries(N,A,mode)
        
        # Iterate over octaves
        
        for i in range(0,len(octaves)):
            # Current frequency
            freq = octaves[i]
        
            # Total number of harmonics that fit in our frequency without
            # producing aliasing, i.e. frequencies below Nyquist (Nh<fs/2)
            Nh = int(np.floor((np.double(fs)/2)/freq))
           
            # Fourier series synthesis
            wavetable = fos.process(Nh)
            
            # Store tables
            if len(wavetable) == N:        
                wavetables = np.vstack((wavetables,wavetable))
        
        wavetables = wavetables[1:len(wavetables),:]
        
        # Write tables to the file
        table_ind = 0
        name = mode + '_bandlim_lut_q15' 
        table_ind = table_ind + 1
        macro_N = 'LUT_' + str(bits) + '_BIT'
        macro_M = 'N_BANDLIM'
        table = writeTable(name, macro_N, wavetables, 'q15_t',macro_M=macro_M)
         
        # Write to output file
        fp.writelines(table)
        fp.writelines('\n\n')
        
        if plotting:
            plt.figure(2)
            plt.plot(np.transpose(wavetables))
            plt.show()

else:

    '''-------------------------------------------------------------------------------
     SAW TABLE
    ------------------------------------------------------------------------------'''
    bits = 9
    N = 2**bits
    t = np.floor(np.arange(-(AMP),(AMP),(float(AMP*2)/N), dtype=np.float))
     
    a = np.arange(-AMP,AMP-1,(4*AMP/(N-1)),dtype=np.float)
    b = np.arange(AMP-1,-AMP,-(4*AMP/(N-1)), dtype=np.float)
     
    t = np.append(a,a)
     
    wave = np.int16(t)
    name = 'saw_lut_q15' 
    macro_N = 'LUT_' + str(bits) + '_BIT'
    table = writeTable(name,macro_N,wave,'q15_t')
     
    if plotting:
        plt.figure(2)
        plt.plot(wave)
        plt.show()
     
    # Write to output file
    fp.writelines(table)
    fp.writelines('\n\n')
     
    '''-------------------------------------------------------------------------------
     TRIANGLE TABLE    
    ------------------------------------------------------------------------------'''
    bits = 9
    N = 2**bits
    a = np.arange(-AMP,AMP-1,(4*AMP/(N-1)),dtype=np.float)
    b = np.arange(AMP-1,-AMP,-(4*AMP/(N-1)), dtype=np.float)
     
    t = np.append(a,b)
    wave = np.int16(t)
    name = 'tri_lut_q15' 
    macro_N = 'LUT_' + str(bits) + '_BIT'
    table = writeTable(name,macro_N,wave,'q15_t')
     
    if plotting:
        plt.figure(3)
        plt.plot(wave)
        plt.show()
     
    # Write to output file
    fp.writelines(table)
    fp.writelines('\n\n')
     
    '''-------------------------------------------------------------------------------
     SQUARE TABLE
    ------------------------------------------------------------------------------'''     
    bits = 9
    N = 2**bits
     
    ones_neg = np.ones(N/2)*(-AMP-1)
    ones_pos = np.ones(N/2)*((AMP))
    wave = np.int16(np.concatenate((ones_neg,ones_pos)))
    name = 'squ_lut_q15' 
    macro_N = 'LUT_' + str(bits) + '_BIT'
    table = writeTable(name,macro_N,wave,'q15_t')
     
    if plotting:
        plt.figure(4)
        plt.plot(wave)
        plt.show()
     
    # Write to output file
    fp.writelines(table)
    fp.writelines('\n\n')

'''-------------------------------------------------------------------------------
 SINE TABLE
------------------------------------------------------------------------------'''
bits = 8
N = 2**bits
t = np.arange(0,N, dtype=np.float)
wave = np.int16(np.floor(np.sin(t*2*np.pi/N)*(AMP)))
 
name = 'sin_lut_q15' 
macro_N = 'LUT_' + str(bits) + '_BIT'
table = writeTable(name,macro_N,wave,'q15_t')
 
if plotting:
 
    plt.figure(1)
    plt.plot(wave)
    plt.show()
 
# Write to output file
fp.writelines(table)
fp.writelines('\n\n')
 
if USE_LFO_TABLE: 
    '''-------------------------------------------------------------------------------
     LFO SINE TABLE
    ------------------------------------------------------------------------------'''
    bits = 5
    N = 2**bits
    t = np.arange(0,N, dtype=np.float)
    wave = np.int16(np.floor(np.sin(t*2*np.pi/N)*(2**8-1)/2))
     
    name = 'sin_lfo_lut_q15' 
    macro_N = 'LUT_' + str(bits) + '_BIT'
    table = writeTable(name,macro_N,wave,'q15_t')
     
    if plotting:
        plt.figure(5)
        plt.plot(wave)
        plt.show()
     
    # Write to output file
    fp.writelines(table)
    fp.writelines('\n\n')

if USE_ADSR_BETA_COEFFS:
    '''-------------------------------------------------------------------------------
     ADSR BETA EXP TABLE
    ------------------------------------------------------------------------------'''
     
    bits = 12
    N = (2**bits)
    t = np.arange(0,N, dtype=np.float)
    c = 100
    b = np.power((2**14/c),(np.divide(1.0, N-1)))
    exp_curve = np.int16(np.round(np.power(b, t)*c))
    ratio = 0.5
    print 'ADSR RATIO in q31 = '+ str(ratio*2**31)
    
    FRAME_SIZE = 32
    fs = AUDIO_FS/FRAME_SIZE
     
    beta_table = []
    time_table = np.logspace(np.log10(0.01),np.log10(5),N)
    for i in range(0,N-1):
        tau = time_table[i]
        beta = np.int32((2**31)*np.exp((-np.log((1.0 + ratio) / ratio)/(tau*fs))))
        beta_table.append(beta)
     
    name = 'adsr_beta_exp_curve_q31' 
    macro_N = 'LUT_' + str(bits) + '_BIT'
    table = writeTable(name,macro_N,beta_table,'q31_t')
     
    if plotting:
        plt.figure(6)
        plt.plot(beta_table)
        plt.show()
     
    # Write to output file
    fp.writelines(table)
    fp.writelines('\n\n')

'''-------------------------------------------------------------------------------
 ADSR ATTACK/DECAY TABLES
------------------------------------------------------------------------------'''

init_state = 0;
MAX_AMP = int('7FFF', 16)
targetRatio_att = 1;
targetRatio_dec = 0.001;
sustain_lvl_f = 0;
sustain_lvl = np.floor(sustain_lvl_f*MAX_AMP);
control_signal = MAX_AMP;

# Set state targets
ATTACK_TARGET = MAX_AMP;
DECAY_TARGET = sustain_lvl; 
RELEASE_TARGET = 0;

# Beta coeffs table generation
bits = 8
N = 2**bits;
tau = N;
beta_att = ((2**31)*np.exp(-np.log((1 + targetRatio_att) / targetRatio_att) / (tau)));
beta_dec = np.int32((2**31)*np.exp(-np.log((1 + targetRatio_dec) / targetRatio_dec) / (tau)));


# Init moving average filter
#---------------------------------------------
adsr = ADSR(sustain_lvl,init_state);
adsr.set_beta(beta_att,targetRatio_att,'ATT');
adsr.set_beta(beta_dec,targetRatio_dec,'DEC');


# Generate the AD envelope 
#---------------------------------------------
avg_mem = [];
state = 'ATT';
adsr.beta = adsr.beta_att;
adsr.base = adsr.base_att;

while 'END' not in state: 
    adsr.update()
    avg_mem.append(adsr.avg_val)
    
    if (adsr.avg_val >= ATTACK_TARGET ) and ('ATT' in state):
        adsr.base = adsr.base_dec;
        adsr.beta = adsr.beta_dec;
        att_table = avg_mem
        avg_mem = []
        state = 'DEC'; 
      
    if adsr.avg_val <= DECAY_TARGET and ('DEC' in state):
        
        dec_table = [MAX_AMP] + avg_mem
        state = 'END';
     
# Configure exp attack table to write  
data_type = 'q15'
name = 'adsr_att_exp_' + data_type 
macro_N = 'LUT_' + str(bits) + '_BIT'
table = writeTable(name,macro_N,att_table, data_type + '_t',isConst=False)
  
# Write to output file
fp.writelines(table)
fp.writelines('\n\n')

# Configure exp decay table to write 
name = 'adsr_dec_exp_' + data_type 
macro_N = 'LUT_' + str(bits) + '_BIT'
table = writeTable(name,macro_N,dec_table, data_type + '_t',isConst=False)
  
# Write to output file
fp.writelines(table)
fp.writelines('\n\n')

if plotting:
    plt.figure(10)
    plt.plot(att_table+dec_table)
    plt.show()


'''-------------------------------------------------------------------------------
 ADSR TIME2PHASEINC TABLE
------------------------------------------------------------------------------'''
bits_adc = 12
N = (2**bits_adc)
bits_lut = 8
LUT_LENGHT = (2**bits_lut)
SHIFT_PHASE = (2**23)
FS = AUDIO_FS
FRAME_SIZE = 32
min_time_exp = 0.01
max_time_exp = 1
min_time_lin = 1
max_time_lin = 5
adsr_ph_table = []
 
times_exp = np.linspace(min_time_exp,max_time_exp,N/2)
times_lin = np.linspace(min_time_lin,max_time_lin, N - N/2 + 2)
times = np.append(times_exp,times_lin[1:-1])

for time in times:
    ph_inc = np.uint32(((float(LUT_LENGHT)/(FS/FRAME_SIZE))/time)*SHIFT_PHASE)
    adsr_ph_table.append(ph_inc)
     

name = 'adsr_time_phinc_lut' 
macro_N = 'ADSR_TIME_PHINC_LUT_SIZE'
table = writeTable(name,macro_N,adsr_ph_table,'uint32_t')
 
# Write to output file
fp.writelines(table)
fp.writelines('\n\n')
 
'''-------------------------------------------------------------------------------
 MIDI2FREQ TABLE
------------------------------------------------------------------------------'''
bits_midi = 7
N = (2**bits_midi)
midi_table = np.array([])
 
for midi_num in range(0,N):
    midi_table = np.append(midi_table,np.floor(np.power(2,(midi_num-69)/12.0)*440*10000)/10000)
 
name = ' midi_freq_lut' 
macro_N = 'MIDI_FREQ_LUT_SIZE'
table = writeTable(name,macro_N,midi_table,'double')
 
# Write to output file
fp.writelines(table)
fp.writelines('\n\n')
 
'''-------------------------------------------------------------------------------
 MIDI2PHASEINC TABLE
------------------------------------------------------------------------------'''
bits_midi = 7
N = (2**bits_midi)
bits_lut = 8
LUT_LENGHT = (2**bits_lut)
SHIFT_PHASE = (2**23)
fs = 48000
midi_ph_table = []
 
for midi_num in range(0,N):
    freq = np.floor(np.power(2,(midi_num-69)/12.0)*440*10000)/10000
    ph_inc = np.uint32(((float(LUT_LENGHT)/fs)*freq)*SHIFT_PHASE)
    midi_ph_table.append(ph_inc)
     
 
name = ' midi_phinc_lut' 
macro_N = 'MIDI_PHINC_LUT_SIZE'
table = writeTable(name,macro_N,midi_ph_table,'uint32_t')
 
# Write to output file
fp.writelines(table)
fp.writelines('\n\n')
 
'''-------------------------------------------------------------------------------
 LFO PHASEINC TABLE
------------------------------------------------------------------------------'''
bits_adc = 12
N = (2**bits_adc)
bits_lut = 8
LUT_LENGHT = (2**bits_lut)
SHIFT_PHASE = (2**23)
FS = AUDIO_FS
FRAME_SIZE = 32
min_freq = 0.1
max_freq = 50
lfo_ph_table = []
 
freqs = np.linspace(min_freq,max_freq,N)
for freq in freqs:
    ph_inc = np.uint32(((float(LUT_LENGHT)/(FS/FRAME_SIZE))*freq)*SHIFT_PHASE)
    lfo_ph_table.append(ph_inc)
     
 
name = ' lfo_phinc_lut' 
macro_N = 'LFO_PHINC_LUT_SIZE'
table = writeTable(name,macro_N,lfo_ph_table,'uint32_t')
 
# Write to output file
fp.writelines(table)
fp.writelines('\n\n')

'''-------------------------------------------------------------------------------
 MIDI2BANDLIMIND
------------------------------------------------------------------------------'''
bits = 7
N = (2**bits)
SHIFT_PHASE = (2**23)
N_TABLES = 10;
fs = AUDIO_FS
freqs = []
 
for midi_num in range(0,N):
    freq = np.floor(np.power(2,(midi_num-69)/12.0)*440*10000)/10000
    freqs.append(freq)
    
midi2inc = (np.ceil(np.log2(np.ceil((freqs)/octaves[0]))))
midi2inc = np.array(midi2inc)
midi2inc = midi2inc.astype(int)

name = ' midi_bandlim_inds_lut' 
macro_N = 'MIDI_BANDLIM_INDS_LUT_SIZE'
table = writeTable(name,macro_N,midi2inc,'uint8_t')

# Write to output file
fp.writelines(table)
fp.writelines('\n\n')

'''-------------------------------------------------------------------------------
 DITHERING 
------------------------------------------------------------------------------'''
# bits = 7
# N = (2**bits)
# SHIFT_PHASE = (2**23)
# N_TABLES = 10;
# fs = AUDIO_FS
# freqs = []
#  
# for midi_num in range(0,N):
#     freq = np.floor(np.power(2,(midi_num-69)/12.0)*440*10000)/10000
#     freqs.append(freq)
#     
# midi2inc = (np.ceil(np.log2(np.ceil((freqs)/octaves[0]))))
# midi2inc = np.array(midi2inc)
# midi2inc = midi2inc.astype(int)

# Number of bits to be enhanced by the dithering
M = 4

for i in np.arange(0,2**M):
    pattern = np.concatenate((np.zeros(2**M - i,int),np.ones(i,int)),0); 
    if not i:
        ditheringPatterns = pattern
    else:
        ditheringPatterns = np.vstack((ditheringPatterns,pattern))

name = ' dithering_lut' 
macro_N = 'DITHERING_LUT_SIZE'
table = writeTable(name, macro_N, ditheringPatterns, 'uint8_t',macro_M=macro_N)

# Write to output file
fp.writelines(table)
fp.writelines('\n\n')


'''-------------------------------------------------------------------------------
 FILE END. Do not intend to write anything after this... 
------------------------------------------------------------------------------'''
fp.close()

print('Table generation successful!!!')
