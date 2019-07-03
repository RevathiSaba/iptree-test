#! /usr/bin/env python3

import random
import ipaddress
import argparse



def generate_ipv4(a_range, a_file):
	MAX_IPV4 = ipaddress.IPv4Address._ALL_ONES
	l_file = open(a_file, "a")
	for i in range(a_range):
		val = ipaddress.IPv4Address._string_from_ip_int(random.randint(0, MAX_IPV4))
		l_file.write(val)
		l_file.write('\n')


def generate_ipv6(a_range, a_file):
	MAX_IPV6 = ipaddress.IPv6Address._ALL_ONES
	l_file = open(a_file, "a")
	for i in range(a_range):
		val = ipaddress.IPv6Address._string_from_ip_int(random.randint(0, MAX_IPV6))
		l_file.write(val)
		l_file.write('\n')

def main():

	l_arg_parser = argparse.ArgumentParser(
                description='random ipv4 and ipv6 generator',
                usage='%(prog)s',
                epilog='')
	l_arg_parser.add_argument('-ipv4',
							  '--ipv4',
							  dest ='ipv4',
							  help = 'generate ipv4 address',
							  action = 'store_true',
							  default = None,
							  required = False)
	l_arg_parser.add_argument('-ipv6',
							  '--ipv6',
							  dest ='ipv6',
							  help = 'generate ipv6 address',
							  action = 'store_true',
							  default = None,
							  required = False)
	l_arg_parser.add_argument('-fn',
							  '--filename',
							  dest ='filename',
							  help = 'filename to store ip address',
							  default = 'ipaddr.txt',
							  required = False)
	l_arg_parser.add_argument('-n',
							  '--num',
							  dest ='num',
							  type = int,
							  help = 'num of ipaddress to generate',
							  default = 100,
							  required = False)
	
	l_args = l_arg_parser.parse_args()

	if l_args.ipv4:
		generate_ipv4(l_args.num, l_args.filename)
	elif l_args.ipv6:
		generate_ipv6(l_args.num, l_args.filename)
	else:
		print('provide args')


if __name__ == "__main__":
    main()