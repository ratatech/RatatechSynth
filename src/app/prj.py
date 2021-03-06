import os,sys,time
py_scripts_pth = os.path.join(os.path.dirname(__file__),'..','..','python')
print py_scripts_pth
sys.path.append(py_scripts_pth)
from RatatechSerial import RatatechSerial
from RatatechUtils import RatatechUtils
from RatatechBuild import RatatechBuild
import argparse



parser = argparse.ArgumentParser(description='Build and flash the selected project')
parser.add_argument('target_board',
                   help='Select target board to flash the program')

args = parser.parse_args()
#print((args.target_board))



# Get project name from the directory name. Note that the test project directory name
# should match with the build directory name. If not, just define the project name as 
# the desired target build directory
#prjName = os.path.realpath(__file__).split('/')[-2]
prjName = 'release'


# Create test objects
ratatechUtil = RatatechUtils()
ratatechBuild = RatatechBuild(prjName,target=args.target_board)

# Build the project
ratatechBuild.buildPrj()

# Check if board is connected and if so, set up usb rights if needed
status = ratatechUtil.checkStm32()

if status == 'CONNECTED':
    
    # Program stm32
    ratatechBuild.flashOpenocd()
