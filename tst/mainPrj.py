import os,sys,time
import argparse
import pdb

# Parse input arguments
parser = argparse.ArgumentParser(description='Build and flash the selected project')
#parser.add_argument('-board',nargs=1,help='Select target board to flash the program. Valid options: [nucleo,pcb]')
parser.add_argument('-board', nargs='+', default='pcb',help='Select target board to flash the program. Valid options: [nucleo,pcb]')
parser.add_argument('-project',help='Select project with target test')
args = parser.parse_args()



# Get project name. Note that the test project directory name
# should match with the build directory name. 
prjName = args.project

# Get board type
board = args.board

# Add main python dir to the path
py_scripts_pth = os.path.join(os.path.dirname(__file__),'..','python')
sys.path.append(py_scripts_pth)
sys.path.append(prjName)

# Add custom classes
from RatatechSerial import RatatechSerial
from RatatechUtils  import RatatechUtils
from RatatechBuild  import RatatechBuild
from RatatechTest   import RatatechTest

# Main test object
tst = RatatechTest(prjName,board)

# Add specifict test 
from prj import test

# Build the project
tst.build.buildPrj()

if tst.utils.isStlinkConnected():
    
    # Program stm32
    tst.build.flash()
 
    # Start usart communication and get test results
    usartOutLines, test_result = tst.testUsart(printConsole=True)   
        
    test(tst,usartOutLines)
    
    # Throw error in case of fail
    if not test_result:
        raise ValueError('Test Failed!') 