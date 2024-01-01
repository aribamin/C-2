import sys
import random

f_nb = int(sys.argv[1])
nb_lines = int(sys.argv[2])

nb_students = random.randint(1, nb_lines + 100)
union_find = list(range(nb_students + 1))


def uf_find(uf, x):
    if uf[x] != x:
        uf[x] = uf_find(uf, uf[x])
    return uf[x]


with open(f"args_{f_nb}", "w") as farg:
    print(nb_lines, nb_students, f"input_{f_nb}", file=farg)

with open(f"input_{f_nb}", "w") as fin, open(f"output_{f_nb}", "w") as fout:
    for _ in range(nb_lines):
        c = "j" if random.random() > 0.6 else "?"

        lhs = random.randint(1, nb_students)
        rhs = random.randint(1, nb_students)

        print(c, lhs, rhs, file=fin)

        a = uf_find(union_find, lhs)
        b = uf_find(union_find, rhs)

        if c == "j":
            union_find[a] = b
        else:
            print("T" if a == b else "F", file=fout)
