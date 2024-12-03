import re
import aiofiles
import asyncio
import time

async def main():
    re_mult = r'mul\((\d+),(\d+)\)|do\(\)|don\'t\(\)'
    re_mult = re.compile(re_mult)
    total = 0
    mul_disabled = False
    
    async with aiofiles.open('./3/input.dat', mode='r') as f:
        async for line in f:
            for match in re.finditer(re_mult, line):
                print(match.group(0))
                if match.group(0).startswith('don\'t'):
                    mul_disabled = True
                elif match.group(0).startswith('do'):
                    mul_disabled = False
                else:
                    if mul_disabled:
                        continue
                    
                    lhs = int(match.group(1))
                    rhs = int(match.group(2))
                
                    total += lhs * rhs
    
    print(total)    

if __name__ == '__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f"Time ms: {(t2-t1)*1000:.2f}")