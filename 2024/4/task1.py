import asyncio
import aiofiles
import regex as re
import numpy as np
import time

async def main():
    puzzel = []
    
    async with aiofiles.open('input.txt') as file:
        async for line in file:
            line = line.strip()
            puzzel.append(list(line))
    
    puzzel = np.array(puzzel)
    x, y = puzzel.shape
    # print(puzzel)

    total = 0

    # top left to bottom right
    for d in range(x + y - 1):
        diagonal = []
        for i in range(x):
            j = d - i
            if 0 <= j < y:
                diagonal.append(puzzel[i, j])
        
        total += local_search(diagonal)

    # bottom left to top right
    for d in range(1 - x, y):
        diagonal = []
        for i in range(x):
            j = i + d
            if 0 <= j < y:
                diagonal.append(puzzel[i, j])
        
        total += local_search(diagonal)
    
    # horizontal
    for row in range(y):
        line = puzzel[row, :]
        total += local_search(line)
    
    # vertical
    for col in range(x):
        line = puzzel[:, col]
        total += local_search(line)
        
    print(total)
    
    

def local_search(array):
    word = r"XMAS|SAMX"
    word = re.compile(word)
    
    if len(array) < 4:
        return 0

    line = ''.join(array)
    count = len(re.findall(word, line, overlapped=True))
    
    # print(f'{line} {count}')
    
    return count


if __name__ == '__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f"Execution time: {(t2-t1)*1000: .2f}ms")