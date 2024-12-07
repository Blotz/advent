import asyncio
import aiofiles
import numpy as np
import time

async def main():
    total = 0
    
    async with aiofiles.open('input.txt', 'r') as file:
        async for line in file:
            line = line.strip().split(':')
            target = int(line[0])
            numbers = list(map(int, line[1][1:].split(' ')))
            
            # print(f'Target: {target}')
            # print(f'Numbers: {numbers}')
            
            if find_sum(target, numbers):
                total += target
    
    print(f'Total: {total}')

def find_sum(target, numbers):
    if not numbers:
        return False
    
    numbers = numbers.copy()  # Copy the list to avoid modifying the original
    
    
    n0 = numbers.pop(0)
    n1 = numbers.pop(0)
    
    add = n0 + n1
    mul = n0 * n1
    cat = int(str(n0) + str(n1))
    
    if len(numbers) == 0:
        if add == target:
            return True
        
        if mul == target:
            return True
        
        if cat == target:
            return True

        return False
    
    return (find_sum(target, [add] + numbers) 
        or find_sum(target, [mul] + numbers)
        or find_sum(target, [cat] + numbers))

if __name__ == '__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f'Execution time: {(t2-t1): .2f}s')