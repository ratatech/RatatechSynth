def test(tst,usartOutLines):
    
    # Parse the output buffer and create wav audio files for each of the generated signals.
    # Each of the corresponding substrings should match the name of the output buffers used in
    # oscillator_tst.cc otherwise the parsing won't work.
    FS = 48000
    debug = False    
    
    tst.utils.rawUsart2wav('buff_lfo_sin_out',usartOutLines,FS,debug)
    tst.utils.rawUsart2wav('buff_lfo_tri_out',usartOutLines,FS,debug)
    tst.utils.rawUsart2wav('buff_lfo_saw_out',usartOutLines,FS,debug)
    
    if debug:
        raw_input("Press the <ENTER> to close plots and stop debugging...")
    