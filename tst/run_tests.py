import os
import numpy as np
from termcolor import colored
import argparse

# Parse input arguments
parser = argparse.ArgumentParser(description='Regression testing')
parser.add_argument('-board', nargs='+', default='pcb',help='Select target board to flash the program. Valid options: [nucleo,pcb]')
args = parser.parse_args()

# Get board type
board = args.board[0]

# Init results list
results = []

# Define here list of tests
tests = 'oscillator_tst','lfo_tst','adsr_tst','mixer_tst','mov_avg_tst','sound_gen_tst'

# Ensure testing from main dir
assert 'RatatechSynth' in os.getcwd().split('/')[-1] , colored('All tests must be executed from main dir "RatatechSynth", change directory and try again','red')

# Testing...
for test_name in tests:
    return_value = os.system('python '+ ' tst/mainPrj.py -b ' + board + ' -p tst/'+ test_name + '/')
    results.append([test_name,return_value])
    
# Print results
print '\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n'
print '\t|SUMMARY OF TESTS:'
print '\t------------------------------------------------'
for result in results:
    result_string = ('OK' if result[1] == 0 else 'FAIL')
    out_color = ('green' if result[1] == 0 else 'red')
    print colored('\t' + result[0] + ' ' + '\t ---> ' + result_string,out_color)
print '\n'