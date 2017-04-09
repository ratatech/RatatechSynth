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
        
    def testUart(self):    
        
        # Open serial port to read test output
        ratatech_serial = RatatechSerial()
        ratatech_serial.open()
       
        # Send uart confirmation
        ratatech_serial.write("1")
        
        # Start reading uart
        usartOutLines = ratatech_serial.read()
        
        return usartOutLines