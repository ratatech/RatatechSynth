fs = 16e3;
N = 16e3*10;
f = 100;
t = [0:N];
x = sin(2*pi*f.*t/fs);
state = 0;
ampli = 1;


attackTime = 0.3;
decayTime = 0.2;
releaseTime = 0.2;
sustainLevel = 0.5;

expMin = 0.009; % adjust to change curvature

% Init structure
ADSR_PAR.sustainLevel = sustainLevel;
ADSR_PAR.expMin = expMin;
ADSR_PAR.fs = fs;

ADSR_PAR = setAttack(ADSR_PAR,attackTime,'EXP');
ADSR_PAR = setDecay(ADSR_PAR,decayTime,'EXP');
ADSR_PAR = setRelease(ADSR_PAR,releaseTime,'EXP');

% Init states
b = ADSR_PAR.b_att;
range = ADSR_PAR.range_att;
offs = ADSR_PAR.offs_att; % for decay
state = ADSR_PAR.state_att;
peakLevel = ADSR_PAR.peak_att;
sgn = ADSR_PAR.sgn_att;
ADSR_STATE = 1;
env = 0;
env_mem = [];
% Run the envelope
for i=[1:N]
   % Output = signal * envelope
    x(i) = x(i) * (env);
    env_mem = [env_mem,env];
    state = b*state;
    env = (peakLevel+sgn*(((state - ADSR_PAR.expMin)) * range) + offs);

    % End of Attack STATE
    if(env>=1)
        ADSR_STATE =2;
        env = 1;
        b = ADSR_PAR.b_dec;
        range = ADSR_PAR.range_dec;
        offs = ADSR_PAR.offs_dec; % for decay
        state = ADSR_PAR.state_dec;
        peakLevel = ADSR_PAR.peak_dec;
        sgn = ADSR_PAR.sgn_dec;

    end

    % End of Decay STATE
    if(ADSR_STATE == 2 && env<=sustainLevel)
        ADSR_STATE =3;
        env = sustainLevel;
        b = 1;
    end	

    % Start of Release STATE
    if(i==fs*8)
        ADSR_STATE =4;
        b = ADSR_PAR.b_rel;
        range = ADSR_PAR.range_rel;
        offs = ADSR_PAR.offs_rel; % for decay
        state = ADSR_PAR.state_rel;
        peakLevel = ADSR_PAR.peak_rel;
        sgn = ADSR_PAR.sgn_rel;

    end

			

end



figure(1)
plot(t/fs,x)

envelope_q15 = (env_mem*2^31)/2^16;
figure(2)
plot(envelope_q15)
