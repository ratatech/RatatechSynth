import os,sys,time
py_scripts_pth = os.path.join(os.path.dirname(__file__), '..','..','python')
sys.path.append(py_scripts_pth)
from RatatechSerial import RatatechSerial
from RatatechUtils import RatatechUtils
from build import RatatechBuild

# Get project name from the directory name. Note that the test project directory name
# should match with the build directory name. 
prjName = os.path.realpath(__file__).split('/')[-2]

# Create test objects
ratatechUtil = RatatechUtils()
ratatechBuild = RatatechBuild(prjName)

# Build the project
ratatechBuild.buildPrj()

# Check if board is connected and if so, set up usb rights if needed
status = ratatechUtil.checkStm32()

if status == 'CONNECTED':
    
    # Program stm32
    ratatechBuild.flash()
    
    # Start usart communication and get test results
    # Select USART port, ttyACM0 used for Nucleo onboard debugging and testing, ttyUSB0 used for synth pcb debugging and testing
    port="ttyACM0"
    usartOutLines, test_result = ratatechBuild.testUsart(port) 
    
    

