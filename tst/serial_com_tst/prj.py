import os,sys,time
py_scripts_pth = os.path.join(os.path.dirname(__file__), '..','..','python')
sys.path.append(py_scripts_pth)
from RatatechSerial import RatatechSerial
from RatatechUtils import RatatechUtils
from build import RatatechBuild

# Get project name from the directory name. Note that the test project directory name
# should match with the build directory name. 
prjName = os.path.dirname(__file__).split('/')[-1]

# Create test objects
ratatechUtil = RatatechUtils()
ratatechBuild = RatatechBuild(prjName)


# Check if board is connected and if so, set up usb rights if needed
status = ratatechUtil.checkStm32()

if status == 'CONNECTED':
    
    # Program stm32
    ratatechBuild.flash()

    # Start uart communication and get test results
    uartOutLines = ratatechBuild.testUart(port="ttyACM0") 
       
    # Discard first lines possibly remaining in usart buffer from old tests       
    firstLine = [idx for idx, s in enumerate(uartOutLines) if 'TEST' in s][0]
    uartOutLines = uartOutLines[firstLine:-1]
     
    # Print the usart output    
    for line in uartOutLines:
        print line  

        
