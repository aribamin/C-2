#!/usr/bin/env python3
import sys
import random

if len(sys.argv) < 2:
    print("Usage: python3 ex11q1_fuzzer.py <part-num>")
    exit(1)

l = list()
std_out = list()
std_err = list()

for _ in range(100000):
    if 0.001 > random.random():
        std_out.append("print")
        std_err.append(str(l))
    else:
        new_item = random.randint(0, 2**31)
        index = random.randint(0, len(l))
        l.insert(index, new_item)
        std_out.append(f"insert {new_item} at {index}")


for x in range(int(sys.argv[1])):
    for l in std_out:
        print(l)
    for l in std_err:
        print(l, file=sys.stderr)
