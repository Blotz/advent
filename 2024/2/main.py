import aiofiles
import asyncio
import time

async def main():
    
    safe_reports = 0
    
    async with aiofiles.open('./2/input.dat', mode='r') as f:
        async for line in f:
            report = line.split()
            report = [int(v) for v in report]
            
            if is_safe_report(report):
                safe_reports += 1
            else:
                # generate permutations.
                for idx in range(len(report)):
                    new_report = report[:idx] + report[idx+1:]
                    
                    if is_safe_report(new_report):
                        safe_reports += 1
                        break
                    
                
    print(safe_reports)

def is_safe_report(report):
    if report[0] > report[1]:
        is_decending = True
    else:
        is_decending = False
    
    for idx in range(0, len(report)-1):
        if is_decending and report[idx] <= report[idx + 1]:
            return False

        if (not is_decending) and report[idx] >= report[idx + 1]:
            return False
        
        if abs(report[idx] - report[idx + 1]) > 3:
            return False
    
    return True

if __name__=="__main__":
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f"Time ms: {(t2-t1)*1000:.2f}")