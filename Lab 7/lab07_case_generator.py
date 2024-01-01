import sys
import random

NB_AISLE = int(sys.argv[1])
NB_LINES = int(sys.argv[2])

print(NB_AISLE)

for _ in range(NB_LINES):
    if random.random() < 0.1:
        pline = random.randint(0, NB_AISLE-1)
        print(f"0 {pline}")
    else:
        product_code = random.randint(1, 2**30)
        product_name = chr(random.randint(33, 126))
        print(f"{product_code} {product_name}")
