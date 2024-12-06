import aiofiles
import asyncio
import numpy as np

from enum import Enum
import time

from tqdm import tqdm

class Direction(Enum):
    NORTH = 1
    EAST  = 2
    SOUTH = 3
    WEST  = 4

async def main():
    puzzle = []
    orig_actor = [0, 0]
    orig_direction = Direction.NORTH
    
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
                    orig_actor = [y, x]
            
            puzzle.append(row)            

    orig_puzzle = np.array(puzzle, dtype=np.byte)
    shape = orig_puzzle.shape
    
    # puzzle[actor[0], actor[1]] = 2
    # print(puzzle)
    
    puzzle = np.copy(orig_puzzle)
    actor = list(orig_actor)
    direction = orig_direction
    previous_positions = set()
    
    while True:
        previous_positions.add((actor[0], actor[1]))
        
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
        
    print(puzzle)
    print(len(previous_positions))
    
    # previous_positions = set()
    # previous_positions.add((actor[0], actor[1], direction))
    causes_loop = 0
    for idx in tqdm(previous_positions):
        puzzle = np.copy(orig_puzzle)
        puzzle[idx[0], idx[1]] = 1
        actor = list(orig_actor)
        direction = orig_direction
        directional_previous_position = set()
        
        while True:
            # puzzle[actor[0], actor[1]] = 2
            if (actor[0], actor[1], direction) in directional_previous_position:
                causes_loop += 1
                break
            else:
                directional_previous_position.add((actor[0], actor[1], direction))
            
            
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
            
        # print(puzzle)    
    print(causes_loop)
    
if __name__=='__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f"Execution time: {(t2-t1)*1000: .2f}ms")