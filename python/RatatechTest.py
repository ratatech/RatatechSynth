#!/usr/bin/python

import os, sys, serial, time
from termcolor import colored
py_scripts_pth = os.path.join(os.path.dirname(__file__), '.')
sys.path.append(py_scripts_pth)

# Add custom classes
from RatatechSerial import RatatechSerial
from RatatechUtils  import RatatechUtils
from RatatechBuild  import RatatechBuild

class RatatechTest(object):
    def __init__(self,prjName,board):
        
        # Keep project name internally
        self.prjName = prjName
        
        # Check if we are executing a manual test
        if 'manual' in (self.prjName):
            self.isManualTst = True
        else:
            self.isManualTst = False
        
        # Throw error in case of fail
        if not prjName.endswith('/'):
            raise ValueError('Wrong project name. It should correspond to the directory containing the test ending with /')
            
        # Remove backslash
        if prjName.count('/')>1:
            prjName = prjName.split('/')[-2]
        
        self.utils = RatatechUtils()
        self.build = RatatechBuild(prjName)
        
         # Select USART port, ttyACM0 used for Nucleo onboard debugging and testing, 
         # ttyUSB0 used for synth pcb debugging and testing    
        if 'nucleo' in board:
            self.port="ttyACM0"
        else:
            self.port="ttyUSB1"
                        
    def parseUsart(self,usartOutLines):
        # Print the usart output    
        test_result = True
        start_printing = False
        newUsartOutLines = []
        
        print('\n\n-----------------------\n')
        for line in usartOutLines:
            
            # Wait until the first line does not appear
            if 'TEST:' in line:
                start_printing = True
            
            # Print line 
            if start_printing:
                print line
                newUsartOutLines.append(line)
                
            # Check for a failed result    
            if 'FAIL' in line:
                test_result = False
                
        return test_result, newUsartOutLines
               
    def testUsart(self,printConsole=False):    
        
#         import pdb
#         pdb.set_trace()
        # Open serial port to read test output
        ratatech_serial = RatatechSerial(self.port,not self.isManualTst)       
        ratatech_serial.ser.printConsole = printConsole
        ratatech_serial.open()       
        
        print 'Serial port open success!'
     
        time.sleep(0.1)    
        print 'Wait usart and read'

        # Start reading usart
        usartOutLines = ratatech_serial.readLines("1")
        
        # Parse lines and check for fails
        test_result,usartOutLines = self.parseUsart(usartOutLines)

        return usartOutLines, test_result
    
        
        
