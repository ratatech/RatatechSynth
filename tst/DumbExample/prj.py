import os,sys


py_scripts_pth = os.path.join(os.path.dirname(__file__), '..','..','python')
sys.path.append(py_scripts_pth)
from RatatechSerial import RatatechSerial


# ST-link dir
stlink = '/usr/local/bin/st-flash '

# Build dir

build_dir = os.path.join(os.path.dirname(__file__), '..','..','DumbExample/')
build_dir = build_dir.replace(' ','\ ')


tst_bin = 'DumbExample.bin'

# ST-link arguments
stlink_cmd = 'write ' + build_dir + tst_bin + ' 0x8000000'


# Put together all command line arguements
cmd = stlink + stlink_cmd

print cmd
# Execute command
os.system(cmd)

# Open serial port to read test output
ratatech_serial = RatatechSerial()
ratatech_serial.open()

