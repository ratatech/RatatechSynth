import mido
import time
import numpy as np

def test(tst,usartOutLines): 

    msg = mido.Message('note_on', note=0)
    port = mido.open_output('CH345:CH345 MIDI 1 32:0')
    _note = 0
    _velocity = int(np.random.random_sample(1)*127)
        
    while True:
        
        # Simply generate note on/off messages to verify proper communication 
        # by the on-board midi input interface
        msg = mido.Message('note_on', note=_note, velocity=_velocity)
        port.send(msg)
        time.sleep(0.1)
        msg = mido.Message('note_off', note=_note,velocity=0)
        port.send(msg)
        
        # Increase note and wrap the highest note
        _note = _note + 1
        if _note>127:
            _note = 0
            
        # Set a random velocity
        _velocity = int(np.random.random_sample(1)*127)    
        time.sleep(2)
         
         

    