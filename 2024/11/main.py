import aiofiles
import asyncio
import numpy as np
import time
import tqdm
import functools

def count_stones(stone, cache, n=75):
    if ((stone, n, ) in cache.keys()):
        return cache[(stone, n)]
    
    if n == 0:
        return 1 
    
    # Rule 1
    if stone == 0:
        value = count_stones(1, cache, n - 1)
        cache[(stone, n)] = value
        return value

    # Rule 2
    if len(str(stone)) % 2 == 0:
        stone = str(stone)
        v1 = count_stones(int(stone[len(stone)//2:]), cache, n - 1)
        v2 = count_stones(int(stone[:len(stone)//2]), cache, n - 1)
        value = v1 + v2
        cache[(stone, n)] = value
        return value

    # Rule 3
    value = count_stones(stone * 2024, cache, n - 1)
    cache[(stone, n)] = value
    return value

async def main():
    async with aiofiles.open('input.txt', 'r') as f:
        async for line in f:
            stones = list(map(int, line.strip().split(' ')))

    print(stones)
    cache = dict()
    print(sum([count_stones(s, cache) for s in stones]))
    print(len(cache))


if __name__ == '__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f'Execution time: {(t2 - t1) * 1000 : .2f}ms')