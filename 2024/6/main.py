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
    
    def next(self):
        if self == Direction.NORTH:
            return Direction.EAST
        elif self == Direction.EAST:
            return Direction.SOUTH
        elif self == Direction.SOUTH:
            return Direction.WEST
        elif self == Direction.WEST:
            return Direction.NORTH

dirs = {
    Direction.NORTH: (-1, 0),
    Direction.EAST:  (0, 1),
    Direction.SOUTH: (1, 0),
    Direction.WEST:  (0, -1)
}

def is_in_bounds(actor, shape):
    return actor[0] >= 0 and actor[0] < shape[0] and actor[1] >= 0 and actor[1] < shape[1]

async def main():
    puzzle = []
    orig_actor = (0, 0)
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
                    orig_actor = (y, x)
            
            puzzle.append(row)            

    puzzle = np.array(puzzle, dtype=np.byte)
    shape = puzzle.shape
    actor = orig_actor
    direction = orig_direction
    previous_positions = set()
    
    while True:
        previous_positions.add((actor[0], actor[1]))
        
        move = dirs[direction]
        next = (actor[0] + move[0], actor[1] + move[1])
        if not is_in_bounds(next, shape):
            break
        elif puzzle[next[0], next[1]] == 1:
            direction = direction.next()
        else:
            actor = next
        
    print(len(previous_positions))
    
    causes_loop = 0
    for idx in tqdm(previous_positions):
        actor = orig_actor
        direction = orig_direction
        directional_previous_position = set()
        
        while True:
            if (direction, actor[0], actor[1]) in directional_previous_position:
                causes_loop += 1
                break
            else:
                directional_previous_position.add((direction, actor[0], actor[1]))
            
            move = dirs[direction]
            next = (actor[0] + move[0], actor[1] + move[1])
            if not is_in_bounds(next, shape):
                break
            elif puzzle[next[0], next[1]] == 1:
                direction = direction.next()
            elif next == (idx[0], idx[1]):
                direction = direction.next()
            else:
                actor = next
            
    print(causes_loop)
    
if __name__=='__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f"Execution time: {(t2-t1): .2f}s")