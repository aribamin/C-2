#!/usr/bin/env python3
import random
import sys

def randchar():
    return chr(random.randint(97, 122))

def genint():
    # Exponential distribution
    return int((random.random() * 10)**100)

def genrot():
    return random.randint(0, 1000)

def genop():
    return random.choice(['+', '@', 'rot'])

def rotate(this, by):
    this = list(str(this))
    by = int(by) % len(this)

    this = this[by:] + this[:by]

    while len(this) > 0 and this[0] == '0':
        this.pop(0)

    if len(this) == 0:
        return "0"
    else:
        return "".join(this)


if __name__ == "__main__":
    N = random.randint(1, 10)
    print(N)

    for _ in range(N):
        lhs = genint()
        op = genop()
        rhs = genrot() if op == 'rot' else genint()

        print(f"{lhs} {op} {rhs}")

        if op == '+':
            print(lhs+rhs, file=sys.stderr)
        elif op == '@':
            print(str(lhs) + str(rhs), file=sys.stderr)
        else:
            print(rotate(lhs, rhs), file=sys.stderr)
