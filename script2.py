import random

size = input('Size: ')

def random_number():
    return random.randint(1, int(size))

with open(f'array{size}.h','w') as f:
    content = f'#include <stdlib.h>\n#include <stdio.h>\n\n'
    content += f'#define SIZE = {size}\n'
    content += '#define NARRAY = ['
    for i in range(int(size)):
        n = random_number()
        if i == int(size)-1:
            content += str(n) + ']'
        else:
            content += str(n) + ', '
    f.write(content)