import os,sys,time
py_scripts_pth = os.path.join(os.path.dirname(__file__), '..','..','python')
sys.path.append(py_scripts_pth)
from RatatechSerial import RatatechSerial
from RatatechUtils import RatatechUtils
from build import RatatechBuild


# Create test objects
ratatechUtil = RatatechUtils()
ratatechBuild = RatatechBuild()

# Check if board is connected and if so, set up usb rights if needed
status = ratatechUtil.checkStm32()

if status == 'CONNECTED':
    
    # Program stm32
    ratatechBuild.flash()
            
    # Start uart communication and get test results
    uartOutLines = ratatechBuild.testUart() 
    
    firstLine = [idx for idx, s in enumerate(uartOutLines) if 'TEST' in s][0]
    uartOutLines = uartOutLines[firstLine:-1]
    
    for line in uartOutLines:
        print line  
        
    # Check second last output for the test result
    if 'FAIL' in uartOutLines[-2]:
        testResult = 'FAIL'
        raise ValueError('Test Failed!')
