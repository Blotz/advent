import aiofiles
import asyncio
import numpy as np
import time

def is_inbounds(x, y, max_x, max_y):
    return x >= 0 and x < max_x and y >= 0 and y < max_y

async def main():
    grid = []
    async with aiofiles.open('input.txt', 'r') as f:
        async for line in f:
            grid.append(list(line.strip()))
                
    grid = np.array(grid)
    max_x, max_y = grid.shape
    
    chars = np.unique_values(grid)
    chars = chars[chars != '.']
    
    total_anti_nodes = 0
    anti_nodes_grid = np.zeros((max_x, max_y))
    for c in chars:
        tower = np.argwhere(grid == c)
        
        # clear 1s from anti_nodes_grid
        np.where(anti_nodes_grid == 1, 0, anti_nodes_grid)
        
        for t1 in tower:
            for t2 in tower:
                if np.array_equal(t1, t2):
                    continue
                
                dx = t2[0] - t1[0]
                dy = t2[1] - t1[1]
                
                x = t2[0]
                y = t2[1]
                
                while is_inbounds(x, y, max_x, max_y):
                    anti_nodes_grid[x, y] += 1
                    
                    x += dx
                    y += dy

                x = t1[0]
                y = t1[1]
                
                while is_inbounds(x, y, max_x, max_y):
                    anti_nodes_grid[x, y] += 1
                    
                    x -= dx
                    y -= dy
                
    
    # print(grid)
    # print(anti_nodes_grid)
    # count the number of anti-nodes which is greater than 1
    total_anti_nodes = np.sum(anti_nodes_grid > 1) 
    print(f'Total anti-nodes: {total_anti_nodes}')

    
if __name__ == '__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f'Execution time: {(t2 - t1) * 1000 : .2f}ms')