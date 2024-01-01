import sys
import random

NB_LINES = int(sys.argv[1])

array_name = "".join([chr(random.randint(97, 122)) for _ in range(10)])

print("const var " + array_name + " = []!!")

for _ in range(NB_LINES):
    if random.random() < 0.2:
        print(f"print({array_name})!")
    else:
        if random.random() < 0.4:
            index = int(random.random() * 10) - 1
        elif random.random() < 0.4:
            index = round(random.random() * 100, 4)
        else:
            index = round(random.random() * 2**20 - 1, 4)

        index = str(index)
        value = random.randint(0,2147480000)
        print(f"{array_name}[{index}] = {value}!")
