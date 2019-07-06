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
./build.sh
```

### Build nms (waflz ip trie)

```bash
cd waflz_iptree
./build.sh
```

### Steps to gather memory metrics
	
```bash
/usr/bin/time -v ./msc --file=../testdata/ipv4/ipaddr_1000_shuffled.txt --type=ipv4
```

```bash
/usr/bin/time -v ./nms --file=../testdata/ipv4/ipaddr_1000_shuffled.txt
```

Maximum resident memory is the memory used by the tree


### Steps to gather search metrics

```bash
./msc --file=../testdata/ipaddr_1000_shuffled.txt --type=ipv4 --search=../testdata/ipv4/ipaddr_orginal.txt
```

```bash
./nms --file=../testdata/ipaddr_1000_shuffled.txt --search=../tesdata/ipv4/ipaddr_original.txt
```

Output will print out the search time in seconds

### Note
testdata folder has lot of samples of ipv4 and ipv6 address to perform load and search


Sample load and search metrics are here: https://verizondigital.github.io/waflz/appendix.html#ip-trie-performance


















	


	




