Firt run qspy wiht with the proper serial port and baud rate for the target and UDP socket for the python test:

	-u [UDP_port]     7701    UDP socket with optional port
	-c <serial_port>  /dev/ttyS0 serial port input (default)
	-b <baud_rate>    115200  baud rate for the com port

example:

	./qspy -c/dev/ttyUSB1 -b115200 -u
	
Then run the tests:
	python3.6 -m qspypy.qutest test_philo.py test_table.py 
