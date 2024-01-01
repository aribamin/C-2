#!/usr/bin/env python3
import random
import sys


def randchar():
    return chr(random.randint(97, 122))


def get_word():
    return "".join(randchar() for _ in range(random.randint(1, 7)))


def levi_dist(a, b):
    if len(b) == 0:
        return len(a)
    elif len(a) == 0:
        return len(b)
    elif a[0] == b[0]:
        return levi_dist(a[1:], b[1:])
    else:
        r1 = levi_dist(a[1:], b)
        r2 = levi_dist(a, b[1:])
        r3 = levi_dist(a[1:], b[1:])

        return 1 + min(r1, r2, r3)

def spell_check(a):
    global dictionary

    min_word = ""
    min_value = 1000000

    for x in dictionary:
        if levi_dist(a, x) < min_value:
            min_word = x
            min_value = levi_dist(a, x)

    return min_word


if __name__ == "__main__":
    N = random.randint(1, 20)
    M = random.randint(0, 100)

    dictionary = list()

    print(f"{N} {M}")

    for _ in range(N - 1):
        word = get_word()
        dictionary.append(word)
        print(word, end=" ")
    word = get_word()
    dictionary.append(word)
    print(word)

    for _ in range(M):
        for _ in range(random.randint(1, 10) - 1):
            word = get_word()
            print(word, end=" ")
            print(spell_check(word), file=sys.stderr, end=" ")
        word = get_word()
        print(word)
        print(spell_check(word), file=sys.stderr)
