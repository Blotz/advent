import aiofiles
import asyncio

import numpy as np
import itertools

import time


async def main():
    t1 = time.time()
    
    person_index = {
        "Alice": 0,
        "Bob": 1,
        "Carol": 2,
        "David": 3,
        "Eric": 4,
        "Frank": 5,
        "George": 6,
        "Mallory": 7
    }
    happiness_matrix = np.zeros((9, 9))
    
    async with aiofiles.open("input.txt", mode="r") as f:
        async for line in f:
            data = line.split()
            
            person = data[0].strip()
            will_gain = True if data[2] == "gain" else False
            happiness = int(data[3]) if will_gain else -int(data[3])
            neighbour = data[10][:-1].strip()
            
            # happiness = -happiness
            
            # print(f"{person} {happiness} {neighbour}")
            happiness_matrix[person_index[person]][person_index[neighbour]] = happiness
    
    # normilze matrix to be positive
    print(happiness_matrix)
    
    total_change = brute_force(happiness_matrix)
    print(total_change)
    
    t2 = time.time()
    print(f"Execution time: {t2-t1}s")
    

def brute_force(matrix):
    max_happiness = 0
    n = len(matrix)
    for perm in itertools.permutations(range(n)):
        happiness = 0
        for i in range(n):
            happiness += matrix[perm[i]][perm[(i+1)%n]]
            happiness += matrix[perm[(i+1)%n]][perm[i]]
        
        max_happiness = max(max_happiness, happiness)
    return max_happiness


if __name__ == "__main__":
    asyncio.run(main())