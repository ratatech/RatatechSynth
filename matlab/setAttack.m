function [ADSR_PAR] = setAttack(ADSR_PAR,time,type)

    switch(type)

        case 'EXP'

            % Calc Attack
            ADSR_PAR.b_att = ((ADSR_PAR.expMin+1)/ADSR_PAR.expMin)^(1/(time*ADSR_PAR.fs));
            ADSR_PAR.range_att = 1;
            ADSR_PAR.offs_att = 0;
            ADSR_PAR.state_att = ADSR_PAR.expMin;
            ADSR_PAR.peak_att = 0;
            ADSR_PAR.sgn_att = 1;

       case 'LOG'

            % Calc Attack
            ADSR_PAR.b_att = ((ADSR_PAR.expMin)/(1+ADSR_PAR.expMin))^(1/(time*ADSR_PAR.fs));
            ADSR_PAR.range_att = 1;
            ADSR_PAR.offs_att = 0;
            ADSR_PAR.state_att = ADSR_PAR.expMin+1;
            ADSR_PAR.peak_att = 1;
            ADSR_PAR.sgn_att = -1;

    end
end

