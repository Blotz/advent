import asyncio
import aiofiles
import time

async def main():
    total = 0
    words = [
        'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine'
    ]
    async with aiofiles.open('input.txt', mode='r') as f:
        # read char by char
        async for line in f:
            d1 = None
            d2 = None
            while d1 is None:                
                if line[0].isdigit():
                    d2 = d1 = line[0]
                if line.startswith('one'):
                    d2 = d1 = '1'
                if line.startswith('two'):
                    d2 = d1 = '2'
                if line.startswith('three'):
                    d2 = d1 = '3'
                if line.startswith('four'):
                    d2 = d1 = '4'
                if line.startswith('five'):
                    d2 = d1 = '5'
                if line.startswith('six'):
                    d2 = d1 = '6'
                if line.startswith('seven'):
                    d2 = d1 = '7'
                if line.startswith('eight'):
                    d2 = d1 = '8'
                if line.startswith('nine'):
                    d2 = d1 = '9'
                line = line[1:]
            
            while line:
                if line[0].isdigit():
                    d2 = line[0]
                if line.startswith('one'):
                    d2 = '1'
                if line.startswith('two'):
                    d2 = '2'
                if line.startswith('three'):
                    d2 = '3'
                if line.startswith('four'):
                    d2 = '4'
                if line.startswith('five'):
                    d2 = '5'
                if line.startswith('six'):
                    d2 = '6'
                if line.startswith('seven'):
                    d2 = '7'
                if line.startswith('eight'):
                    d2 = '8'
                if line.startswith('nine'):
                    d2 = '9'
                line = line[1:]
                
            total += int(d1 + d2)
                
    print(total)

if __name__ == '__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f"Execution time: {t2-t1: .2f}s")