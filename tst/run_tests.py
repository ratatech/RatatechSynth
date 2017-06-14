import os
import numpy as np
from termcolor import colored

results = []

tests = 'oscillator_tst','lfo_tst','adsr_tst','mixer_tst','mov_avg_tst'

for test_name in tests:
    return_value = os.system("python " + test_name + "/prj.py")
    results.append([test_name,return_value])
    
print '\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n'
print '\t|SUMMARY OF TESTS:'
print '\t------------------------------------------------'
for result in results:
    result_string = ('OK' if result[1] == 0 else 'FAIL')
    out_color = ('green' if result[1] == 0 else 'red')
    print colored('\t' + result[0] + ' ---> ' + result_string,out_color)
print '\n'