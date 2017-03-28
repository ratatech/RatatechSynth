import os

workspace = '/home/rata/Projects/Eclipse Workspace/RatatechSynth'
cmnd = '/usr/local/bin/st-flash '
cmnd = cmnd + 'write ' + workspace + '/Release/RatatechSynth.bin '
cmnd = cmnd + '0x8000000'

print(cmnd)
os.system(cmnd)