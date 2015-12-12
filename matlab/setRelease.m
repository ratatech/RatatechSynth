function [ADSR_PAR] = setRelease(ADSR_PAR,time,type)

    switch(type)

        case 'EXP'

            % Calc Attack
            ADSR_PAR.b_rel = (ADSR_PAR.expMin/(ADSR_PAR.expMin+1))^(1/(time*ADSR_PAR.fs));
            ADSR_PAR.range_rel = ADSR_PAR.sustainLevel;
            ADSR_PAR.offs_rel = 0;
            ADSR_PAR.state_rel = 1+ADSR_PAR.expMin;
            ADSR_PAR.peak_rel = 0;
            ADSR_PAR.sgn_rel = 1;
            
       case 'LOG'

            % Calc Attack
            ADSR_PAR.b_rel = ((ADSR_PAR.expMin+1)/ADSR_PAR.expMin)^(1/(time*ADSR_PAR.fs));
            ADSR_PAR.range_rel = ADSR_PAR.sustainLevel;
            ADSR_PAR.offs_rel = 0;
            ADSR_PAR.state_rel = ADSR_PAR.expMin;
            ADSR_PAR.peak_rel = ADSR_PAR.sustainLevel;
            ADSR_PAR.sgn_rel = -1;

    end
end

