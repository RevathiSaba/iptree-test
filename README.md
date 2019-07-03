# Ip tree testing
Utilities to compare memory and search metrics of ModSecurity msc_tree and Waflz IP trie

### Steps

### Generate ipv4 and ipv6 address using random_ip_generator.py.

```bash
./random_ip_generator.py --type=ipv4 --num=100000 --file=ipaddr_v4.txt
```

### Build msc tree

```bash
cd modsec_iptree
g++ -O2 -g3 main.cc msc_tree.cc -o msc
```

### Build nms (waflz ip trie)

```bash
cd waflz_iptree
g++ -O2 -g3 main.cc nms.cc -o nms
```

### Steps to gather memory metrics
	
```bash
/usr/bin/time -v ./msc --file=../testdata/ipaddr_1000_shuffled.txt --type=ipv4
```

```bash
/usr/bin/time -v ./nms --file=../testdata/ipaddr_1000_shuffled.txt
```

Maximum resident memory is the memory used by the tree


### Steps to gather search metrics
	
Uncomment or define search vector in main.cc and rebuild msc and nms

Run msc with the desired testdata

```bash
./msc --file=../testdata/ipaddr_1000_shuffled.txt --type=ipv4
```

```bash
./nms --file=../testdata/ipaddr_1000_shuffled.txt
```

Output will print out the search time in seconds

### Note
testdata folder has lot of samples of ipv4 and ipv6 address to perform load and search


Sample load and search metrics are here: https://verizondigital.github.io/waflz/appendix.html#ip-trie-performance


















	


	




