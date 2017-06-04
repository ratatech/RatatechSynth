#!/usr/bin/python

import os, sys, serial, time
py_scripts_pth = os.path.join(os.path.dirname(__file__), '.')
sys.path.append(py_scripts_pth)
from RatatechSerial import RatatechSerial

class RatatechBuild(object):
    def __init__(self,prjName):
        
        # ST-link dir
        self.stlink = '/usr/local/bin/st-flash '

        self.prjName = prjName
    
    def flash(self):

        # Build dir
        buildDir = os.path.join(os.path.dirname(__file__), '..',self.prjName+'/')
        buildDir = buildDir.replace(' ','\ ')
        
        # Binary name
        tst_bin = self.prjName+'.bin'
        
        # ST-link arguments
        stlink_cmd = '--reset write ' + buildDir + tst_bin + ' 0x8000000'
           
        # Put together all command line arguements
        cmd = self.stlink + stlink_cmd
        
        # Execute command
        os.system(cmd)
    
    def parseUsart(self,usartOutLines):
        # Print the usart output    
        test_result = True
        for line in usartOutLines:
            print line 
            if 'FAIL' in line:
                test_result = False
        return test_result
               
    def testUsart(self,port="ttyUSB0"):    
        
        # Open serial port to read test output
        ratatech_serial = RatatechSerial(port)
        ratatech_serial.open()  
        print 'Serial port open success!'
     
        time.sleep(0.1)    
        print 'Wait usart and read'

        # Start reading usart
        usartOutLines = ratatech_serial.readLines("1")
        
        # Parse lines and check for fails
        test_result = self.parseUsart(usartOutLines)

        return usartOutLines, test_result
    
        
        
