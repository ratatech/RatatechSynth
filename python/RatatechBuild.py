#!/usr/bin/python

import os, sys, serial, time
from termcolor import colored
py_scripts_pth = os.path.join(os.path.dirname(__file__), '.')
sys.path.append(py_scripts_pth)
from RatatechSerial import RatatechSerial

class RatatechBuild(object):
    def __init__(self,prjName,target='ratatech_board'):
        
        # ST-link dir
        self.stlink = '/usr/local/bin/st-flash '
        
        # Openocd command
        self.openocd = 'openocd '

        self.prjName = '_' + prjName


        # Build dir
        buildDir = os.path.join(os.path.dirname(__file__), '..',self.prjName+'/')
        self.buildDir = buildDir.replace(' ','\ ')
        
        # Root dir
        rootDir = (os.path.join(os.path.dirname(__file__), '..'))
        self.rootDir = rootDir.replace(' ','\ ')
        
        # Set target board used to flash the program
        self.target_board = target

    def buildPrj(self):

        # Check that the project has been compiled at least once manually, otherwise throw error.
        # TODO(JoH): Automatically generate Make files in order not to depend on manually generating them with eclipse
        if not os.path.isdir(self.buildDir):
            raise ValueError('Make file for project %s does not exist. You need to manually compile it first!'%self.buildDir)        
        
        # Put together all command line arguements
        cmd = 'make all -C ' + self.buildDir

        # Execute command
        return_value = os.system(cmd)
        
        # Throw error in case of fail
        if return_value:
            print colored(cmd,'red')
            
            raise ValueError("Compilation error, Test Failed!")  
    
    def flash(self):
        
        # Binary name
        tst_bin = self.prjName +'.bin'
                   
        # ST-link arguments
        stlink_cmd = '--reset write ' + self.buildDir + tst_bin + ' 0x8000000'
           
        # Put together all command line arguements
        cmd = self.stlink + stlink_cmd
        
        print cmd
        
        # Execute command
        os.system(cmd)

    def flashOpenocd(self):
        
        # Binary name
        tst_bin = self.prjName +'.bin'

        # Openocd flash script
        openocd_scr = self.rootDir + '/openocd/scripts/' + self.prjName[1:] + '.cfg'
        
        # Set target board configuration file
        if 'nucleo' in self.target_board:
            stlink_ver = 'stlink-v2-1.cfg'
        else:
            stlink_ver = 'stlink-v2.cfg'
            
        # Openocd arguments
        openocd_cmd = '-f interface/' + stlink_ver +' -f target/stm32f1x_stlink.cfg -f ' + openocd_scr
                      
        # Put together all command line arguements
        cmd = self.openocd + openocd_cmd

        # Execute command
        os.system(cmd)          
        
        
