import aiofiles
import asyncio
import numpy as np

from enum import Enum
import time

class Direction(Enum):
    NORTH = 1
    EAST  = 2
    SOUTH = 3
    WEST  = 4

async def main():
    puzzle = []
    actor = [0, 0]
    direction = Direction.NORTH
    
    async with aiofiles.open('input.txt', 'r') as file:
        async for line in file:
            row = []
            for char in line:
                if char == '.':
                    row.append(0)
                elif char == '#':
                    row.append(1)
                elif char == '^':
                    x = len(row)
                    y = len(puzzle)
                    row.append(0)
                    actor = [y, x]
            
            puzzle.append(row)            

    puzzle = np.array(puzzle, dtype=np.byte)
    shape = puzzle.shape
    
    # puzzle[actor[0], actor[1]] = 2
    # print(puzzle)
    
    while True:
        puzzle[actor[0], actor[1]] = 2
        
        if direction == Direction.SOUTH:
            if actor[0] + 1 >= shape[0]:
                break
            elif puzzle[actor[0] + 1, actor[1]] == 1:
                direction = Direction.WEST
            else:
                actor[0] += 1
        
        elif direction == Direction.EAST:
            if actor[1] + 1 >= shape[1]:
                break
            elif puzzle[actor[0], actor[1] + 1] == 1:
                direction = Direction.SOUTH
            else:
                actor[1] += 1
        
        elif direction == Direction.NORTH:
            if actor[0] - 1 < 0:
                break
            elif puzzle[actor[0] - 1, actor[1]] == 1:
                direction = Direction.EAST
            else:
                actor[0] -= 1
        
        elif direction == Direction.WEST:
            if actor[1] - 1 < 0:
                break
            elif puzzle[actor[0], actor[1] - 1] == 1:
                direction = Direction.NORTH
            else:
                actor[1] -= 1
        
        # print(actor, direction)
    
    print(puzzle)
    print(np.count_nonzero(puzzle == 2))
    
if __name__=='__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f"Execution time: {(t2-t1)*1000: .2f}ms")