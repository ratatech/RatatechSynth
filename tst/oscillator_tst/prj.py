import os,sys,time
from RatatechSerial import RatatechSerial
from RatatechUtils import RatatechUtils
from build import RatatechBuild
import argparse

py_scripts_pth = os.path.join(os.path.dirname(__file__), '..','..','python')
sys.path.append(py_scripts_pth)

parser = argparse.ArgumentParser(description='Build and flash the selected project')
parser.add_argument('target_board',
                   help='Select target board to flash the program [nucleo,pcb]')
args = parser.parse_args()


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
    if 'nucleo' in args.target_board:
        port="ttyACM0"
    else:
        port="ttyUSB0"
            
    usartOutLines, test_result = ratatechBuild.testUsart(port,printConsole=True) 
    
    # Parse the output buffer and create wav audio files for each of the generated signals.
    # Each of the corresponding substrings should match the name of the output buffers used in
    # oscillator_tst.cc otherwise the parsing won't work.
    FS = 48000
    debug = False
    ratatechUtil.rawUsart2wav('buff_sin_out',usartOutLines,FS,debug)
    ratatechUtil.rawUsart2wav('buff_squ_out',usartOutLines,FS,debug)
    ratatechUtil.rawUsart2wav('buff_saw_out',usartOutLines,FS,debug)
    ratatechUtil.rawUsart2wav('buff_tri_out',usartOutLines,FS,debug)
      
    # Throw error in case of fail
    if not test_result:
        raise ValueError('Test Failed!')    
