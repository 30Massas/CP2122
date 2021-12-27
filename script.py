import random

size = input('Size: ')

def random_number():
    return random.randint(1, int(size))

with open(f'array{size}.txt','w') as f:
    content = f'{size}\n'
    for i in range(int(size)):
        n = random_number()
        if i == int(size)-1:
            content += str(n)
        else:
            content += str(n) + '\n'
    f.write(content)