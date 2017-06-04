#!/usr/bin/python

import serial, time


class RatatechSerial(object):

    def __init__(self,port="ttyUSB0"):
        #initialization and open the port

        #possible timeout values:
        #    1. None: wait forever, block call
        #    2. 0: non-blocking mode, return immediately
        #    3. x, x is bigger than 0, float allowed, timeout block call
        
        self.ser = serial.Serial()
        self.ser.port = "/dev/"+port
        self.ser.baudrate = 115200
        self.ser.bytesize = serial.EIGHTBITS #number of bits per bytes
        self.ser.parity = serial.PARITY_NONE #set parity check: no parity
        self.ser.stopbits = serial.STOPBITS_ONE #number of stop bits
        self.ser.timeout = 1            #non-block read
        self.ser.xonxoff = False     #disable software flow control
        self.ser.rtscts = False     #disable hardware (RTS/CTS) flow control
        self.ser.dsrdtr = False       #disable hardware (DSR/DTR) flow control
        self.ser.writeTimeout = 2     #timeout for write
        self.ser.printConsole = False

    def open(self):
        TIMEOUT = 20
        waitTime = 0.5
        serialWait = 0
        while True:
            if (serialWait/waitTime) >= TIMEOUT:
                print "Timeout expired!"
                print "error open serial port: " + str(e)
                exit()
            try: 
                self.ser.open()
                break
            except Exception, e:
                print "Uart busy, wait..."
                time.sleep(waitTime)
                serialWait = serialWait + waitTime

        if self.ser.isOpen():
        
            try:
                self.ser.flushInput() #flush input buffer, discarding all its contents
                self.ser.flushOutput()#flush output buffer, aborting current output 
                self.status = "OPEN"
            except Exception, e1:
                print "error communicating...: " + str(e1)
        else:
            print "cannot open serial port "       
                
    def write(self,serial_str):  
        if self.status == "OPEN":          
            #write data
            self.ser.write(serial_str)
            self.ser.flushInput() #flush input buffer, discarding all its contents
            self.ser.flushOutput()#flush output buffer, aborting current output 
        else:
            print "Serial port not open!"
                    
    def read(self):
        
        if self.status == "OPEN":  
            numOfLines = 0
            usartLines = []
            while True:          
                
                response = self.ser.readline()
                usartLines.append(response)
                
                if len(response)>0:
                    if self.ser.printConsole:
                        print(response)
                                        
                if(response == 'exit'):
                    self.status = "CLOSED"
                    self.ser.close()
                    return usartLines
        else:
            print "Serial port not open!"
            
    def readLines(self,confStr):
        print 'Port ' + self.ser.port + ' is '+ self.status
        if self.status == "OPEN": 
            
            # Send usart confirmation and then start reading 
            self.ser.write(confStr)
            
            numOfLines = 0
            usartLines = []
            while True:    
                # Read line
                response = self.ser.readline()
                
                # Store received line
                usartLines.append(response)

                if self.ser.printConsole:
                    if len(response)>0:
                        print(response)
                    else:
                        print('Shit, no response!')
                
                # When line "exit" is received, close the serial communication and return the received lines
                if(response == 'exit'):
                    self.status = "CLOSED"
                    self.ser.close()
                    return usartLines
        else:
            print "Serial port not open!"                    
    
    def close(self):
        self.ser.flushInput() #flush input buffer, discarding all its contents
        self.ser.flushOutput()#flush output buffer, aborting current output      
        self.status = "CLOSED"
        self.ser.close()
                

        
