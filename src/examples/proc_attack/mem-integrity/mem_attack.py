#!/usr/bin/env python3
import time

from sys import argv, exit


def print_usage():
	"""Print the usage string if script was used improperly"""
	print('Usage: \
		\t$ {} <pid> <threadname> <addr > <byte0> <byte1> <byte2> <byte3> <byte4>'.format(argv[0]))
	print("e.g. : \t$ python3 mem_attack.py 21566 test_thread 0x64ed88 0 0 0 0 0")
	print("e.g. : \t$ python3 mem_attack.py 21566 test_thread 0x64ed88 h e l p 0")
	exit(1)


def read_write_mem(pid, threadid,address, byte0, byte1, byte2, byte3, byte4):
	try:
		mem_file = open("/proc/{}/task/{}/mem".format(pid,threadid), 'rb+')
	except IOError as e:
		print("Can't open file /proc/{}/task/{}/maps: IOError: {}".format(pid, threadid, e))
		exit(1)
	int_address = int(address,16)
	print(hex(int_address))
	while True:
		mem_file.seek(int_address)
		mem_file.write(b0.to_bytes(1,byteorder='little'))
		mem_file.write(b1.to_bytes(1,byteorder='little'))
		mem_file.write(b2.to_bytes(1,byteorder='little'))
		mem_file.write(b3.to_bytes(1,byteorder='little'))
		mem_file.write(b4.to_bytes(1,byteorder='little'))
		mem_file.flush()
		time.sleep(0.005)
	mem_file.close()


if (len(argv) == 9):
	pid = argv[1]
	threadid = argv[2]
	address = argv[3]
	print(threadid)
	if isinstance(argv[4], int):
		b0 = int(argv[4])
	else:
		b0 = ord(argv[4])
	if isinstance(argv[5], int):
		b1 = int(argv[5])
	else:
		b1 = ord(argv[5])
	if isinstance(argv[6], int):
		b2 = int(argv[6])
	else:
		b2 = ord(argv[6])
	if isinstance(argv[7], int):
		b3 = int(argv[7])
	else:
		b3 = ord(argv[7])
	if isinstance(argv[8], int):
		b4 = int(argv[8])
	else:
		b4 = ord(argv[8])
	read_write_mem(pid, threadid, address, b0, b1, b2, b3, b4)
else:
	print_usage()
