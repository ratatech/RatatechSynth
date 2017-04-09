#!/usr/bin/python

import os, sys, serial, time
py_scripts_pth = os.path.join(os.path.dirname(__file__), '.')
sys.path.append(py_scripts_pth)
from RatatechSerial import RatatechSerial

class RatatechBuild(object):
    def __init__(self):
        
        # ST-link dir
        self.stlink = '/usr/local/bin/st-flash '
        
        # Get project name from the directory name. Note that the test project directory name
        # should coincide with the build directory. BE careful, the index for the string split 
        # is hardcoded since this this script should stay in the same directory. If it has to be
        # moved, modify index accordingly
        print  os.path.dirname(__file__)
        self.prjName = os.path.dirname(__file__).split('/')[-4]
    
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