N=(2^14)-1;
adc = ([0:N]);
yN = N;
fpPresicion = 15;
c = 100;
c_fp =floor(c*2^fpPresicion);
dur = N;
b = (N/c)^(1/N);
b_fp = (2^14/c_fp)^(floor(2^fpPresicion/N));
adc_exp =round((b.^adc)*c);



figure(1)
plot(adc_exp,'linewidth',2)
