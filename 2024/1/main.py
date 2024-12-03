import aiofiles
import asyncio
import heapq
import time

async def main():
    # await task1()
    await task2()

async def task1():
    sorted_left = []
    sorted_right = []
    
    async with aiofiles.open('1/input.dat', mode='r') as f:
        async for line in f:
            # "1234 5678"
            left, right = line.split(maxsplit=1)
            
            left = int(left)
            right = int(right)
            heapq.heappush(sorted_left, left)
            heapq.heappush(sorted_right, right)
    
    total_dist = 0
    
    while sorted_left and sorted_right:
        left = heapq.heappop(sorted_left)
        right = heapq.heappop(sorted_right)
        total_dist += abs(left - right)
        
        
    print(total_dist)

async def task2():
    list_left = []
    count_right = {}
    
    async with aiofiles.open('1/input.dat', mode='r') as f:
        async for line in f:
            # "1234 5678"
            left, right = line.split(maxsplit=1)
            
            left = int(left)
            right = int(right)
            list_left.append(left)
            
            if right in count_right:
                count_right[right] += 1
            else:
                count_right[right] = 1
    
    similarity = 0
    
    for left in list_left:
        if left in count_right:
            similarity += left * count_right[left]
        
        
    print(similarity)

if __name__ == '__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f"Time ms: {(t2-t1)*1000:.2f}")