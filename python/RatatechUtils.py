import os
from subprocess import PIPE, Popen


class RatatechUtils(object):
    
    def __init__(self):
        # ST-link dir
        self.stlinkDir = '/usr/local/bin/'

        
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
            