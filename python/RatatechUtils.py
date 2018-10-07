import os
from subprocess import PIPE, Popen
import scipy.io.wavfile
import math
import numpy as np
import matplotlib.pyplot as plt


class RatatechUtils(object):
    
    def __init__(self,prjName):
        # ST-link dir
        self.stlinkDir = '/usr/local/bin/'
        
        # Keep project name internally
        self.prjName = prjName

        
    def __cmdline(self,command):        
        p = Popen(args=command,stdout=PIPE,stderr=PIPE,shell=True)
        stdout_data, stderr_data = p.communicate()
        p_status = p.wait()
        if stdout_data:
            return stdout_data
        else:
            return stderr_data

    def checkStm32(self): 
        status = 'UNCHECKED'
        shellOutput = self.__cmdline(self.stlinkDir+'st-info --chipid')
        if not shellOutput:
            # Get usb address where the STM32 is connected
            shellOutput = self.__cmdline(self.stlinkDir+'st-util')
            usbAddr =  shellOutput.split()[-1].replace(':','/')
            
            # Grant st-link rights
            self.__cmdline('sudo ../../python/usbRights.sh '+ usbAddr)
            
            # If success, we should have now a chip ID. Otherwise it means 
            # no board is connected
            shellOutput = self.__cmdline(self.stlinkDir+'st-info --chipid')
            if not shellOutput:
                status = 'UNCONNECTED'
            else:
                status = 'CONNECTED' 
        else:
            status = 'CONNECTED' 
            
        return status
    
    def isStlinkConnected(self):
    
        if self.checkStm32() == 'CONNECTED':
            return(True)
        else:
            return(False)
    
    def rawUsart2wav(self,sub,lines,fs,debug=False):
        buff_out = [s for s in lines if sub in s]
        raw_audio = buff_out[0].split(sub)[1].split('[')[1].split(']')[0]
        raw_audio = np.fromstring(raw_audio, dtype=np.int32, sep=',')
        raw_audio = np.asarray(raw_audio, dtype=np.int16)
        
        # Define output test dir
        outDir = 'tst/' + self.prjName + '/_out/'
        if not os.path.isdir(outDir):
            os.mkdir(outDir)
                        
        scipy.io.wavfile.write(outDir + sub.replace('buff','test')+'.wav',fs,raw_audio)
        t = np.arange(0,float(len(raw_audio))/fs,float(1)/fs)
        if debug:
            plt.figure()
            plt.plot(t,raw_audio)
            plt.show(block=False)
            plt.show()
            #plt.close()
            
            