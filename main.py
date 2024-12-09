import aiofiles
import asyncio
import numpy as np
import time


async def main():
    async with aiofiles.open('test.txt', 'r') as f:
        async for line in f:
            print(line.strip())
    
if __name__ == '__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f'Execution time: {(t2 - t1) * 1000 : .2f}ms')