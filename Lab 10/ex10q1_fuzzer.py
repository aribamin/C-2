import sys
import random
from collections import deque

# Input is piped to stdout
# Solution is piped to stderr

v_front = deque()
v_back = deque()

cases = ["N", "C", "F", "L"]
weights = [10, 8, 6, 4]

cweights = [sum(weights[:x]) for x in range(1, len(weights) + 1)]


def rand_int():
    global v_front, v_back

    l = len(v_front) + len(v_back)

    return random.randint(max(l - 1000, 0), l + 1000)


def rebalance():
    global v_front, v_back

    while len(v_front) - len(v_back) < 0:
        v_front.append(v_back.popleft())

    while len(v_front) - len(v_back) > 1:
        v_back.appendleft(v_front.pop())


def n_queue(i, sid):
    global v_front, v_back

    if len(v_front) + len(v_back) < i:
        v_back.append(sid)
    rebalance()


def c_queue(i, sid):
    global v_front, v_back

    if len(v_front) < i:
        v_front.append(sid)
    rebalance()


def l_dequeue():
    if len(v_back) > 0:
        v_back.pop()
    elif len(v_front) > 0:
        v_front.pop()
    rebalance()


def f_dequeue():
    if len(v_front) > 0:
        ret = v_front.popleft()
    elif len(v_back) > 0:
        ret = v_back.popleft()
    else:
        ret = "empty"

    rebalance()
    return str(ret)


# Generate and solve
with open('/dev/stdout', 'a') as out, open('/dev/stderr', 'a') as err:
    for _ in range(int(sys.argv[1])):
        choice = random.choices(cases, cum_weights=cweights)[0]

        if choice == "N":
            i = rand_int()
            sid = random.randint(10**6, 10**7)
            out.write(f"N {i} {sid}\n")

            n_queue(i, sid)
        elif choice == "C":
            i = rand_int()
            sid = random.randint(10**6, 10**7)
            out.write(f"C {i} {sid}\n")

            c_queue(i, sid)
        elif choice == "L":
            out.write(str(choice))
            out.write("\n")
            l_dequeue()
        else:
            out.write(str(choice))
            out.write("\n")
            err.write(f_dequeue())
            err.write("\n")
