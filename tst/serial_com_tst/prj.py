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
    uartOutLines = ratatechBuild.testUart() 
  
           
    # Discard first lines possibly remaining in usart buffer from old tests       
    firstLine = [idx for idx, s in enumerate(uartOutLines) if 'TEST' in s][0]
    uartOutLines = uartOutLines[firstLine:-1]
     
    # Print the usart output    
    for line in uartOutLines:
        print line  
#             
#     # Check second last output for the test result
#     if 'FAIL' in uartOutLines[-2]:
#         testResult = 'FAIL'
#         raise ValueError('Test Failed!')
#         
#     # Parse the output buffer and create wav audio files for each of the generated signals.
#     # Each of the corresponding substrings should match the name of the output buffers used in
#     # oscillator_tst.cc otherwise the parsing won't work.
#     FS = 4000
#     debug = False
#     ratatechUtil.rawUsart2wav('buff_lfo_sin_out',uartOutLines,FS,debug)
#     ratatechUtil.rawUsart2wav('buff_lfo_tri_out',uartOutLines,FS,debug)
#     ratatechUtil.rawUsart2wav('buff_lfo_saw_out',uartOutLines,FS,debug)
#     ratatechUtil.rawUsart2wav('buff_lfo_osc_mod_out',uartOutLines,FS,debug)
#     if debug:
#         raw_input("Press the <ENTER> to close plots and stop debugging...")
#     
        
