function [ADSR_PAR] = setDecay(ADSR_PAR,time,type)

    switch(type)

        case 'EXP'

            % Calc Attack
            ADSR_PAR.b_dec = (ADSR_PAR.expMin/(ADSR_PAR.expMin+1))^(1/(time*ADSR_PAR.fs));
            ADSR_PAR.range_dec = 1-ADSR_PAR.sustainLevel;
            ADSR_PAR.offs_dec = ADSR_PAR.sustainLevel;
            ADSR_PAR.state_dec = 1+ADSR_PAR.expMin;
            ADSR_PAR.peak_dec = 0;
            ADSR_PAR.sgn_dec = 1;
            
       case 'LOG'

            % Calc Attack
            ADSR_PAR.b_dec = ((ADSR_PAR.expMin+1)/ADSR_PAR.expMin)^(1/(time*ADSR_PAR.fs));
            ADSR_PAR.range_dec = 1-ADSR_PAR.sustainLevel;
            ADSR_PAR.offs_dec = 0;
            ADSR_PAR.state_dec = ADSR_PAR.expMin;
            ADSR_PAR.peak_dec = 1;
            ADSR_PAR.sgn_dec = -1;

    end
end

