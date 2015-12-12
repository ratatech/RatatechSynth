fs = 16e3;
N = 16e3*10;
f = 100;
t = [0:N];
x = sin(2*pi*f.*t/fs);
state = 0;
ampli = 1;
attackTime = 2;
decayTime = 2;
releaseTime = 2;
sustainLevel = 0.8;

targetRatio = 0.09;

% Calc Attack
b_att = exp(-log((1.0 + targetRatio) / targetRatio) / (attackTime*fs))
attackBase = (1.0 + targetRatio) * (1.0 - b_att)

% Calc Decay
b_dec = exp(-log((1 + targetRatio) / targetRatio) / (decayTime *fs))
decayBase = (sustainLevel-targetRatio) * (1-b_dec)

% Calc Release
b_rel = exp(-log((1 + targetRatio) / targetRatio) / (releaseTime *fs))
releaseBase = (-targetRatio) * (1-b_rel)


% Init states
state = 0;
b = b_att;
base = attackBase;
ADSR_STATE = 1;

% Run the envelope
for i=[1:N]
	% Output = signal * envelope
	x(i) = x(i) * state;
	env = base + state * b;
	
	% End of Attack STATE
	if(env>=1)
		ADSR_STATE =2;
		env = 1;
		b = b_dec;
		base = decayBase;
	end
	
	% End of Decay STATE
	if(ADSR_STATE == 2 && env<sustainLevel)
		ADSR_STATE =3;
		env = sustainLevel;
		b = 1;
		base = 0;
	end	

	% Start of Release STATE
	if(i>=fs*8)
		ADSR_STATE =4;
		b = b_rel;
		base = releaseBase;
	end
			
	if(env<=0)
	 	env = 0;
	end
	state = env;
end


figure(1)
plot(t/fs,x)
hold on;

hold off;