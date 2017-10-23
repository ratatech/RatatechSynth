#!/usr/bin/python

import serial, time
import numpy as np


## FOURIER SERIES Synthesize a signal by means of the fourier series
#
# Synthesize a band-limited signal by means of the Fourier series. The 
# synthesis equation is described as:
# 
#   x(t) = a_0 + SUM( a_n*np.cos(2*np.pi*f*t*n)) - SUM( b_n*np.sin(2*np.pi*f*t*n))
#
# Where the a_0 is the DC bin, and a_n / b_n are the conp.sine and np.sine 
# amplitude coefficients. Well described on the book "The Scientist and 
# Engineer's Guide to Digital Signal Procesnp.sing", Chapter 13- Continuous 
# Signal Procesnp.sing.  
class FourierSeries(object):

    def __init__(self,N,A,type):

        
        self.N = N
        self.A = A
        self.type = type
        self.t = np.arange(0,N);
    
    def quatize(self,y,B):
        if B == 8:
            yq = np.int8(np.round(y*2**(B-1)));
        elif B == 16:
            yq = np.int16(np.round(y*2**(B-1)));
        elif B == 32:
            yq = np.int32(np.round(y*2**(B-1)));

        return(yq)
    
    def get_coeffs(self,n):
        
        # Define coefficients for each different shape.
        if(self.type == 'squ'):
            a_n = ((4*self.A)/(n*np.pi))*np.sin(n*np.pi/2);
            b_n = 0;
        elif(self.type == 'saw'):
            a_n = 0;
            b_n = (2*self.A/(n*np.pi));
        elif(self.type == 'tri'):
            a_n = (4*self.A*(1-(-1)**n))/((n*np.pi)**2);
            b_n = 0;
        
            
        return(a_n,b_n)
    
    
    def process(self,Nh):
        # Init output signal
        y = 0
        
        # DC bin
        a_0 = 0
        
        # Add first the DC bin to the summation
        y = y + a_0
        
        # Iterate over harmonics
        for n in range(1,Nh):
            
            # Low pass filter designed with the Lanczos sigma factor 
            # used to mitigate waveform artefacts due to the Gibbs 
            # phenomenon. More info on the book "Digital Waveform
            # Genearation", chapter 5- DDS arbitrary waveform
            # generation.
            Hk = ((Nh)/(n*np.pi)) * np.sin((n*np.pi)/(Nh))
            #Hk = 1;
            # Get the coefficients
            [a_n,b_n] = self.get_coeffs(n)

            y = y + Hk * a_n * np.cos(n*2*np.pi*self.t/(self.N)) - Hk * b_n * np.sin(n*2*np.pi*self.t/(self.N)) 
            
        return(self.quatize(y, 16))