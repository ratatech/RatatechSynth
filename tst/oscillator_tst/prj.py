import os,sys,time
py_scripts_pth = os.path.join(os.path.dirname(__file__), '..','..','python')
sys.path.append(py_scripts_pth)
from RatatechSerial import RatatechSerial
from RatatechUtils import RatatechUtils

# Serial communication
ratatechUtil = RatatechUtils()

# Check if board is connected and if so, set up usb rights if needed
status = ratatechUtil.checkStm32()

if status == 'CONNECTED':
        
    
    # ST-link dir
    stlink = '/usr/local/bin/st-flash '
    
    # Build dir
    
    build_dir = os.path.join(os.path.dirname(__file__), '..','..','oscillator_tst/')
    build_dir = build_dir.replace(' ','\ ')
    
    # Binary name
    tst_bin = 'oscillator_tst.bin'
    
    # ST-link arguments
    stlink_cmd = 'write ' + build_dir + tst_bin + ' 0x8000000'
       
    # Put together all command line arguements
    cmd = stlink + stlink_cmd
    
    # Execute command
    os.system(cmd)

    # Give some time to start the test app
    time.sleep(0.1)   
    
    # Open serial port to read test output
    ratatech_serial = RatatechSerial()
    ratatech_serial.open()
    
    # Send uart confirmation
    ratatech_serial.write("1")
    
    # Start reading uart
    usartOutLines = ratatech_serial.read()
    
    # Parse the output buffer
    sub = 'buff_sin_out'
    buff_out = [s for s in usartOutLines if sub in s]
    print buff_out
          
    # Check second last output for the test result
    if 'FAIL' in usartOutLines[-2]:
        testResult = 'FAIL'
        raise ValueError('Test Failed!')

