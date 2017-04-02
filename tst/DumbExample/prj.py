import os,sys
sys.path.append('../../python')
from RatatechSerial import RatatechSerial


# ST-link dir
stlink = '/usr/local/bin/st-flash '

# Build dir
build_dir = '../../DumbExample/'

# ST-link arguments
stlink_cmd = 'write ' + build_dir + 'DumbExample.bin 0x8000000'


# Put together all command line arguements
cmd = stlink + stlink_cmd

# Execute command
os.system(cmd)

# Open serial port to read test output
ratatech_serial = RatatechSerial()
ratatech_serial.open()

