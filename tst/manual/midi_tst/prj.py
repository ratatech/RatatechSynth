def test(tst,usartOutLines): 
    import mido
    import time
    
    msg = mido.Message('note_on', note=0)
    port = mido.open_output('CH345:CH345 MIDI 1 32:0')
    _note = 124

    msg = mido.Message('note_on', note=_note)
    port.send(msg)
    
    port.send(msg)
    port.send(msg)
        
#     while True:
#         msg = mido.Message('note_on', note=_note)
#         port.send(msg)
#         _note = _note + 1
#         if _note>127:
#             _note = 0
#         time.sleep(1)
#         
#         

    