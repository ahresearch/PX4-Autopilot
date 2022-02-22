#!/usr/bin/env python3
import time

from sys import argv, exit


def print_usage():
	"""Print the usage string if script was used improperly"""
	print('Usage: \
		\t$ {} <pid> <addr > <byte0> <byte1> <byte2> <byte3> <byte4>'.format(argv[0]))
	print("e.g. : \t$ python3 mem_attack.py 21566 0x64ed88 0 0 0 0 0")
	print("e.g. : \t$ python3 mem_attack.py 21566 0x64ed88 h e l p 0")
	exit(1)


def read_write_mem(pid, offset, byte0, byte1, byte2, byte3, byte4):
	try:
		mem_file = open("/proc/{}/mem".format(pid), 'rb+')
	except IOError as e:
		print("Can't open file /proc/{}/maps: IOError: {}".format(pid, e))
		exit(1)
	int_offset = int(offset,16)
	print(hex(int_offset))
	while True:
		mem_file.seek(int_offset)
		mem_file.write(b0.to_bytes(1,byteorder='little'))
		mem_file.write(b1.to_bytes(1,byteorder='little'))
		mem_file.write(b2.to_bytes(1,byteorder='little'))
		mem_file.write(b3.to_bytes(1,byteorder='little'))
		mem_file.write(b4.to_bytes(1,byteorder='little'))
		mem_file.flush()
		time.sleep(0.005)
	mem_file.close()


if (len(argv) == 8):
	pid = argv[1]
	offset = argv[2]
	if isinstance(argv[3], int):
		b0 = int(argv[3])
	else:
		b0 = ord(argv[3])
	if isinstance(argv[4], int):
		b1 = int(argv[4])
	else:
		b1 = ord(argv[4])
	if isinstance(argv[5], int):
		b2 = int(argv[5])
	else:
		b2 = ord(argv[5])
	if isinstance(argv[6], int):
		b3 = int(argv[6])
	else:
		b3 = ord(argv[6])
	if isinstance(argv[7], int):
		b4 = int(argv[7])
	else:
		b4 = ord(argv[7])
	read_write_mem(pid, offset, b0, b1, b2, b3, b4)
else:
	print_usage()
