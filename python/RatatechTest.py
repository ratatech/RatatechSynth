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
        print('TODO:do something at init')
        
        # Remove backslash if project names contains it. Typically added with auto-completion
        if prjName.endswith('/'):
            prjName = prjName.split('/')[0]
        
        self.utils = RatatechUtils()
        self.build = RatatechBuild(prjName)
        
         # Select USART port, ttyACM0 used for Nucleo onboard debugging and testing, 
         # ttyUSB0 used for synth pcb debugging and testing    
        if 'nucleo' in board:
            self.port="ttyACM0"
        else:
            self.port="ttyUSB0"
                        
    def parseUsart(self,usartOutLines):
        # Print the usart output    
        test_result = True
        start_printing = False
        newUsartOutLines = []
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
        
        # Open serial port to read test output
        ratatech_serial = RatatechSerial(self.port)       
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
    
        
        
