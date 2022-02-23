#!/usr/bin/env python3
import time

from sys import argv, exit


def print_usage():
	"""Print the usage string if script was used improperly"""
	print('Usage: \
		\t$ {} <pid> <threadid> <addr > <byte0> <byte1> <byte2> <byte3> <byte4>'.format(argv[0]))
	print("e.g. : \t$ python3 mem_attack.py 545177 545178 0x64ed88 0 0 0 0 0")
	print("e.g. : \t$ python3 mem_attack.py 545177 545178 0x64ed88 h e l p 0")
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

def convert_byte(b):
	if isinstance(b, int):
		return int(b)
	else:
		return ord(b)

if (len(argv) == 9):
	pid = argv[1]
	threadid = argv[2]
	address = argv[3]
	print(threadid)
	b0 = convert_byte(argv[4])
	b1 = convert_byte(argv[5])
	b2 = convert_byte(argv[6])
	b3 = convert_byte(argv[7])
	b4 = convert_byte(argv[8])
	read_write_mem(pid, threadid, address, b0, b1, b2, b3, b4)
else:
	print_usage()
