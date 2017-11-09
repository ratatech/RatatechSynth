#!/usr/bin/python

import serial, time
import numpy as np


## ADSR
#
class ADSR(object):

    def __init__(self,sustainLevel,init_state):
        
        self.sustainLevel = sustainLevel;
        self.avg_val = 0;
        self.state = init_state;  
        self.att_scl = 1;
        self.beta = 0
    
    
    # Update time constant
    def set_beta(self,beta,targetRatio,state):
        
        if 'ATT' in state:
            self.beta_att = beta;
            self.base_att = np.int32((np.int64(((2**31 + targetRatio*2**31) * (2**31 - (self.beta_att))))>>31));  
    
        if 'DEC' in state: 
            self.beta_dec = beta;
            self.base_dec = np.int32((np.int64(((self.sustainLevel*2**15 - self.att_scl*targetRatio*2**31) * (2**31 - (self.beta_dec))))>>31));
           
        if 'REL' in state: 
            self.beta_rel = beta;
            self.base_rel = -np.int32((np.int64(((self.att_scl*targetRatio*2**31) * (2**31 - (self.beta_rel))))>>31));
                
                   
    
    # Update adsr sample
    def update(self):
        x32 = np.int32((np.int64(self.state)*np.int64(self.beta)>>31));
        self.state = self.base + x32;

        if(self.state < 0):
            self.state = 0;
        
        self.avg_val = np.int16((self.state>>16));
       
    
