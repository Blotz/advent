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

    for row in range(1, y-1):
        for col in range(1, x-1):
            # print(puzzel[row, col], end='')
            total += local_search(puzzel, (row, col))
    
    print(total)

def local_search(puzzel, pos):
    x, y = pos
    if puzzel[x,y] != 'A':
        return 0
    
    tl = puzzel[x-1,y-1]
    tr = puzzel[x+1,y-1]
    bl = puzzel[x-1,y+1]
    br = puzzel[x+1,y+1]
    
    if tl == 'M' and tr == 'M' and br == 'S' and bl == 'S':
        # print("TOP", pos)
        return 1
    if tl == 'S' and tr == 'S' and br == 'M' and bl == 'M':
        # print("BOTTOM", pos)
        return 1
    
    if tl == 'S' and tr == 'M' and br == 'M' and bl == 'S':
        # print("RIGHT", pos)
        return 1
    if tl == 'M' and tr == 'S' and br == 'S' and bl == 'M':
        # print("LEFT", pos)
        return 1
    
        
    return 0


if __name__ == '__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f"Execution time: {(t2-t1)*1000: .2f}ms")