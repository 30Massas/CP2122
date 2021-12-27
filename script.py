import random

def random_number():
    return random.randint(1, 500000)

with open('Array50000.txt','w') as f:
    content = '50000 '
    for _ in range(50000):
        n = random_number()
        content += str(n) + ' '
    f.write(content)